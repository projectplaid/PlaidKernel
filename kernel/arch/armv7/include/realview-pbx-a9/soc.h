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

#ifndef __BOARD_SOC_H
#define __BOARD_SOC_H

#define GIC1_BASE (0x1e000000)
#define GIC2_BASE (0x1e001000)
#define GIC3_BASE (0x1e002000)
#define GIC4_BASE (0x1e003000)

#define SYSREG_BASE (0x10000000)
#define SYSCTRL_BASE (0x10001000)
#define TWSIO_BASE (0x10002000)
#define AACI_BASE (0x10004000)
#define MCI_BASE (0x10005000)
#define KMI0_BASE (0x10006000)
#define KMI1_BASE (0x10007000)
#define SSPI_BASE (0x1000d000)
#define SCI_BASE (0x1000e000)
#define WATCHDOG_BASE (0x10010000)
#define TIMER01_BASE (0x10011000)
#define TIMER23_BASE (0x10012000)
#define GPIO0_BASE (0x10013000)
#define GPIO1_BASE (0x10014000)
#define GPIO2_BASE (0x10015000)
#define TWSIO_BASE_DVI (0x10002000)
#define RTC_BASE (0x10017000)
#define DMC_BASE (0x10018000)
#define PCI_BASE (0x10019000)
#define CLCD_BASE (0x10020000)
#define DMA_BASE (0x10030000)
#define SMC_BASE (0x10080000)

#define PERIPHERAL_BASE (0x1f000000)

#define NOR_BASE (0x40000000)
#define DOC_BASE (0x44000000)
#define SRAM_BASE (0x48000000)
#define CONFIGFLASH_BASE (0x4c000000)
#define ETHERNET_BASE (0x4e000000)
#define USB_BASE (0x4f000000)

#define UART0_BASE (0x10009000)
#define UART1_BASE (0x1000A000)
#define UART2_BASE (0x1000B000)
#define UART3_BASE (0x1000C000)

#define REALVIEWPBA_GICOFF	0x0100	/* general interrupt controller */
#define REALVIEWPBA_GDIOFF	0x1000  /* GIC distributor */

#endif // __BOARD_SOC_H