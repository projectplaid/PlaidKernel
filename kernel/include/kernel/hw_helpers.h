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

#ifndef __HW_HELPERS_H
#define __HW_HELPERS_H

#include <stdint.h>

//*****************************************************************************
//
// Macros for hardware access, both direct and via the bit-band region.
//
//*****************************************************************************
#define HWREG(x) (*((volatile uint32_t *)(x)))
#define HWREGH(x) (*((volatile unsigned short *)(x)))
#define HWREGB(x) (*((volatile unsigned char *)(x)))
#define HWREGBITW(x, b)                                                                            \
    HWREG(((unsigned int)(x)&0xF0000000) | 0x02000000 | (((unsigned int)(x)&0x000FFFFF) << 5) |    \
          ((b) << 2))
#define HWREGBITH(x, b)                                                                            \
    HWREGH(((unsigned int)(x)&0xF0000000) | 0x02000000 | (((unsigned int)(x)&0x000FFFFF) << 5) |   \
           ((b) << 2))
#define HWREGBITB(x, b)                                                                            \
    HWREGB(((unsigned int)(x)&0xF0000000) | 0x02000000 | (((unsigned int)(x)&0x000FFFFF) << 5) |   \
           ((b) << 2))

#define GENERAL__GET_BITS_FROM_U8(source, lsb, msb)                                                \
    ((uint8_t)((source) & ((uint8_t)(((uint8_t)(0xFF >> ((uint8_t)(7 - ((uint8_t)(msb)&7))))) &    \
                                     ((uint8_t)(0xFF << ((uint8_t)(lsb)&7)))))))

#define GENERAL__GET_BITS_FROM_U16(source, lsb, msb)                                               \
    ((uint16_t)((source) &                                                                         \
                ((uint16_t)(((uint16_t)(0xFFFF >> ((uint8_t)(15 - ((uint8_t)(msb)&15))))) &        \
                            ((uint16_t)(0xFFFF << ((uint8_t)(lsb)&15)))))))

#define GENERAL__GET_BITS_FROM_U32(source, lsb, msb)                                               \
    ((uint32_t)((source) &                                                                         \
                ((uint32_t)(((uint32_t)(0xFFFFFFFF >> ((uint8_t)(31 - ((uint8_t)(msb)&31))))) &    \
                            ((uint32_t)(0xFFFFFFFF << ((uint8_t)(lsb)&31)))))))

#endif // __HW_HELPERS_H