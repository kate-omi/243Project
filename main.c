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

int main() {
    game.state = START;
    while (1) { //infinite loop
        switch (game.state) {
            case START:
                start();
                break;
            case MODESELECT:
                modeSelect();
                break;
            case PENDING:
                wordCompare(game.word.word, game.word.screen);
                break;
            case INCORRECT:
                incorrect();
                break;
            case CORRECT:
                correct();
                break;
            default:
                clearscreen();
                break;
        }
    };
}

void start() {
    drawScreen(1);
    while (keyboard() != '\n') {}    //waiting for user input
    game.state = MODESELECT;
    return;
}

void modeSelect() {
    int i = 1;
    char output;
    while (i == 1) {    //wait for user to select mode
        output = keyboard();
        if ((output == '1') || (output == '2'))
            i = 0;
    }

    if (output == '1') {
        game.mode = COMPUTER;
        playComputer();
    } else {
        game.mode = MULTIPLAYER;
        playMultiplayer();
    }

    return;
}

void incorrect() {
    drawScreen(10);
    //timer(1000000000) //2 seconds
    game.state = PENDING;
    drawScreen(game.word.screen);
    return;
}

void correct() {
    drawScreen(11);
    //timer(1000000000) //2 seconds
    game.state = START;
    return;
}

void playComputer() {

    struct Word cat = {0, "CAT", 30};
    struct Word dog = {1, "DOG", 40};
    struct Word car = {2, "CAR", 50};

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

    wordCompare ();

    //structured so more words can be added easily
    return;
}

void playMultiplayer() {

}

void wordCompare() {
    int i = 0;
    drawScreen(game.word.screen);
    while (i != NUMLETTERS) {
        if (keyboard() != game.word.word[i])
            drawScreen(10);
        else {
            game.word.screen++;
            i++;
            drawScreen(game.word.screen);
        }

    }
    game.state = CORRECT;
    return;
}