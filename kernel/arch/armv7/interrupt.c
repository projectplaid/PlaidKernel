#include "armv7/interrupt.h"
#include "realview-pbx-a9/soc.h"
#include "realview-pbx-a9/timer.h"
#include <stdio.h>

#define REG_IDX_SHIFT (0x05)
#define REG_BIT_MASK (0x1F)
#define NUM_INTERRUPTS (128u)

void (*interrupt_handlers[NUM_INTERRUPTS])(void);

static void IntDefaultHandler(void) { printf("Default interrupt handler fired\r\n"); }

void interrupt_init() {
    uint8_t *b;
	uint32_t *t;

    b = (uint8_t *)(PERIPHERAL_BASE + REALVIEWPBA_GICOFF);
    b[0] = 3;
    b[4] = 0xff;

    /* enable distributor then send SGI with distributor */
    t = (uint32_t *)(PERIPHERAL_BASE + REALVIEWPBA_GDIOFF);
    t[0] = 3;    
}

void interrupt_register(unsigned int intrNum, void (*interrupt_handler)(void)) {
    interrupt_handlers[intrNum] = interrupt_handler;
}

void interrupt_unregister(unsigned int intrNum) { interrupt_handlers[intrNum] = IntDefaultHandler; }
