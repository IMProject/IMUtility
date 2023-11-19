/****************************************************************************
 *
 *   Copyright (c) 2023 IMProject Development Team. All rights reserved.
 *   Authors: Juraj Ciberlin <jciberlin1@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name IMProject nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "bit_manipulation.h"

#define MAX_BIT_SHIFT (31U)

uint32_t
BitManipulation_reflect(uint32_t data, uint8_t n_bits) {
    uint32_t reflection = 0u;
    uint32_t temp_data = data;

    /*
    * Reflect the data around the center bit.
    */
    for (uint8_t bit = 0u; bit < n_bits; ++bit) {
        /*
        * If the LSB bit is set, set the reflection of it.
        */
        if (1u == (temp_data & 1u) ) {
            /* -E> compliant MC3R1.R12.2 1 The shift count is granted to be between 0 and 31 due to bit masking. */
            reflection |= (uint32_t)((uint32_t)1U << (0x1FU & ((n_bits - 1U) - bit)));
        }

        temp_data = (temp_data >> 1u);
    }

    return reflection;
}

bool
BitManipulation_bitSet(uint32_t data, uint8_t n, bool* bit_set) {
    bool status = false;
    if (n <= MAX_BIT_SHIFT) {
        /* -E> compliant MC3R1.R12.2 1 Right hand operand of shift expression is between 0 and 31 due to previous IF statement. */
        uint32_t temp = (uint32_t)1U << n;
        *bit_set = ((data & temp) != 0U);
        status = true;
    }
    return status;
}

bool
BitManipulation_setBit(uint32_t data, uint8_t n, uint32_t* out) {
    bool status = false;
    if (n <= MAX_BIT_SHIFT) {
        /* -E> compliant MC3R1.R12.2 1 Right hand operand of shift expression is between 0 and 31 due to previous IF statement. */
        *out = (data | ((uint32_t)1U << n));
        status = true;
    }
    return status;
}

bool
BitManipulation_clearBit(uint32_t data, uint8_t n, uint32_t* out) {
    bool status = false;
    if (n <= MAX_BIT_SHIFT) {
        /* -E> compliant MC3R1.R12.2 1 Right hand operand of shift expression is between 0 and 31 due to previous IF statement. */
        *out = (data & (~((uint32_t)1U << n)));
        status = true;
    }
    return status;
}

bool
BitManipulation_toggleBit(uint32_t data, uint8_t n, uint32_t* out) {
    bool status = false;
    if (n <= MAX_BIT_SHIFT) {
        /* -E> compliant MC3R1.R12.2 1 Right hand operand of shift expression is between 0 and 31 due to previous IF statement. */
        *out = (data ^ ((uint32_t)1U << n));
        status = true;
    }
    return status;
}
