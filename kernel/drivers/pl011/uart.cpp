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

#include "drivers/pl011/uart.h"
#include "kernel/hw_helpers.h"

static bool uart_initialized = false;

void uart_init(uint32_t base) {
    // Disable the UART
    HWREG(base + UART_CR) &= ~(UART_ENABLE);

    // Flush the transmit FIFO by disabling it
    HWREG(base + UART_LCR_H) &= ~(UART_FIFO_ENABLE);

    // Disable DMA
    HWREG(base + UART_DMACR) &= ~(UART_TXDMAE);
    HWREG(base + UART_DMACR) &= ~(UART_RXDMAE);

    // Enable transmit
    HWREG(base + UART_CR) &= (UART_TXE);

    // Enable receive
    HWREG(base + UART_CR) &= (UART_RXE);

    // Disable loopback
    HWREG(base + UART_CR) &= ~(UART_LBE);

    // Enable the FIFO
    HWREG(base + UART_LCR_H) &= (UART_FIFO_ENABLE);

    // Enable the UART
    HWREG(base + UART_CR) &= (UART_ENABLE);

    uart_initialized = true;
}

void uart_puts(uint32_t base, const char *str) {
    while ('\0' != *str) {
        if ('\n' == *str) {
            uart_putc(base, '\r');
            uart_putc(base, '\n');
        } else {
            uart_putc(base, *str);
        }
        str++;
    }
}

void uart_putc(uint32_t base, char c) {
    if (!uart_initialized) {
        uart_init(base);
    }

    // Don't put anything else into the FIFO if it's full
    while ((HWREG(base + UART_FR) & (UART_TXFF_FULL)) == 1) {
    }

    HWREG(base + UART_DR) = c;
}

char uart_getc(uint32_t base) {
    if (!uart_initialized) {
        uart_init(base);
    }

    // Is there anything available in the FIFO?
    while ((HWREG(base + UART_FR) & (UART_RXFE)) != 0) {
    }

    return HWREG(base + UART_DR);
}

// void uart_baud_rate_set(uint32_t base, uint32_t baud_rate) {
//     uint32_t divisor = uart_divisor_compute(baud_rate);
// }

// uint32_t uart_divisor_compute(uint32_t clock, uint32_t baud_rate) {
//     return (clock) / (16 * baud_rate);
// }