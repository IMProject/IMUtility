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

#ifndef UTILITY_CRC8_ROHC_H_
#define UTILITY_CRC8_ROHC_H_

#include "typedefs.h"

/**
 * @brief Calculates the CRC-8 checksum using the MAXIM polynomial (0x07).
 *
 * This function calculates the CRC-8 checksum of the given data using the MAXIM
 * polynomial (0x07). The calculation is performed using a lookup table for
 * efficiency.
 *
 * @param[in] crc_data_ptr A pointer to the block of data to calculate the checksum for.
 * @param[in] crc_length The length of the data block in bytes.
 * @param[in] final_crc Set the flag to 'true' if it is the last or only operation, and 'false' for data chunks.
 * @param[in] last_crc_ptr Pointer to the last CRC value for data chunks. Shall be set to NULL_PTR if it is the first or only operation.
 *
 * @return The calculated CRC-8 checksum.
 */
uint8_t Crc8_rohc(
    const uint8_t* crc_data_ptr,
    uint32_t crc_length,
    bool final_crc,
    const uint8_t* last_crc_ptr
);

#endif /* UTILITY_CRC8_ROHC_H_ */
