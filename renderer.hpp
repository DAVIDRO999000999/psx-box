//Tell the compiler what we are working on
#ifndef PSXBOX_RENDERER_HPP
#define PSXBOX_RENDERER_HPP

#define SDL_MAIN_HANDLED
#include <SDL.h>

//New namespace
namespace renderer {
  //New destroy function
  void destroy();
  
  //New initialize function
  void initialize();
  
  //New render boolean
  bool render();
}

#endif //PSXBOX_RENDERER_HPP
