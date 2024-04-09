#include "timer.h"
/********************************************************************************
* Interrupt Service Routine: Determines the interrupt source and calls the appropriate subroutine
*******************************************************************************/
void interrupt_handler(void){
int ipending;
NIOS2_READ_IPENDING(ipending);
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
    volatile int *interval_timer_ptr = (int *)0xFF202000; // interval timer base address
    *interval_timer_ptr = 0;                                // clear the interrupt

    // If KEY0 is pressed and count is greater than 0, decrement count
    if (start_timer == 1 && count > 0) {
        count--;
        // Update HEX displays with current value of count
        *HEX3_HEX0_ptr = (seg7[count % 10] | seg7[count / 10] << 8);
    }

    // If count reaches 0, stop decrementing and clear key_pressed
    if (count == 0) {
        start_timer = 0;
    }
}

/********************************************************************************/

