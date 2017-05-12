#include "kernel/debug.h"
#include "board/realview-pbx-9/soc.h"
#include "drivers/pl011/uart.h"
#include <stdint.h>

void kputs(const char *str) { uart_puts(UART0_BASE, str); }

void kputc(char c) { uart_putc(UART0_BASE, c); }

char kgetc() { return '\0'; }

int _read(int fd, const void *buf, int count) {
    int written = 0;
    (void)fd;

    for (; count > 0; --count) {
        written++;
        *(uint8_t *)buf = (unsigned char)kgetc();

        if (*(uint8_t *)buf == 0x0Du) {
            *(uint8_t *)buf = '\n';
            break;
        }
        (uint8_t *)buf++;
    }

    return written;
}

int _write(int fd, const void *buf, int count) {
    int written = 0;
    (void)fd;

    for (; count > 0; --count) {
        kputc((char)*(uint8_t *)buf);
        (uint8_t *)buf++;
        written++;
    }

    return written;
}