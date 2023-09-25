/****************************************************************************
 *
 *   Copyright (c) 2023 IMProject Development Team. All rights reserved.
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

#ifndef UTILITY_CRC16_BASE_H_
#define UTILITY_CRC16_BASE_H_

#include "typedefs.h"

/**
 * @brief Calculates a lookup table for a given 16-bit polynomial.
 *
 * This function generates a lookup table for use in calculating an 16-bit CRC
 * checksum with the specified polynomial. The resulting table is stored in the
 * 'crc_table' array, which must be a pre-allocated array of 256 bytes.
 *
 * @param[in] polynomial The 16-bit polynomial to use for the CRC calculation.
 * @param[out] crc_table A pointer to the pre-allocated array that will hold the
 *                  resulting lookup table.
 */
void Crc16Base_tableCalculator(uint16_t polynomial, uint16_t crc_table[256]);

/**
 * @brief Calculates an 16-bit CRC checksum for a block of data.
 *
 * This function calculates an 16-bit CRC checksum for the given block of data
 * using the specified parameters. The 'crc_table' parameter should be a lookup
 * table generated using the 'CRC16Base_TableCalculator' function. The 'crc_data_ptr'
 * parameter should be a pointer to the block of data to calculate the checksum for.
 * The 'crc_length' parameter is the length of the data block in bytes. The 'crc_initial_value'
 * parameter is the initial value of the checksum calculation. The 'xor_value' parameter
 * is a value that is XORed with the final checksum result. The 'reflected_output' parameter
 * specifies whether the final checksum value should be bit-reflected. The 'reflected_input'
 * parameter specifies whether the input data should be bit-reflected before the checksum calculation.
 * The 'final_xor' parameter specifies whether the final checksum value should be XORed with 'xor_value'.
 *
 * @param[in] crc_table The lookup table to use for the CRC calculation.
 * @param[in] crc_data_ptr A pointer to the data block to calculate the checksum for.
 * @param[in] crc_length The length of the data block in bytes.
 * @param[in] crc_initial_value The initial value of the checksum calculation.
 * @param[in] xor_value The value to XOR with the final checksum result.
 * @param[in] reflected_output Whether the final checksum value should be bit-reflected.
 * @param[in] reflected_input Whether the input data should be bit-reflected before the checksum calculation.
 * @param[in] final_xor Whether the final checksum value should be XORed with 'xor_value'.
 *
 * @return The calculated CRC checksum.
 */
uint16_t Crc16Base(
    const uint16_t crc_table[256],
    const uint8_t* crc_data_ptr,
    uint32_t crc_length,
    uint16_t crc_initial_value,
    uint16_t final_xor_value,
    bool reflected_output,
    bool reflected_input,
    bool final_xor
);

#endif /* UTILITY_CRC16_BASE_H_ */
