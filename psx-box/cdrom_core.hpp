#ifndef PSXBOX_CDROM_CORE_HPP
#define PSXBOX_CDROM_CORE_HPP

#include <cstdint>
#include <deque>

//Create a new namespace for cdrom
namespace cdrom {
  struct state_t {
  
    // All the states that the CDROM can be in
    uint32_t interrupt_enable;
    uint32_t interrupt_disable;
    uint32_t index;
    uint32_t command;
    bool has_command;
    
    
    std::deque<uint8_t> args_fifo;
    std::deque<uint8_t> resp_fifo;
    std::deque<uint8_t> data_fifo;
 };

  extern state_t state;
  
  // bus_read function reads the address passed to it
  uint32_t bus_read(int width, uint32_t address);
  
  
  // bus_write function writes data at the address passed to it
  void bus_write(int width, uint32_t address, uint32_t data);

  
  // Function to run the CD
  void run();

}

#endif //PSXBOX_CDROM_CORE_HPP
