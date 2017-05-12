#ifndef __ARMV7_CPU_H
#define __ARMV7_CPU_H

void cpu_switch_to_privileged_mode(void);

void cpu_switch_to_user_mode(void);

void cpu_irq_disable(void);

void cpu_irq_enable(void);

void cpu_fiq_disable(void);

void cpu_fiq_enable(void);

#endif // __ARMV7_CPU_H