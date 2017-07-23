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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kernel/arch.h"
#include "kernel/board.h"
#include "kernel/debug.h"

extern void __libc_init_array();

void _init() {}

void kernel_main() {
    arch_init();

    board_init();

    __libc_init_array();

    kputs("Plaid kernel startup\r\n");

    char *str;
    str = (char *)malloc(15);
    if (str == 0) {
        printf("no memory!\r\n");
    } else {
        strcpy(str, "malloc");
        printf("dynamic alloc str = %s, Address = %02x\r\n", str, str);
    }

    const char *p = "world";
    printf("static alloc str = %s, Address = %02x\r\n", p, p);

    for (;;) {
    }
}