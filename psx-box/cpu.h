#pragma once

#ifndef PSXBOX_CPU_CORE_HPP
#define PSXBOX_CPU_CORE_HPP

#include <cstdint>

namespace cpu {

	typedef void(*opcode)();

	// The PS1 Has a total of 67 Op Codes
	extern opcode op_table[64];
	extern opcode op_table_special[64];

	// Stopping Here for tonight will resume work tommorow :)

	struct state_t {


		// Since the PS1 uses 32 bit addressing the registers go up to 32 Bits so we will use uint32
		// There are 16 Registers in total so we needed 16 Elemenets in the Array

		struct {

			uint32_t regs[16];

		} cop0;


		struct {

			/*A typical CPU execution cycle goes roughly like this:


				Fetch the instruction located at address PC,
				Increment the PC to point to the next instruction,
				Execute the instruction,
				Repeat */


			uint32_t gp[32];
			uint32_t lo;
			uint32_t hi;
			uint32_t pc;
			uint32_t this_pc;
			uint32_t next_pc;

		} regs;


		// Setting up some needed booleans for the register state

		uint32_t code;

		bool is_branch;
		bool is_branch_delay_slot;

		bool is_load;
		bool is_load_delay_slot;

		uint32_t load_index;
		uint32_t load_value;

		uint32_t i_stat;
		uint32_t i_mask;
	};
		
		
	extern state_t state;

	// Implementing needed function calls
	void initialize();
	void disassemble();
	void tick();
	void enter_exception(uint32_t code);
	void leave_exception();
	void read_code();


	// read_data func takes the width and address in memory and reads the data from it
	uint32_t read_data(int width, uint32_t address);


	// Writes the given data at the address specified
	void write_data(int width, uint32_t address, uint32_t data);


	// Reads data from the CPU Bus at the specified address in memeory
	uint32_t bus_read(int width, uint32_t address);


	// Writes the given data to the CPU Bus at the address in memory
	void bus_write(int width, uint32_t address, uint32_t data);

	/* -------------
	   Instructions
	   -------------

	   These are the Operation or OpCodes for the PS1 */


	// Implementing Opcodes as function calls
	void op_add();
	void op_addi();
	void op_addiu();
	void op_addu();
	void op_and();
     
 
}




#endif


