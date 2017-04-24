#include <cassert>
#include "cdrom_core.hpp"
#include "bus.hpp"

cdrom::state_t cdrom::state;

static uint8_t get_arg() {
  auto parameter = cdrom::state.args_fifo.front();
  cdrom::state.args_fifo.pop_front();
  
  return parameter;
}

static void set_arg(uint8_t data) {
  cdrom::state.args_fifo.push_back(data);
}

static uint8_t get_resp() {
  auto response = cdrom::state.resp_fifo.front();
  cdrom::state.resp_fifo.pop_front();
  
  return response;
}

static void set_resp(uint8_t data) {
  cdrom::state.data_fifo.push_back(data);
}

static uint32_t get_data() {
  auto data = cdrom::state.data_fifo.front();
  cdrom::state.data_fifo.pop_front();
  
  return data;
}

static void set_data(uint8_t data) {
  cdrom::state.data_fifo.push_back(data);
}

uint32_t cdrom::bus_read(int width, uint32_t address) {
  assert(width == BYTE);
  
  switch (address - 0x1f801800) {
    case 0: {
      uint32_t result = state.index;
      //Stopping here for now :D
