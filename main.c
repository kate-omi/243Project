#include "main.h"

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
                clearScreen();
                break;
        }
    };
}

void start() {
    background(START, 0);
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
        background(PENDING, 0);
        game.mode = COMPUTER;
        playComputer();
    } else {
        game.mode = MULTIPLAYER;
        playMultiplayer();
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

void playComputer() {

    struct Word cat = {0, "CAT", CAT};

    /*  OTHER POTENTIAL WORDS: Bat, Ant, Bow, Bed, Car */
 
    int wordselect = 0; //could make random number using rand() % NUMWORDS for more options
    switch (wordselect) {
        case 0:
            game.word = cat;
            break;
    }

    wordCompare ();
    //structured so more words can be added easily
    return;
}

void playMultiplayer() {
    //print a "tyep here screen"
    for (int i = 0; i < 3; i++) {
        outputHex = keyboard();
        game.word.word[i] = keyboard();
        switch (keyboard()) {    //letter mapping
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
                default:
                    output = '0'; // default case if no match found
        }
        background(game.word.letter, outputHex);
    }

    while(count!=0){//counter is from timer
    wordCompare ();
    }
    //structured so more words can be added easily
    return;
}

void wordCompare() {
    char output;
    int outputHex;
    game.word.letter = 0;
    background(game.word.screen, 0);
    while (game.word.letter != NUMLETTERS) {
        outputHex = keyboard();
        switch (keyboard()) {    //letter mapping
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
        
        if (output != game.word.word[game.word.letter])
            background(10, 0);
        else {
            game.word.letter++;
            background(game.word.letter, outputHex);
        }

    }
    game.state = CORRECT;
    return;
}
