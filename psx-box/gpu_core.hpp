//Tell the compiler what we are doing here
#ifndef PSXBOX_GPU_CORE_HPP
#define PSXBOX_GPU_CORE_HPP

//Include all the libraries
#include <cstdint>
#include <queue>
#include "utility.hpp"

//New namespace
namespace gpu {
  struct state_t {
    //Bunch of variables that help us with drawing
    uint32_t status = 0x14802000;
    uint32_t texture_window_mask_x;
    uint32_t texture_window_mask_y;
    uint32_t texture_window_offset_x;
    uint32_t texture_window_offset_y;
    uint32_t drawing_area_x1;
    uint32_t drawing_area_y1;
    uint32_t drawing_area_x2;
    uint32_t drawing_area_y2;
    uint32_t x_offset;
    uint32_t y_offset;
    uint32_t display_area_x;
    uint32_t display_area_y;
    uint32_t display_area_x1;
    uint32_t display_area_y1;
    uint32_t display_area_x2;
    uint32_t display_area_y2;
    bool textured_rectangle_x_flip;
    bool textured_rectangle_y_flip;

    struct {
      uint32_t buffer[16];
      int wr;
      int rd;
   } fifo;
   
    struct {
      struct {
        int x;
        int y;
        int w;
        int h;
      } reg;
      
    struct {
      bool active;
      int x;
      int y;
    } run;
  } cpu_to_gpu_transfer;
  
  struct {
    struct {
      int x;
      int y;
      int w;
      int h;
    } reg;
    
    struct {
      bool active;
      int y;
      int x;
    } run;
  } gpu_to_cpu_transfer;
};

    extern state_t state;
    
    //New uint32_t function named bus_read
    uint32_t bus_read(int width, uint32_t address);
    
    //New return type void function with the name bus_write
    void bus_write(int width, uint32_t address, uint32_t data);
    
    //2 New uint32_t vars
    uint32_t data(); // Data
    uint32_t stat(); // Status
    
    //New functions with the name gp0 and gp1
    void gp0(uint32_t data);
    void gp1(uint32_t data);
    
    //New vram_transfer function
    void vram_transfer(uint16_t data);
    
    //We call this new function here
    uint16_t vram_transfer();
    
    //Some color and drawing code
    struct color_t {
      int r;
      int g;
      int b;
    };
    
    struct point_t {
      int x;
      int y;
    };
    
    //New draw point function
    void draw_point(int x, int y, int r, int g, int b);
    
    //New namespace :D
    namespace gouraud {
      struct pixel_t P
        point_t point;
        color_t color;
      };
      
      template<int size>
      struct polygon_t {
        pixel_t v[size];
      };
      
      //Some polygon drawing functions with the return type void
      void draw_poly3(const gpu::gouraud::polygon_t<3> &p);
      void draw_poly4(const gpu::gouraud::polygon_t<4> &p);
    }
    
    //ANOTHER NAMESPACE :D
    namespace texture {
      struct pixel_t {
      //Useful vars
        point_t point;
        color_t color;
        int u;
        int v;
     };
     
     template<int size>
     struct polygon_t {
      pixel_t v[size];
      int clut_x;
      int clut_y;
      int base_u;
      int base_v;
      int depth;
    };
    
    //Functions with the same name as the ones from the last namespace, but different use
    void draw_poly3(const polygon_t<3> &p);
    void draw_poly4(const polygon_t<4> &p);
   } 
}

#endif //PSXBOX_GPU_CORE_HPP
