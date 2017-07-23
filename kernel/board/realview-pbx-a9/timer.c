#include "board/realview-pbx-a9/soc.h"
#include "board/realview-pbx-a9/timer.h"
#include "kernel/board.h"

#include <stdint.h>

void timer_init() {
    uint8_t *b;
	uint32_t *t;

    b = (uint8_t *)(PERIPHERAL_BASE + REALVIEWPBA_GICOFF);
    b[0] = 3;
    b[4] = 0xff;

    /* enable distributor then send SGI with distributor */
    t = (uint32_t *)(PERIPHERAL_BASE + REALVIEWPBA_GDIOFF);
    t[0] = 3;
}