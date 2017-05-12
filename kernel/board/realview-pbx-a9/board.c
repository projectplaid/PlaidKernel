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