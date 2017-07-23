#include "armv7/regs.h"
#include "realview-pbx-a9/soc.h"

.text
.arm
.code 32

.equ MODE_FIQ, 0x11
.equ MODE_IRQ, 0x12
.equ MODE_SYS, 0x1F
.equ I_BIT, 0x80

.equ ADDR_SIR_IRQ, GIC1_BASE + INTC_SIR_IRQ
.equ ADDR_SIR_FIQ, GIC1_BASE + INTC_SIR_FIQ
.equ ADDR_CONTROL, GIC1_BASE + INTC_CONTROL
.equ ADDR_THRESHOLD, GIC1_BASE + INTC_THRESHOLD
.equ ADDR_IRQ_PRIORITY, GIC1_BASE + INTC_IRQ_PRIORITY

.equ MASK_ACTIVE_IRQ, INTC_SIR_IRQ_ACTIVEIRQ
.equ MASK_ACTIVE_FIQ, INTC_SIR_FIQ_ACTIVEFIQ
.equ NEWIRQAGR, INTC_CONTROL_NEWIRQAGR
.equ NEWFIQAGR, INTC_CONTROL_NEWFIQAGR

.globl IRQHandler
IRQHandler:
    SUB      r14, r14, #4             @ Apply lr correction
    STMFD    r13!, {r0-r3, r12, r14}  @ Save context
    MRS      r12, spsr                @ Copy spsr
    VMRS     r1, FPSCR                @ Copy fpscr
    STMFD    r13!, {r1, r12}          @ Save spsr and fpscr
    VSTMDB   r13!, {d0-d7}            @ Save D0-D7 NEON/VFP registers

    LDR      r0, =ADDR_THRESHOLD      @ Get the IRQ Threshold
    LDR      r1, [r0, #0]             
    STMFD    r13!, {r1}               @ Save the threshold value

    LDR      r2, =ADDR_IRQ_PRIORITY   @ Get the active IRQ priority          
    LDR      r3, [r2, #0]
    STR      r3, [r0, #0]             @ Set the priority as threshold   

    LDR      r1, =ADDR_SIR_IRQ        @ Get the Active IRQ
    LDR      r2, [r1]
    AND      r2, r2, #MASK_ACTIVE_IRQ @ Mask the Active IRQ number

    MOV      r0, #NEWIRQAGR           @ To enable new IRQ Generation
    LDR      r1, =ADDR_CONTROL
    
    CMP      r3, #0                   @ Check if non-maskable priority 0
    STRNE    r0, [r1]                 @ if > 0 priority, acknowledge INTC
    DSB                               @ Make sure acknowledgement is completed
    
    @
    @ Enable IRQ and switch to system mode. But IRQ shall be enabled
    @ only if priority level is > 0. Note that priority 0 is non maskable.
    @ Interrupt Service Routines will execute in System Mode.
    @
    MRS      r14, cpsr                @ Read cpsr
    ORR      r14, r14, #MODE_SYS
    BICNE    r14, r14, #I_BIT         @ Enable IRQ if priority > 0
    MSR      cpsr, r14
                            
    
    STMFD    r13!, {r14}              @ Save lr_usr

    LDR      r0, =interrupt_handlers  @ Load the base of the vector table
    ADD      r14, pc, #0              @ Save return address in LR
    LDR      pc, [r0, r2, lsl #2]     @ Jump to the ISR

    LDMFD    r13!, {r14}              @ Restore lr_usr

    @
    @ Disable IRQ and change back to IRQ mode
    @
    CPSID    i, #MODE_IRQ

    LDR      r0, =ADDR_THRESHOLD      @ Get the IRQ Threshold

    LDR      r1, [r0, #0]
    CMP      r1, #0                   @ If priority 0
    MOVEQ    r2, #NEWIRQAGR           @ Enable new IRQ Generation
    LDREQ    r1, =ADDR_CONTROL 
    STREQ    r2, [r1]
    
    LDMFD    r13!, {r1}
    STR      r1, [r0, #0]             @ Restore the threshold value
    VLDMIA   r13!, {d0-d7}            @ Restore D0-D7 Neon/VFP registers
    LDMFD    r13!, {r1, r12}          @ Get fpscr and spsr
    MSR      spsr, r12                @ Restore spsr
    VMSR     fpscr, r1                @ Restore fpscr

    LDMFD    r13!, {r0-r3, r12, pc}^  @ Restore the context and return

.globl FIQHandler
FIQHandler:
        SUBS     pc, r14, #0x4            @ Return to program before FIQ

.end