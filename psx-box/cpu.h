
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
		// There are 16 Registers in total so we needed 16 Elemenets in the Regs Array

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
	void op_andi();
	void op_beq();
	void op_bgtz();
	void op_blez();
	void op_bne();
	void op_break();
	void op_bxx();
	void op_cop0();
	void op_cop1();
	void op_cop2();
	void op_cop3();
	void op_div();
	void op_divu();
	void op_j();
	void op_jal();
	void op_jalr();
	void op_jr();
	void op_lb();
	void op_lbu();
	void op_lh();
	void op_lhu();
	void op_lui();
	void op_lw();
	void op_lwc0();
	void op_lwc1();
	void op_lwc2();
	void op_lwc3();
	void op_lwl();
	void op_lwr();
	void op_mfhi();
	void op_mflo();
	void op_mthi();
	void op_mtlow();
	void op_mtlo();
	void op_mult();
	void op_multu();
	void op_nor();
	void op_or();
	void op_ori();
	void op_sb();
	void op_sh();
	void op_sll();
	void op_sllv();
	void op_slt();
	void op_slti();
	void op_sltiu();
	void op_sltu();
	void op_sra();
	void op_srav();
	void op_srl();
	void op_srlv();
	void op_slry();
	void op_sub();
	void op_subu();
	void op_sw();
	void op_swc0();
	void op_swc1();
	void op_swc2();
	void op_swc3();
	void op_swl();
	void op_swr();
	void op_syscall();
	void op_xor();
	void op_xori();


	// Undefined Operation Code Instruction
	void op_und();


	namespace decoder {

		uint32_t iconst();
		uint32_t uconst();
		uint32_t sa();
		uint32_t rd();
		uint32_t rt();
		uint32_t rs();



	}

}



#endif //PSXBOX_CPU_CORE_HPP
