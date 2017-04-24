#ifndef PSXBOX_VRAM_HPP
#define PSXBOX_VRAM_HPP

#include <cstdint>

namespace vram {

uint16_t *get_pointer();

uint16_t read(int x, int y);

void write(int x, int y, uint16_t data);

}

#endif //PSXBOX_VRAM_HPP
