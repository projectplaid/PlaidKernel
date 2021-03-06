/****************************************************************************/
/*  AM335x.lds                                                              */
/*  Copyright (c) 2014  Texas Instruments Incorporated                      */
/*  Author: Rafael de Souza                                                 */
/*                                                                          */
/*    Description: This file is a sample linker command file that can be    */
/*                 used for linking programs built with the GCC compiler    */
/*                 and running the resulting .out file on an AM335x device. */
/*                 Use it as a guideline.  You will want to                 */
/*                 change the memory layout to match your specific          */
/*                 target system.  You may want to change the allocation    */
/*                 scheme according to the size of your program.            */
/*                                                                          */
/****************************************************************************/

MEMORY
{
    DDR0 :     o = 0x00000000,  l =  0x8000000 /* 128MB */ /* 0x40000000 1GB external DDR Bank 0 */
}

HEAPSIZE = 0x4000;
STACKSIZE = 0x4000;

/* Linker script to place sections and symbol values. Should be used together
 * with other linker script that defines memory region DDR0.
 * It references following symbols, which must be defined in code:
 *   Entry : Entry of reset handler
 * 
 * It defines following symbols, which code can use without definition:
 *   __exidx_start
 *   __exidx_end
 *   __etext
 *   __data_start__
 *   __preinit_array_start
 *   __preinit_array_end
 *   __init_array_start
 *   __init_array_end
 *   __fini_array_start
 *   __fini_array_end
 *   __data_end__
 *   __bss_start__
 *   __bss_end__
 *   __end__
 *   end
 *   __HeapLimit
 *   __HeapBase        - To be compatible with Linaro's semihosting support 
 *   __StackLimit
 *   __StackTop
 *   __StackBase    - To be compatible with Linaro's semihosting support 
 *   __stack
 */
ENTRY(_Reset)

SECTIONS
{
    .rsthand :
    {
        . = ALIGN(0x10000);
        __vector_start = .;
        KEEP(*(.isr_vector))
        __vector_end = .;
        *start.S.obj (.text)
    } > DDR0
    
    . = ALIGN(4);
    .text :
    {
        *(.text*)

        KEEP(*(.init))
        KEEP(*(.fini))

        /* .ctors */
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)

        /* .dtors */
         *crtbegin.o(.dtors)
         *crtbegin?.o(.dtors)
         *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
         *(SORT(.dtors.*))
         *(.dtors)

        *(.rodata*)

        KEEP(*(.eh_frame*))
    } > DDR0

    .ARM.extab : 
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > DDR0

    __exidx_start = .;
    .ARM.exidx :
    {
        *(.ARM.exidx* .gnu.linkonce.armexidx.*)
    } > DDR0
    __exidx_end = .;

    .data :
    {
        . = ALIGN(4);
        __data_start__ = .;
        *(vtable)
        *(.data*)

        . = ALIGN(4);
        /* preinit data */
        PROVIDE (__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE (__preinit_array_end = .);

        . = ALIGN(4);
        /* init data */
        PROVIDE (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE (__init_array_end = .);

        . = ALIGN(4);
        /* finit data */
        PROVIDE (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array))
        PROVIDE (__fini_array_end = .);

        . = ALIGN(4);
        /* All data end */
        __data_end__ = .;
    } > DDR0

    .bss :
    {
        . = ALIGN(4);
        __bss_start__ = .;
        *(.bss*)
        *(COMMON)
        __bss_end__ = .;
    } > DDR0
    
    .heap (NOLOAD):
    {
        /* The line below can be used to FILL the memory with a known value and
         * debug any stack overruns. For this to work, the specifier (NOLOAD) above 
         * must be removed at the expense of an increase in the output binary size */
        FILL(0xDEADBEEF)
        . = ALIGN(4);
        __end__ = .;
        end = __end__;
        /* The line below created to be compatible with Linaro's semihosting support */
        __HeapBase = __end__; 
        *(.heap*)
        . = . + HEAPSIZE;
        __HeapLimit = .; 
    } > DDR0

    /* .stack section doesn't contain any symbols. It is only
     * used for linker to calculate size of stack sections, and assign
     * values to stack symbols later */
    .stack (NOLOAD):
    {
        /* The line below can be used to FILL the memory with a known value and
         * debug any stack overruns. For this to work, the specifier (NOLOAD) above 
         * must be removed at the expense of an increase in the output binary size */
        FILL(0xBAD0BAD0)
        . = ALIGN(4);
        __StackLimit = . ;
        *(.stack*)
        . = . + STACKSIZE;
        __StackTop = . ;
        /* The line below created to be compatible with Linaro's semihosting support */
        __StackBase = . ;
    } > DDR0
    PROVIDE(__stack = __StackTop);

}
/**************************************************************************/
