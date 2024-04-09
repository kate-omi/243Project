#ifndef VGA_H
#define VGA_H

// Include necessary libraries
#include "address_map_nios2.h"

//structure prototypes
struct Screen {
  int x[2]; //start, end and width
  int y[2];
  const int* array;
  int height;
};

//definitions
#define START 0
#define END 1
#define KEYBOARD -1

// Function prototypes
void background (int screen, int letter);
void drawBackground(struct Screen screen, volatile int* pixel_base, volatile short int* pixel_address);
void removeBackground(struct Screen screen, volatile int* pixel_base, volatile short int* pixel_address);

#endif // VGA_H