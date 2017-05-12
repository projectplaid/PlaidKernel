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

#ifndef __PL011_UART_H
#define __PL011_UART_H

#include <stdbool.h>
#include <stdint.h>

#define UART_DR (0x000)
#define UART_RSR (0x004)
#define UART_FR (0x018)
#define UART_ILPR (0x020)
#define UART_IBRD (0x024)
#define UART_FBRD (0x028)
#define UART_LCR_H (0x02C)
#define UART_CR (0x030)
#define UART_IFLS (0x034)
#define UART_IMSC (0x038)
#define UART_RIS (0x03C)
#define UART_MIS (0x040)
#define UART_ICR (0x044)
#define UART_DMACR (0x048)
#define UART_PID0 (0xFE0)
#define UART_PID1 (0xFE4)
#define UART_PID2 (0xFE8)
#define UART_PID3 (0xFEC)
#define UART_PCID0 (0xFF4)
#define UART_PCID1 (0xFF4)
#define UART_PCID2 (0xFF8)
#define UART_PCID3 (0xFFC)

// flags

#define UART_RXFF_FULL (1 << 6)
#define UART_TXFF_FULL (1 << 5)
#define UART_RXFE (1 << 4)
#define UART_BUSY (1 << 3)

#define UART_CTS_EN (1 << 15)
#define UART_RTS_EN (1 << 14)
#define UART_OUT2 (1 << 13)
#define UART_OUT1 (1 << 12)
#define UART_RTS (1 << 11)
#define UART_DTR (1 << 10)
#define UART_RXE (1 << 9)
#define UART_TXE (1 << 8)
#define UART_LBE (1 << 7)
#define UART_SIRLP (1 << 2)
#define UART_SIREN (1 << 1)
#define UART_ENABLE (1 << 0)

#define UART_FIFO_ENABLE (1 << 4)

#define UART_TXDMAE (1 << 1)
#define UART_RXDMAE (1 << 0)

void uart_puts(uint32_t base, const char *str);
char uart_getc(uint32_t base);
void uart_putc(uint32_t base, char c);
void uart_init(uint32_t base);

#endif // __PL011_UART_H