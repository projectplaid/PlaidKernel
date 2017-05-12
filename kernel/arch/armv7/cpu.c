#include "armv7/cpu.h"

void cpu_switch_to_privileged_mode(void) { asm("SWI 458752"); }

void cpu_switch_to_user_mode(void) {
    asm("mrs r0, CPSR\n bic r0, #0x0F\n orr r0, #0x10\n msr CPSR, r0");
}

void cpu_irq_disable(void) { asm("dsb\n mrs r0, CPSR\n orr r0, #0x80\n msr CPSR, r0"); }

void cpu_irq_enable(void) { asm("dsb\n mrs r0, CPSR\n bic r0, #0x80\n msr CPSR, r0"); }

void cpu_fiq_disable(void) { asm("dsb\n mrs r0, CPSR\n orr r0, #0x40\n msr CPSR, r0"); }

void cpu_fiq_enable(void) { asm("dsb\n mrs r0, CPSR\n bic r0, #0x40\n msr CPSR, r0"); }
