#include <cassert>
#include "cdrom_core.hpp"
#include "bus.hpp"

cdrom::state_t cdrom::state;

// Function gets the args and returns paramter
static uint8_t get_arg() {
  auto parameter = cdrom::state.args_fifo.front();
  cdrom::state.args_fifo.pop_front();
  
  return parameter;
}

// Function sets the args
static void set_arg(uint8_t data) {
  cdrom::state.args_fifo.push_back(data);
}

// Function gets the response from cdrom and returns it
static uint8_t get_resp() {
  auto response = cdrom::state.resp_fifo.front();
  cdrom::state.resp_fifo.pop_front();
  
  return response;
}

// Function sets the response to cdrom
static void set_resp(uint8_t data) {
  cdrom::state.data_fifo.push_back(data);
}

// Function gets data from cdrom
static uint32_t get_data() {
  auto data = cdrom::state.data_fifo.front();
  cdrom::state.data_fifo.pop_front();
  
  return data;
}

// Function sets data for cdrom
static void set_data(uint8_t data) {
  cdrom::state.data_fifo.push_back(data);
}

// Bus read function reads in an address passed to it
uint32_t cdrom::bus_read(int width, uint32_t address) {
  assert(width == BYTE);
  
  
  switch (address - 0x1f801800) {
    case 0: {
      uint32_t result = state.index;
      
      if (state.args_fifo.size() == 0) { result |= 1 << 3; }
      if (state.args_fifo.size() != 16) { result |= 1 << 4; }
      if (state.resp_fifo.size() != 0) { result |= 1 << 5; }
      if (state.data_fifo.size() != 0) { result |= 1 << 6; }
      
      return result;
    }
      
    case 1: return get_resp();
    case 2: return get_data();
    case 3:
      switch (state.index & 1) {
        default: return state.interrupt_enable;
        case 1: return state.interrupt_request;
      }
  }
  
  return 0;

}

void cdrom::bus_write(int width, uint32_t address, uint32_t data) {
  assert(width == BYTE);
  
  switch (address - 0x1f801800) {
    case 0:
      state.index = data & 3;
      return;
    case 1:
      switch (state.index) {
        case 0: // command register
          state.command = uint8_t(data);
          state.has_command = true;
          break;

        case 1: break; // sound map data out
        case 2: break; // sound map coding info
        case 3: break; // audio volume for cd-right to spu-right
      }
        break;
      
    case 2:
        switch (state.index) {
          case 0:
            set_arg(uint8_t(data));
            break;
            
          case 1:
             state.interrupt_enable = data;
             break;
            
          case 2: break;
          case 3: break;
        }
        break;
      
    case 3:
      switch (state.index) {
        case 0: break;
          
        case 1:
          state.interrupt_request &= ~data;
          break;
        
        case 2: break;
        case 3: break;
      }
      break;
  }
}

static void (*second_response)() = nullptr;

static void command_get_stat() {
  set_resp(0x02);

  cdrom::state.interrupt_request = 3;
  bus::irq(2);
}

static void command_test() {
  switch (get_arg()) {
    case 0x20:
      set_resp(0x99);
      set_resp(0x02);
      set_resp(0x01);
      set_resp(0xc3);

      cdrom::state.interrupt_request = 3;
      bus::irq(2);
      break;
  }
}

static void command_get_id_no_disk() {
  set_resp(0x08);
  set_resp(0x40);

  set_resp(0x00);
  set_resp(0x00);

  set_resp(0x00);
  set_resp(0x00);
  set_resp(0x00);
  set_resp(0x00);

  cdrom::state.interrupt_request = 5;
  bus::irq(2);
}

static void command_get_id() {
  set_resp(0x02);

  cdrom::state.interrupt_request = 3;
  bus::irq(2);

  second_response = &command_get_id_no_disk;
}

void cdrom::run() {
  if (second_response) {
    second_response();
    second_response = nullptr;
  }

  if (state.has_command) {
    state.has_command = false;

    switch (state.command) {
      case 0x01:
        return command_get_stat();

      case 0x19:
        return command_test();

      case 0x1a:
        return command_get_id();

      default:
        printf("cd-rom command: $%02x\n", state.command);
        break;
    }
  }
}
