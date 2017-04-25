#include <pch.h>
#include "vram.hpp"
#include "utility.hpp"
// im sure this is obvious but were callin the other headers so we can use them here

static utility::memory_t<20> buffer;

uint16_t* vram::get_pointer() {
      return &buffer.h[0];
}
// the above (i think) is calling the vram pointer and multiplying it with the uint16_t value, then buffers it. (maybe?)

uint16_t vram::read(int x, int y) {
	return buffer.h[(y * 1024) + x];
	// more of the same, i think
}

void vram::write(int x, int y, uint16_t data) {
      if (x < 0 || x > 0x400) return;
      if (y < 0 || y > 0x200) return;
// were writing to the vram depending on the data we just called

// Now we just buffer the system
buffer.h[(y * 1024) + x] = data;
}
