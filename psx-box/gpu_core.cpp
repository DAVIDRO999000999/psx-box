
// Including needed libraries
#include <pch.h>
#include <cassert>
#include "gpu_core.hpp"
#include "bus.hpp"
#include "vram.hpp"

// setting up gpu state in the gpu namespace
gpu::state_t gpu::state;


// The data function collects data for the GPU 
uint32_t gpu::data() {
	if (gpu::state.gpu_to_cpu_transfer.run.active) {
		auto lower = vram_transfer();
		auto upper = vram_transfer();

		return (upper << 16) | lower;
	}

	return 0;
}

// This function also gets data and send it to the GPU
uint32_t gpu::stat() {
	//  19    Vertical Resolution         (0=240, 1=480, when Bit22=1)  ;GP1(08h).2
	//  26    Ready to receive Cmd Word   (0=No, 1=Ready)  ;GP0(...) ;via GP0
	//  27    Ready to send VRAM to CPU   (0=No, 1=Ready)  ;GP0(C0h) ;via GPUREAD
	//  28    Ready to receive DMA Block  (0=No, 1=Ready)  ;GP0(...) ;via GP0

	return (gpu::state.status & ~0x00080000) | 0x1c002000;
}


// This function reads in data from the CPU BUS at the given address
uint32_t gpu::bus_read(int width, uint32_t address) {
	assert(width == WORD);

	switch (address) {
	case 0x1f801810:
		return data();

	case 0x1f801814:
		return stat();

	default:
		return 0;
	}
}


// THis function writes data on the bus at the given address
void gpu::bus_write(int width, uint32_t address, uint32_t data) {
	assert(width == WORD);

	switch (address) {
	case 0x1f801810:
		return gp0(data);

	case 0x1f801814:
		return gp1(data);
	}
}

// Pretty self explanatory Transfers vram
uint16_t gpu::vram_transfer() {
	auto &transfer = gpu::state.gpu_to_cpu_transfer;
	if (!transfer.run.active) {
		return 0;
	}


	// Assiging the data to be equal to whatever value is returned by the read function()
	auto data = vram::read(transfer.reg.x + transfer.run.x,
		transfer.reg.y + transfer.run.y);

	transfer.run.x++;

	if (transfer.run.x == transfer.reg.w) {
		transfer.run.x = 0;
		transfer.run.y++;

		if (transfer.run.y == transfer.reg.h) {
			transfer.run.y = 0;
			transfer.run.active = false;
		}
	}

	return data;
}

void gpu::vram_transfer(uint16_t data) {
	auto &transfer = gpu::state.cpu_to_gpu_transfer;
	if (!transfer.run.active) {
		return;
	}

	vram::write(transfer.reg.x + transfer.run.x,
		transfer.reg.y + transfer.run.y, uint16_t(data));

	transfer.run.x++;

	if (transfer.run.x == transfer.reg.w) {
		transfer.run.x = 0;
		transfer.run.y++;

		if (transfer.run.y == transfer.reg.h) {
			transfer.run.y = 0;
			transfer.run.active = false;
		}
	}
}
