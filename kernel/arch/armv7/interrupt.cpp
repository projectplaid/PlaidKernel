#include "armv7/interrupt.h"
#include <stdio.h>

#define REG_IDX_SHIFT (0x05)
#define REG_BIT_MASK (0x1F)
#define NUM_INTERRUPTS (128u)

void (*interrupt_handlers[NUM_INTERRUPTS])(void);

static void IntDefaultHandler(void) { printf("Default interrupt handler fired\r\n"); }

void interrupt_init() {}

void interrupt_register(unsigned int intrNum, void (*interrupt_handler)(void)) {
    interrupt_handlers[intrNum] = interrupt_handler;
}

void interrupt_unregister(unsigned int intrNum) { interrupt_handlers[intrNum] = IntDefaultHandler; }
