#include <pch.h>
#include "vram.hpp"
#include "utility.hpp"
// Calling the other headers so we can use them here

static utility::memory_t<20> buffer;

uint16_t* vram::get_pointer() {
      return &buffer.h[0];
}
// get_pointer function gets the address and we return the address of the buffer in memory

uint16_t vram::read(int x, int y) {
	return buffer.h[(y * 1024) + x];
	// read() reads in data that gets passed to it at x and y and returns 
	// the modified buffer
}

void vram::write(int x, int y, uint16_t data) {
      if (x < 0 || x > 0x400) return;
      if (y < 0 || y > 0x200) return;
// were writing to the vram depending on the data we just passed to it

	
// Now we just buffer the system
buffer.h[(y * 1024) + x] = data;
}
