// Last update: 2021-05-06 20:00:00
#include "address_map_nios2.h"

#include "vga.h"
#include "keyboard.h"
#include "timer.h"

#define NUMWORDS 3
#define NUMLETTERS 3

//game modes
#define COMPUTER 1
#define MULTIPLAYER 2
#define NONE 3

void start();
void modeSelect();
void incorrect();
void correct();

void playComputer();
void playMultiplayer();

void wordCompare();

int main() {
    game.state = START;
    NIOS2_WRITE_IENABLE( 0x81 );    // set interrupt mask bits for levels 0 and 7
    while (1) { //infinite loop
        switch (game.state) {
            case START:
                start();
                break;
            case MODESELECT:
                modeSelect();
                break;
            case COMPUTER:
                playComputer();
                break;
            case MULTIPLAYER:
                playMultiplayer();
                break;

                //
            case PENDING:
                wordCompare(game.word.word, game.word.screen);
                break;
            case INCORRECT:
                incorrect();
                break;
            case CORRECT:
                correct();
                break;
            case TIMEOUT:
                background(-1, 0);
                break;
            default:
                //clearScreen();
                break;
        }
    };
}

void start() {
    background(START, 0);
    keyboardsetup();
    while (1) {}
    return;
}

void modeSelect() {
    background(MODESELECT, 0);
    while (1) {}
    return;
}

void playComputer() {
    background(PENDING, 0);

    struct Word cat = {0, "CAT", 30, 0};
    struct Word dog = {1, "DOG", 40, 0};
    struct Word car = {2, "CAR", 50, 0};

    /*  OTHER POTENTIAL WORDS: Bat, Ant, Bow, Bed, Car */
 
    int wordselect = 0; //could make random number using rand() % NUMWORDS for more options
    switch (wordselect) {
        case 0:
            game.word = cat;
            break;
        case 1:
            game.word = dog;
            break;
        case 2:
            game.word = car;
            break;
    }
    game.state = PENDING;
    NIOS2_WRITE_STATUS(1);
    timer();
    while (1) {}
    //structured so more words can be added easily
    return;
}

int wordCompare(char output) {
    if (output == game.word.word[game.word.i]) {
        game.word.i++;
        return 1;
    } else {
        game.state = INCORRECT;
        return 0;
    }
    return;
}

void incorrect() {
    background(10, 0);
    //timer(1000000000) //2 seconds
    game.state = PENDING;
    background(game.word.screen, 0);
    return;
}

void correct() {
    background(11, 0);
    //timer(1000000000) //2 seconds
    game.state = START;
    return;
}
