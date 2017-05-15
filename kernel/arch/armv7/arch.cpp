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

#include <stdint.h>

#include "armv7/cpu.h"
#include "armv7/interrupt.h"
#include "kernel/arch.h"

extern "C" void CP15VectorBaseAddrSet(unsigned int addr);
extern "C" void _Reset();
extern "C" void SVC_Handler();
extern "C" void IRQHandler();
extern "C" void FIQHandler();

void UndefInstHandler() {
    for (;;) {
    }
}

void AbortHandler() {
    for (;;) {
    }
}

static unsigned int const vecTbl[14] = {
    0xE59FF018, /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018, /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018, /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF018, /* Opcode for loading PC with the contents of [PC + 0x18] */
    0xE59FF014, /* Opcode for loading PC with the contents of [PC + 0x14] */
    0xE24FF008, /* Opcode for loading PC with (PC - 8) (eq. to while(1)) */
    0xE59FF010, /* Opcode for loading PC with the contents of [PC + 0x10] */
    0xE59FF010, /* Opcode for loading PC with the contents of [PC + 0x10] */
    (unsigned int)_Reset,
    (unsigned int)UndefInstHandler,
    (unsigned int)SVC_Handler,
    (unsigned int)AbortHandler,
    (unsigned int)IRQHandler,
    (unsigned int)FIQHandler};

const unsigned int VECTOR_BASE = 0x00000000;

static void CopyVectorTable() {
    uint32_t *dest = (uint32_t *)VECTOR_BASE;
    uint32_t *src = (uint32_t *)vecTbl;
    uint32_t count;

    CP15VectorBaseAddrSet(VECTOR_BASE);

    for (count = 0; count < sizeof(vecTbl) / sizeof(vecTbl[0]); count++) {
        dest[count] = src[count];
    }
}

void arch_init() {
    CopyVectorTable();

    cpu_switch_to_privileged_mode();

    interrupt_init();
}
