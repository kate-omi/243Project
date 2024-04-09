#ifndef MAIN_H
#define MAIN_H

// Last update: 2021-05-06 20:00:00
#include "address_map_nios2.h"

#include "vga.h"
#include "keyboard.h"

#define NUMWORDS 3
#define NUMLETTERS 3

//game modes
#define COMPUTER 1
#define MULTIPLAYER 2
#define NONE 3

//game states
#define START 0
#define MODESELECT 1
#define PENDING 2
#define INCORRECT 3
#define CORRECT 4

struct Word {
    int status;
    char word[NUMLETTERS + 1];
    int letter;
    int screen;
};

struct Game {
    int mode;
    int state;
    struct Word word;
};

struct Game game;

void start();
void modeSelect();
void incorrect();
void correct();

void playComputer();
void playMultiplayer();

void wordCompare();

#endif