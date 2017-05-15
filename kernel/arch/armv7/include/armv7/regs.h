#ifndef __REGS_H
#define __REGS_H

#define INTC_SIR_IRQ (0x40)
#define INTC_SIR_FIQ (0x44)
#define INTC_CONTROL (0x48)
#define INTC_PROTECTION (0x4c)
#define INTC_IDLE (0x50)
#define INTC_IRQ_PRIORITY (0x60)
#define INTC_FIQ_PRIORITY (0x64)
#define INTC_THRESHOLD (0x68)
#define INTC_SICR (0x6c)
#define INTC_SCR(n) (0x70 + ((n)*0x04))
#define INTC_ITR(n) (0x80 + ((n)*0x20))
#define INTC_MIR(n) (0x84 + ((n)*0x20))
#define INTC_MIR_CLEAR(n) (0x88 + ((n)*0x20))
#define INTC_MIR_SET(n) (0x8c + ((n)*0x20))
#define INTC_ISR_SET(n) (0x90 + ((n)*0x20))
#define INTC_ISR_CLEAR(n) (0x94 + ((n)*0x20))
#define INTC_PENDING_IRQ(n) (0x98 + ((n)*0x20))
#define INTC_PENDING_FIQ(n) (0x9c + ((n)*0x20))
#define INTC_ILR(n) (0x100 + ((n)*0x04))

#define INTC_CONTROL_NEWFIQAGR (0x00000002)
#define INTC_CONTROL_NEWFIQAGR_SHIFT (0x00000001)

#define INTC_SIR_FIQ_ACTIVEFIQ (0x0000007F)
#define INTC_SIR_FIQ_ACTIVEFIQ_SHIFT (0x00000000)

#define INTC_CONTROL_NEWIRQAGR (0x00000001)
#define INTC_CONTROL_NEWIRQAGR_SHIFT (0x00000000)

#define INTC_SIR_IRQ_ACTIVEIRQ (0x0000007F)
#define INTC_SIR_IRQ_ACTIVEIRQ_SHIFT (0x00000000)

#endif // __REGS_H