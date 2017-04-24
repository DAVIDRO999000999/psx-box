//Init code for the compiler
#ifndef __SPU_CORE_HPP__
#define __SPU_CORE_HPP__

//Include library
#include <stdint.h>

//New namespace
namespace spu {
  //New uint32_t function with the name bus_read
  uint32_t bus_read(int width, uint32_t address);
  
  //New function with the name bus_write
  void bus_write(int width, uint32_t address, uint32_t data);
}

#endif
