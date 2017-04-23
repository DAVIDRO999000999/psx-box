#pragma once

#ifndef PSXBOX_CPU_CORE_HPP
#define PSXBOX_CPU_CORE_HPP

#include <cstdint>

namespace cpu {

	typedef void(*opcode)();

	// The PS1 Has a total of 64 Op Codes
	extern opcode op_table[64];
	extern opcode op_table_special[64];

	// Stopping Here for tonight will resume work tommorow 




}




#endif


