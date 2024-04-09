#include "keyboard.h"

char keyboard() {
    unsigned char byte1 = 0;
    unsigned char byte2 = 0;

    volatile int * PS2_ptr = (int *)PS2_BASE;

    int PS2_data;
    int RVALID;

    char output;

    while (1) {
        PS2_data = *(PS2_ptr); // read the Data register in the PS/2 port
        RVALID = PS2_data & 0x8000;

        if (RVALID) {
            byte1 = byte2;
            byte2 = PS2_data & 0xFF;
        }

        if (byte1 == 0xF0)    //if key released
            return byte2;
    }
return 0;
}