#include <stdint.h>

#include "armv7/cpu.h"
#include "kernel/arch.h"

extern void CP15VectorBaseAddrSet(unsigned int addr);
extern void _Reset();
extern void SVC_Handler();

void UndefInstHandler() {
    for (;;) {
    }
}

void AbortHandler() {
    for (;;) {
    }
}

void IRQHandler() {}

void FIQHandler() {}

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

    // interrupt_init();
}
