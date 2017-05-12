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

#ifndef __ARMV7_CPU_H
#define __ARMV7_CPU_H

void cpu_switch_to_privileged_mode(void);

void cpu_switch_to_user_mode(void);

void cpu_irq_disable(void);

void cpu_irq_enable(void);

void cpu_fiq_disable(void);

void cpu_fiq_enable(void);

#endif // __ARMV7_CPU_H