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