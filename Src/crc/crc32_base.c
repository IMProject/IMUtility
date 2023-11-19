/****************************************************************************
 *
 *   Copyright (c) 2021 - 2023 IMProject Development Team. All rights reserved.
 *   Authors: Igor Misic <igy1000mb@gmail.com>
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

#include "crc32_base.h"

#include "bit_manipulation.h"

#define REFLECTED_INPUT_BITS_NUM    (8U)
#define REFLECTED_OUTPUT_BITS_NUM   (32U)

void
Crc32Base_tableCalculator(uint32_t polynomial, uint32_t crc_table[256]) {

    uint32_t top_bit = 0x80000000U;

    for (uint32_t dividend = 0U; dividend < 256U; ++dividend) {
        uint32_t residue = dividend << 24U;

        for (uint8_t bit = 0U; bit < 8U; bit++) {
            if (0U == (residue & top_bit)) {
                residue <<= 1U;
            } else {
                residue = (residue << 1U) ^ polynomial;
            }
        }

        crc_table[dividend] = residue;
    }
}

uint32_t
Crc32Base(
    const uint32_t crc_table[256],
    const uint8_t* crc_data_ptr,
    uint32_t crc_length,
    uint32_t crc_initial_value,
    uint32_t final_xor_value,
    bool reflected_output,
    bool reflected_input,
    bool final_xor) {

    uint32_t crc = crc_initial_value;
    const uint8_t* temp_data_ptr = crc_data_ptr;

    for (uint32_t counter = 0U; counter < crc_length; ++counter) {
        uint8_t temp;

        if (reflected_input) {
            temp = (uint8_t)BitManipulation_reflect(*temp_data_ptr, REFLECTED_INPUT_BITS_NUM);
        } else {
            temp = *temp_data_ptr;
        }

        crc = (crc << 8u) ^ crc_table[(uint8_t)((crc >> 24U) ^ temp)];
        ++temp_data_ptr;

    }

    if (reflected_output) {
        crc = BitManipulation_reflect(crc, REFLECTED_OUTPUT_BITS_NUM);
    }

    if (final_xor) {
        crc ^= final_xor_value;
    }
    return crc;
}
