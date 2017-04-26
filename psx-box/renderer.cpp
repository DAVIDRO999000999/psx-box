//Add some essential previously coded header files
#include <pch.h>
#include "renderer.hpp"
#include "vram.hpp"

//Create a new SDL_Window with the name window
SDL_Window *window;
//Create a new SDL_Surface with the name surface
SDL_Surface *surface;
//Create a new SDL_Event with the name event
SDL_Event event;

//Create new function with the name "destroy" that destroys the SDL_Window
void renderer::destroy() {
  SDL_DestroyWindow(window);
}

//Create a new function with the name "initialize" that initializes the emulator video, window and gets the surface of the window and stores it in a variable named surface
void renderer::initialize() {
  SDL_Init(SDL_INIT_VIDEO);
  
  window = SDL_CreateWindow("psxbox",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, 1024, 512, 0);
  
  surface = SDL_GetWindowSurface(window);
}

//Create a new uint32_t function with the name "color_16_to_24" that converts 16 colors to 24
uint32_t color_16_to_24(uint32_t color) {
  auto r = ((color << 3) & 0xf8);
  auto g = ((color >> 2) & 0xf8);
  auto b = ((color >> 7) & 0xf8);
  
  return (0xff << 24) | (r << 16) | (g << 8) | (b << 0);
}

//Create a new boolean with the name render 
bool renderer::render() {
  SDL_LockSurface(surface);
  
  auto pixels = (uint32_t *)surface->pixels;
  auto colors = vram::get_pointer();
  
  for (uint32_t i = 0; i < 1024 * 512; i++) {
    *pixels++ = color_16_to_24(colors[i]);
  }
  
  SDL_UnlockSurface(surface);
  SDL_UpdateWindowSurface(window);
  
  return !SDL_PollEvent(&event) || event.type != SDL_QUIT;
}
