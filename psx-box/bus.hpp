#pragma once

#ifndef PSXBOX_BUS_HPP
#define PSXBOX_BUS_HPP

#include <stdint.h>
#include <string>


// Setting up needed types for the CPU Bus  
enum bus_width_t { BYTE, HALF, WORD };


// Setting up the bus namespace 
namespace bus {

	// Initialization logic for setting the BIOS and the game
	void initialize(const std::string &bios_file_name, const std::string &game_file_name);
	
	// Handles interrupts
	void irq(int interrupt);

	// Reads data from the bus
	uint32_t read(int width, uint32_t address, uint32_t data);

	// Writes data to the bus
	void write(int width, uint32_t address, uint32_t data);

}


#endif //PSXBOX_BUS_HPP