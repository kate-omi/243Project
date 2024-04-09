#ifndef VGA_H
#define VGA_H

// Include necessary libraries
#include "address_map_nios2.h"

struct Screen {
    int x[2];
    int y[2];
    const int* array;
    int width;
};

// Define necessary constants
#define VGA_WIDTH  320
#define VGA_HEIGHT 240
#define END 1

// Function prototypes
void drawScreen(int screen);
void plotPixel(int x, int y, short int line_color);

void removeBackground(struct Screen screen, volatile int pixel_buffer_start, volatile short int* pixel_address);
void drawBackground(struct Screen screen, volatile int pixel_buffer_start, volatile short int* pixel_address);
void clearScreen();

#endif // VGA_H