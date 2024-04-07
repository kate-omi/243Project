// Last update: 2021-05-06 20:00:00
#include "address_map_nios2.h"

#include "vga.h"
#include "keyboard.h"

#define NUMWORDS 3
#define NUMLETTERS 3

#define COMPUTER 1
#define MULTIPLAYER 2

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

void wordCompare(char word[5], int screennumber);
void assignWord(struct Word wordSelect);


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
        }

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
    struct Word {
        int status;
        char word[5];
        int screen;
    };

    int wordPool[NUMWORDS] = {0, 1, 2};

    struct Word cat = {0, "CAT", 30};
    struct Word dog = {1, "DOG", 40};
    struct Word car = {2, "CAR", 50};

    /*  OTHER POTENTIAL WORDS: Bat, Ant, Bow, Bed, Car */
 
    int wordselect = 0; //could make random number using rand() % NUMWORDS for more options
    switch (wordselect) {
        case 0:
            assignWord(cat);
            break;
        case 1:
            assignWord(dog);
            break;
        case 2:
            assignWord(car);
            break;
    }

    wordCompare (game.word.word, game.word.screen);

    //structured so more words can be added easily

    return;
}

void playMultiplayer() {

}

void wordCompare(char word[5], int screennumber) {
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

void assignWord(struct Word wordSelect) {
    game.word.status = wordSelect.status;
    game.word.screen = wordSelect.screen;
    for (int i = 0; i < NUMLETTERS; i++) {
        game.word.word[i] = wordSelect.word[i];
    }
    return;
}