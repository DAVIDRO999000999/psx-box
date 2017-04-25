#ifndef PSXBOX_VRAM_HPP
#define PSXBOX_VRAM_HPP

#include <cstdint>

// Setting up namespace for virtual ram
namespace vram {

// This Function gets a pointer  
uint16_t *get_pointer();

// Reads in data at x and y  
uint16_t read(int x, int y);

// Writes given data at x and y  
void write(int x, int y, uint16_t data);

}

#endif //PSXBOX_VRAM_HPP
