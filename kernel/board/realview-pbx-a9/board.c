#include "kernel/board.h"
#include "board/realview-pbx-9/soc.h"
#include "drivers/pl011/uart.h"

extern void CP15VectorBaseAddrSet(char *addr);

void board_init() {
    extern char __isr_vector;
    CP15VectorBaseAddrSet(&__isr_vector);

    uart_init(UART0_BASE);
}

void _init() {}