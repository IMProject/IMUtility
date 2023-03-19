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

#ifndef UTILITY_UTILS_H_
#define UTILITY_UTILS_H_

#include "typedefs.h"

bool Utils_QuickUint32Pow10(const uint8_t exponent, uint32_t* result);

/**
 * @brief Converts a string to an unsigned 32-bit integer.
 *
 * This function converts a string to an unsigned 32-bit integer. The string does not need
 * to be null-terminated and requires the string length to be provided. The function returns
 * a boolean value indicating the success of the conversion and stores the converted integer
 * in the provided integer pointer.
 *
 * @param[in] str Pointer to the string to convert.
   @param[in] str_length Length of the string.
   @param[out] integer Pointer to store the converted unsigned 32-bit integer.

   @return true if the conversion was successful, false otherwise.
 */

bool Utils_StringToUint32(const char* str, const uint8_t str_length, uint32_t* integer);
void Utils_SwapElements(byte_t* first, byte_t* second, const uint32_t size);

// Big-endian
void Utils_SerializeBlobBE(byte_t* buf, const byte_t* src, uint32_t size);
void Utils_Serialize32BE(byte_t* buf, uint32_t value);
void Utils_Serialize24BE(byte_t* buf, uint32_t value);
void Utils_Serialize16BE(byte_t* buf, uint16_t value);
void Utils_Serialize8BE(byte_t* buf, uint8_t value);
void Utils_DeserializeBlobBE(const byte_t* buf, byte_t* dst, uint32_t size);
uint32_t Utils_Deserialize32BE(const byte_t* buf);
uint32_t Utils_Deserialize24BE(const byte_t* buf);
uint16_t Utils_Deserialize16BE(const byte_t* buf);
uint8_t Utils_Deserialize8BE(const byte_t* buf);

// Little-endian
void Utils_SerializeBlobLE(byte_t* buf, const byte_t* src, uint32_t size);
void Utils_DeserializeBlobLE(const byte_t* buf, byte_t* dst, uint32_t size);

uint32_t Utils_BitReflect(uint32_t data, uint8_t n_bits);

#endif /* UTILITY_UTILS_H_ */
