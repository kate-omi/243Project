// Last update: 2021-05-06 20:00:00
#include "address_map_nios2.h"
#include "vga.h"

#define PS2_BASE 0xff200100
#define PIXEL_BASE 0xFF203020
#define NUMWORDS 3
//#include <stdlib.h>

void drawScreen(int screen);
void plot_pixel(int x, int y, short int line_color);
void clear_screen();

char keyboard();
void wordCompare(char word[5], int screennumber);

void playComputer();
void playMultiplayer();

int main() {
    while (1) { //infinite loop
        //start screen
        drawScreen(1);
        //press enter to start
        while (keyboard() != '\n') {}    //error detection

        //choose game style screen
        drawScreen(2);
        //press 1 to play against computer, press 2 to play multiplayer
        int i = 1;
        char output;
        while (i == 1) {
            output = keyboard();
            if ((output == '1') || (output == '2'))
                i = 0;
        }
        if (output == '1') 
            playComputer();
        else 
            playMultiplayer();
    };
}


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

        if (byte1 == 0xF0) {    //if key released
            switch (byte2) {    //letter mapping
                //LETTERS
                case 0x1C:
                    output = 'A';
                    break;
                case 0x32:
                    output = 'B';
                    break;
                case 0x21:
                    output = 'C';
                    break;
                case 0x23:
                    output = 'D';
                    break;
                case 0x24:
                    output = 'E';
                    break;
                case 0x2B:
                    output = 'F';
                    break;
                case 0x34:
                    output = 'G';
                    break;
                case 0x33:
                    output = 'H';
                    break;
                case 0x43:
                    output = 'I';
                    break;
                case 0x3B:
                    output = 'J';
                    break;
                case 0x42:
                    output = 'K';
                    break;
                case 0x4B:
                    output = 'L';
                    break;
                case 0x3A:
                    output = 'M';
                    break;
                case 0x31:
                    output = 'N';
                    break;
                case 0x44:
                    output = 'O';
                    break;
                case 0x4D:
                    output = 'P';
                    break;
                case 0x15:
                    output = 'Q';
                    break;
                case 0x2D:
                    output = 'R';
                    break;
                case 0x1B:
                    output = 'S';
                    break;
                case 0x2C:
                    output = 'T';
                    break;
                case 0x3C:
                    output = 'U';
                    break;
                case 0x2A:
                    output = 'V';
                    break;
                case 0x1D:
                    output = 'W';
                    break;
                case 0x22:
                    output = 'X';
                    break;
                case 0x35:
                    output = 'Y';
                    break;
                case 0x1A:
                    output = 'Z';
                    break;

                //NUMBERS
                case 0x45:
                    output = '0';
                    break;
                case 0x16:
                    output = '1';
                    break;
                case 0x1E:
                    output = '2';
                    break;

                //ALTERNATIVE CHARACTERS
                case 0x29:
                    output = ' ';
                    break;
                case 0x5A:
                    output = '\n';
                    break;
                case 0x66:
                    output = '\b';
                    break;

                default:
                    output = '0'; // default case if no match found
            }       
        return output;
        }
    }
return 0;
}

void playComputer() {
    char words[NUMWORDS][5] = { "CAT", "DOG", "CAR"};
    /*  OTHER POTENTIAL WORDS: Bat, Ant, Bow, Bed, Car */
 
    int wordselect = 0;
    int screenselect = 30;
    char word[5];
    
    int i;
    for (i = 0; words[wordselect][i] != '\0'; ++i)
        word[i] = words[wordselect][i];
    word[i] = '\0';

    if (wordselect == 0) {
        wordCompare(word, screenselect);    //if wordselect = cat
    }

    //structured so more words can be added easily

    return;
}

void playMultiplayer() {

}

void wordCompare(char word[5], int screennumber) {
    int i = 0;
    drawScreen(screennumber);
    while (i != 3) {
        if (keyboard() != word[i])
            drawScreen(10);
        else {
            i++;
            drawScreen(screennumber + i);
        }

    }
    drawScreen(11);
    return;
}