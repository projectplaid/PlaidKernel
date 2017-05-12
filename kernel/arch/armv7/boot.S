@
@ Define the stack sizes for different modes. The user/system mode will use
@ the rest of the total stack size
@
    .equ  UND_STACK_SIZE, 0x8
    .equ  ABT_STACK_SIZE, 0x8
    .equ  FIQ_STACK_SIZE, 0x8
    .equ  IRQ_STACK_SIZE, 0x1000
    .equ  SVC_STACK_SIZE, 0x8

@
@ to set the mode bits in CPSR for different modes
@
    .equ  MODE_USR, 0x10
    .equ  MODE_FIQ, 0x11
    .equ  MODE_IRQ, 0x12
    .equ  MODE_SVC, 0x13
    .equ  MODE_ABT, 0x17
    .equ  MODE_UND, 0x1B
    .equ  MODE_SYS, 0x1F

    .equ  I_F_BIT,  0xC0

    .equ MASK_SVC_NUM, 0xFF000000

    .text
    .code 32

.global _Reset
_Reset:
@
@ Set up the Stack for Undefined mode
@
    LDR   r0, =__stack                    @ Read the stack address
    MSR   cpsr_c, #MODE_UND|I_F_BIT       @ switch to undef  mode
    MOV   sp,r0                           @ write the stack pointer
    SUB   r0, r0, #UND_STACK_SIZE         @ give stack space
@
@ Set up the Stack for abort mode
@
    MSR   cpsr_c, #MODE_ABT|I_F_BIT       @ Change to abort mode
    MOV   sp, r0                          @ write the stack pointer
    SUB   r0,r0, #ABT_STACK_SIZE          @ give stack space
@
@ Set up the Stack for FIQ mode
@
    MSR   cpsr_c, #MODE_FIQ|I_F_BIT       @ change to FIQ mode
    MOV   sp,r0                           @ write the stack pointer
    SUB   r0,r0, #FIQ_STACK_SIZE          @ give stack space
@
@ Set up the Stack for IRQ mode
@
    MSR   cpsr_c, #MODE_IRQ|I_F_BIT       @ change to IRQ mode
    MOV   sp,r0                           @ write the stack pointer
    SUB   r0,r0, #IRQ_STACK_SIZE          @ give stack space
@
@ Set up the Stack for SVC mode
@
    MSR   cpsr_c, #MODE_SVC|I_F_BIT       @ change to SVC mode
    MOV   sp,r0                           @ write the stack pointer
    SUB   r0,r0, #SVC_STACK_SIZE          @ give stack space
@
@ Set up the Stack for USer/System mode
@
    MSR   cpsr_c, #MODE_SYS|I_F_BIT       @ change to system mode
    MOV   sp,r0                           @ write the stack pointer

@ Invalidate and Enable Branch Prediction
    @ MOV     r0, #0
    @ MCR     p15, #0, r0, c7, c5, #6
    @ ISB
    @ MRC     p15, #0, r0, c1, c0, #0
    @ ORR     r0, r0, #0x00000800
    @ MCR     p15, #0, r0, c1, c0, #0

@
@ Enable Neon/VFP Co-Processor
@
    MRC p15, #0, r1, c1, c0, #2           @ r1 = Access Control Register
    ORR r1, r1, #(0xf << 20)              @ enable full access for p10,11
    MCR p15, #0, r1, c1, c0, #2           @ Access Control Register = r1
    MOV r1, #0
    MCR p15, #0, r1, c7, c5, #4           @flush prefetch buffer
    MOV r0,#0x40000000
    FMXR FPEXC, r0                        @ Set Neon/VFP Enable bit

@
@ Clear the BSS section here
@
Clear_Bss_Section:
    LDR   r0, =__bss_start__              @ Start address of BSS
    LDR   r1, =(__bss_end__ - 0x04)       @ End address of BSS
    MOV   r2, #0
Loop:
    STR   r2, [r0], #4                    @ Clear one word in BSS
    CMP   r0, r1
    BLE   Loop                            @ Clear till BSS end

@ jump into the C 'main' function
    ldr   r10, =kernel_init                @ Get the address of main
    mov   lr, pc                           @ Dummy return
    bx    r10                              @ Branch to main

@ jump into the C 'main' function
    ldr   r10, =kernel_main                @ Get the address of main
    mov   lr, pc                           @ Dummy return
    bx    r10                              @ Branch to main

ExitLoop:
    B .

    .globl SVC_Handler
SVC_Handler:
    STMFD    r13!, {r0-r1, r14}       @ Save context in SVC stack
    SUB      r13, r13, #0x4           @ Adjust the stack pointer
    LDR      r0, [r14, #-4]           @ R0 points to SWI instruction
    BIC      r0, r0, #MASK_SVC_NUM    @ Get the SWI number
    CMP      r0, #458752
    MRSEQ    r1, spsr                 @ Copy SPSR
    ORREQ    r1, r1, #0x1F            @ Change the mode to System
    MSREQ    spsr_cf, r1              @ Restore SPSR
    ADD      r13, r13, #0x4           @ Adjust the stack pointer
    LDMFD    r13!, {r0-r1, pc}^       @ Restore registers from IRQ stack

    .globl CP15VectorBaseAddrSet
CP15VectorBaseAddrSet:
    MCR     p15, #0, r0, c12, c0, #0
    DSB
    BX      lr

    .section .isr_vector
    .align 4
    .globl  __isr_vector
__isr_vector:
    LDR   pc, [pc,#24]       @ 0x00 Reset
    LDR   pc, [pc,#-8]       @ 0x04 Undefined Instruction
    LDR   pc, [pc,#24]       @ 0x08 Supervisor Call
    LDR   pc, [pc,#-8]       @ 0x0C Prefetch Abort
    LDR   pc, [pc,#-8]       @ 0x10 Data Abort
    LDR   pc, [pc,#-8]       @ 0x14 Not used
    LDR   pc, [pc,#-8]       @ 0x18 IRQ interrupt
    LDR   pc, [pc,#-8]       @ 0x1C FIQ interrupt
    .long  _Reset
    .long  0
    .long  SVC_Handler
    .long  0
    .long  0
    .long  0
    .long  0
    .long  0

    @ b . @ _Reset
    @ b . @ 0
    @ b . @ SVC_Handler
    @ b . @ 0
    @ b . @ 0
    @ b . @ 0
    @ b . @ 0
    @ b . @ 0
   
@
@ End of the file
@
    .end
    