/*
 * Copyright 2017 Robert Roland
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "kernel/debug.h"
#include "board/realview-pbx-a9/soc.h"
#include "drivers/pl011/uart.h"
#include <stdint.h>

void kputs(const char *str) { uart_puts(UART0_BASE, str); }

void kputc(char c) { uart_putc(UART0_BASE, c); }

char kgetc() { return '\0'; }

int _read(int fd, const void *buf, int count) {
    int written = 0;
    (void)fd;

    unsigned char *charbuf = (unsigned char *)buf;

    for (; count > 0; --count) {
        written++;
        *charbuf = kgetc();

        if (*charbuf == 0x0Du) {
            *charbuf = '\n';
            break;
        }
        charbuf++;
    }

    return written;
}

int _write(int fd, const void *buf, int count) {
    int written = 0;
    (void)fd;

    unsigned char *charbuf = (unsigned char *)buf;

    for (; count > 0; --count) {
        kputc(*charbuf);
        charbuf++;
        written++;
    }

    return written;
}