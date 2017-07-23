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

#include "armv7/cpu.h"

void cpu_switch_to_privileged_mode(void) { asm("SWI 458752"); }

void cpu_switch_to_user_mode(void) {
    asm("mrs r0, CPSR\n bic r0, #0x0F\n orr r0, #0x10\n msr CPSR, r0");
}

void cpu_irq_disable(void) { asm("dsb\n mrs r0, CPSR\n orr r0, #0x80\n msr CPSR, r0"); }

void cpu_irq_enable(void) { asm("dsb\n mrs r0, CPSR\n bic r0, #0x80\n msr CPSR, r0"); }

void cpu_fiq_disable(void) { asm("dsb\n mrs r0, CPSR\n orr r0, #0x40\n msr CPSR, r0"); }

void cpu_fiq_enable(void) { asm("dsb\n mrs r0, CPSR\n bic r0, #0x40\n msr CPSR, r0"); }
