#ifndef TIMER_H
#define TIMER_H

#include "address_map_nios2.h"




#ifndef __NIOS2_CTRL_REG_MACROS__
#define __NIOS2_CTRL_REG_MACROS__
/*****************************************************************************/
/* Macros for accessing the control registers. */
/*****************************************************************************/
#define NIOS2_READ_STATUS(dest) \
do { dest = __builtin_rdctl(0); } while (0)
#define NIOS2_WRITE_STATUS(src) \
do { __builtin_wrctl(0, src); } while (0)
#define NIOS2_READ_ESTATUS(dest) \
do { dest = __builtin_rdctl(1); } while (0)
#define NIOS2_READ_BSTATUS(dest) \
do { dest = __builtin_rdctl(2); } while (0)
#define NIOS2_READ_IENABLE(dest) \
do { dest = __builtin_rdctl(3); } while (0)
#define NIOS2_WRITE_IENABLE(src) \
do { __builtin_wrctl(3, src); } while (0)
#define NIOS2_READ_IPENDING(dest) \
do { dest = __builtin_rdctl(4); } while (0)
#define NIOS2_READ_CPUID(dest) \
do { dest = __builtin_rdctl(5); } while (0)
#endif

/* function prototypes */
void interrupt_handler(void);
void interval_timer_isr(void);
void keyboard_isr();
/* The assembly language code below handles Nios II reset processing */
void the_reset (void) __attribute__ ((section (".reset")));
/* The assembly language code below handles Nios II exception processing. This code should not be
* modified; instead, the C language code in the function interrupt_handler() can be modified as
* needed for a given application. */
void the_exception (void) __attribute__ ((section (".exceptions")));


#endif