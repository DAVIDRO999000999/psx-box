#include <pch.h>
#include "gpu_core.hpp"
#include "vram.hpp"


// Min/Max Value stuff
template<int min, int max>
int clip(int value) {
	if (value <= min) return min;
	if (value >= max) return max;
	return value;
};

static int dither_lut[4][4] = {
	{ -4,  0, -3,  1 },
	{ 2, -2,  3, -1 },
	{ -3,  1, -4,  0 },
	{ 3, -1,  2, -2 }
};

//Init gpu::draw_point function
void gpu::draw_point(int x, int y, int r, int g, int b) {
	if (x < int(state.drawing_area_x1) || x > int(state.drawing_area_x2)) return;
	if (y < int(state.drawing_area_y1) || y > int(state.drawing_area_y2)) return;

	auto dither = dither_lut[y & 3][x & 3];

	r = clip<0, 255>(r + dither);
	g = clip<0, 255>(g + dither);
	b = clip<0, 255>(b + dither);

	auto color =
		(((r >> 3) & 0x1f) << 0) |
		(((g >> 3) & 0x1f) << 5) |
		(((b >> 3) & 0x1f) << 10);

	//Write the color along with the x and y coords into vram
	vram::write(x, y, uint16_t(color));
}
