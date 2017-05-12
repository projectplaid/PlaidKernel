#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kernel/arch.h"
#include "kernel/board.h"
#include "kernel/debug.h"

void kernel_init(void) { __libc_init_array(); }

void kernel_main() {
    extern uint32_t __HeapBase;
    arch_init();

    board_init();

    kputs("Plaid kernel startup\r\n");

    char *str;
    str = (char *)malloc(15);
    if (str == 0) {
        printf("no memory!\r\n");
    } else {
        str[0] = 'm';
        str[1] = 'a';
        str[2] = 'l';
        str[3] = 'l';
        str[4] = 'o';
        str[5] = 'c';
        str[6] = '\0';
        printf("dynamic malloc'ed str = %s, Address = %d\r\n", str, str);
    }

    char *p = "world";
    printf("static str = %s, Address = %d\r\n", p, p);

    for (;;) {
    }
}