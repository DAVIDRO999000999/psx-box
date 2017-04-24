//Tell the compiler what we are doing
#ifndef __SPU_CORE_HPP__
#define __SPU_CORE_HPP__

//Include a critical library
#include <stdint.h>

namespace spu {
  //Create a new uint32 function with the parameters width(INT) and address(UINT32_T) with the name bus_read
  uint32_t bus_read(int width, uint32_t address);
  
  //Create a new function with the parameters width(INT), address(UINT32_T) and data(UINT32_T)
  void bus_write(int width, uint32_t address, uint32_t data);
}

#endif
