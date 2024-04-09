#include "interrupt.h"

void the_reset (void)
/*******************************************************************************
* Reset code; by using the section attribute with the name ".reset" we allow the linker program
* to locate this code at the proper reset vector address. This code just calls the main program
******************************************************************************/
{
asm (".set noat"); // magic, for the C compiler
asm (".set nobreak"); // magic, for the C compiler
asm ("movia r2, main"); // call the C language main program
asm ("jmp r2");
}

void the_exception (void)
/*******************************************************************************
* Exceptions code; by giving the code a section attribute with the name ".exceptions" we allow
* the linker to locate this code at the proper exceptions vector address. This code calls the
* interrupt handler and later returns from the exception.
******************************************************************************/
{
asm (".set noat"); // magic, for the C compiler
asm (".set nobreak"); // magic, for the C compiler
asm ( "subi sp, sp, 128");
asm ( "stw et, 96(sp)");
asm ( "rdctl et, ctl4");
asm ( "beq et, r0, SKIP_EA_DEC"); // interrupt is not external
asm ( "subi ea, ea, 4"); // must decrement ea by one instruction for externa
asm ( "SKIP_EA_DEC:" );
asm ( "stw r1, 4(sp)" ); // save all registers
asm ( "stw r2, 8(sp)" );
asm ( "stw r3, 12(sp)" );
asm ( "stw r4, 16(sp)" );
asm ( "stw r5, 20(sp)" );
asm ( "stw r6, 24(sp)" );
asm ( "stw r7, 28(sp)" );
asm ( "stw r8, 32(sp)" );
asm ( "stw r9, 36(sp)" );
asm ( "stw r10, 40(sp)" );
asm ( "stw r11, 44(sp)" );
asm ( "stw r12, 48(sp)" );
asm ( "stw r13, 52(sp)" );
asm ( "stw r14, 56(sp)" );
asm ( "stw r15, 60(sp)" );
asm ( "stw r16, 64(sp)" );
asm ( "stw r17, 68(sp)" );
asm ( "stw r18, 72(sp)" );
asm ( "stw r19, 76(sp)" );
asm ( "stw r20, 80(sp)" );
asm ( "stw r21, 84(sp)" );
asm ( "stw r22, 88(sp)" );
asm ( "stw r23, 92(sp)" );
asm ( "stw r25, 100(sp)" ); // r25 = bt (skip r24 = et, because it was saved above)
asm ( "stw r26, 104(sp)" ); // r26 = gp
// skip r27 because it is sp, and there is no point in saving this
asm ( "stw r28, 112(sp)" ); // r28 = fp
asm ( "stw r29, 116(sp)" ); // r29 = ea
asm ( "stw r30, 120(sp)" ); // r30 = ba
asm ( "stw r31, 124(sp)" ); // r31 = ra
asm ( "addi fp, sp, 128" );
asm ( "call interrupt_handler" ); // call the C language interrupt handler
asm ( "ldw r1, 4(sp)" ); // restore all registers
asm ( "ldw r2, 8(sp)" );
asm ( "ldw r3, 12(sp)" );
asm ( "ldw r4, 16(sp)" );
asm ( "ldw r5, 20(sp)" );
asm ( "ldw r6, 24(sp)" );
asm ( "ldw r7, 28(sp)" );
asm ( "ldw r8, 32(sp)" );
asm ( "ldw r9, 36(sp)" );
asm ( "ldw r10, 40(sp)" );
asm ( "ldw r11, 44(sp)" );
asm ( "ldw r12, 48(sp)" );
asm ( "ldw r13, 52(sp)" );
asm ( "ldw r14, 56(sp)" );
asm ( "ldw r15, 60(sp)" );
asm ( "ldw r16, 64(sp)" );
asm ( "ldw r17, 68(sp)" );
asm ( "ldw r18, 72(sp)" );
asm ( "ldw r19, 76(sp)" );
asm ( "ldw r20, 80(sp)" );
asm ( "ldw r21, 84(sp)" );
asm ( "ldw r22, 88(sp)" );
asm ( "ldw r23, 92(sp)" );
asm ( "ldw r24, 96(sp)" );
asm ( "ldw r25, 100(sp)" ); // r25 = bt
asm ( "ldw r26, 104(sp)" ); // r26 = gp
// skip r27 because it is sp, and we did not save this on the stack
asm ( "ldw r28, 112(sp)" ); // r28 = fp
asm ( "ldw r29, 116(sp)" ); // r29 = ea
asm ( "ldw r30, 120(sp)" ); // r30 = ba
asm ( "ldw r31, 124(sp)" ); // r31 = ra
asm ( "addi sp, sp, 128" );
asm ( "eret" );
}

/********************************************************************************
* Interrupt Service Routine: Determines the interrupt source and calls the appropriate subroutine
*******************************************************************************/
void interrupt_handler(void){
int ipending;
NIOS2_READ_IPENDING(ipending);
    if (ipending & 0x2)
        keyboard_isr();
	if ( ipending & 0x1 ) // interval timer is interrupt level 0
	    interval_timer_isr( );
	// else, ignore the interrupt
	return;
}
/********************************************************************************
* Interval timer interrupt service routine
* Shifts a pattern being displayed on the HEX displays. The shift direction is determined
* by the external variable key_pressed.
********************************************************************************/
void interval_timer_isr(void) {
    unsigned char seg7[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};
    volatile int *HEX3_HEX0_ptr = (int *)HEX3_HEX0_BASE;
    *HEX3_HEX0_ptr = (seg7[0] | seg7[3] << 8);


    volatile int *interval_timer_ptr = (int *)0xFF202000; // interval timer base address
    *interval_timer_ptr = 0;                                // clear the interrupt

    // If KEY0 is pressed and count is greater than 0, decrement count
    if (count) {
        count--;
        // Update HEX displays with current value of count
        *HEX3_HEX0_ptr = (seg7[count % 10] | seg7[count / 10] << 8);
    } else {
        game.state = TIMEOUT;
        NIOS2_WRITE_STATUS(0);  //disable Nios II interrupts
    }
    return;
}
/********************************************************************************/
void keyboard_isr() {
    int letter = keyboard();
    char output;
    switch (letter) {    //letter mapping
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
    switch (game.state){
        case START:
            if (output == '\n')
                game.state = MODESELECT;
            break;
        case MODESELECT:
            if (output == '1')
                game.state = COMPUTER;
            else if (output == '2')
                game.state = MULTIPLAYER;
            NIOS2_WRITE_STATUS(0);  //disable Nios II interrupts
            break;
        case PENDING:
            int i = wordCompare(output);
            if (i) {
                background(0, letter);
                if (game.word.i == NUMLETTERS)
                    game.state = START;
            } else 
                background(11, 0);
            break;
            
    }
    return;
}
/********************************************************************************/

void timer() {
    count = 30;
/* Declare volatile pointers to I/O registers (volatile means that IO load and store instructions
* will be used to access these pointer locations instead of regular memory loads and stores) */
volatile int * interval_timer_ptr = (int *) TIMER_BASE; // interval timer base address
/* set the interval timer period for scrolling the HEX displays */
int counter = 100000000; //1sec
*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
/* start interval timer, enable its interrupts */
*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1

return;
}

void keyboardsetup() {
    volatile int * keyboard_ptr = (int * ) PS2_BASE;
    *(keyboard_ptr + 0x4) = 0x1; // enable interrupts
    NIOS2_WRITE_STATUS(1);  //enable Nios II interrupts
}
