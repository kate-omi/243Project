#include "timer.h"

int main(void)
{
    int i;
    int j;
i=10;
j=2;
count = 30;
volatile int *HEX3_HEX0_ptr = (int *)HEX3_HEX0_BASE;
unsigned char seg7[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x67};
*HEX3_HEX0_ptr = (seg7[0] | seg7[3] << 8);
/* Declare volatile pointers to I/O registers (volatile means that IO load and store instructions
* will be used to access these pointer locations instead of regular memory loads and stores) */
volatile int * interval_timer_ptr = (int *) 0xFF202000; // interval timer base address
volatile int * KEY_ptr = (int *) 0xFF200050; // pushbutton KEY address
/* set the interval timer period for scrolling the HEX displays */
int counter = 100000000; //1sec
*(interval_timer_ptr + 0x2) = (counter & 0xFFFF);
*(interval_timer_ptr + 0x3) = (counter >> 16) & 0xFFFF;
/* start interval timer, enable its interrupts */
*(interval_timer_ptr + 1) = 0x7; // STOP = 0, START = 1, CONT = 1, ITO = 1
*(KEY_ptr + 2) = 0xF; /* write to the pushbutton interrupt mask register, and
* set mask bits to 1 */
start_timer = 1;
	while(1){
		if (start_timer==1){
			NIOS2_WRITE_IENABLE( 0x3 ); /* set interrupt mask bits for levels 0 (interval timer)
			* and level 1 (pushbuttons) */
			NIOS2_WRITE_STATUS( 1 ); // enable Nios II interrupts
		}
	}
}