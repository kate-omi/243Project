#ifndef VGA_H
#define VGA_H

// Include necessary libraries
#include "address_map_nios2.h"

// Define necessary constants
#define VGA_WIDTH  320
#define VGA_HEIGHT 240

// Function prototypes
void drawScreen(int screen);
void plot_pixel(int x, int y, short int line_color);
void clear_screen();

#endif // VGA_H