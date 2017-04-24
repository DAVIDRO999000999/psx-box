//Basic initilization, required for the software to know what we are actually doing here
#ifndef PSXBOX_INPUT_HPP
#define PSXBOX_INPUT_HPP

//Including a required library
#include <cstdint>

//New namespace
namespace input {
  struct state_t { 
    //Create a uint32 with the name status
    uint32_t status;
  };
  
  //Create a uint32 function with the name bus_read and the paramaters width(INT) and address(UINT32_T)
  uint32_t bus_read(int width, uint32_t address);
  
  //Create a new function called bus_write with the parameters width(INT), address(UINT32_T) and data(UINT32_T)
  void bus_write(int width, uint32_t address, uint32_t data);
}

#endif //PSXBOX_INPUT_HPP
