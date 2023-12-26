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

#include "misra_c_2012_doc.h"
#include "typedefs.h"

/**
 * @brief Converts a string to an unsigned 32-bit integer.
 *
 * This function converts a string to an unsigned 32-bit integer. The string does not need
 * to be null-terminated and requires the string length to be provided. The function returns
 * a boolean value indicating the success of the conversion and stores the converted integer
 * in the provided integer pointer.
 *
 * @param[in] str Pointer to the string to convert.
 * @param[in] str_length Length of the string.
 * @param[out] integer Pointer to store the converted unsigned 32-bit integer.
 *
 * @return true if the conversion was successful, false otherwise.
 */
bool Utils_StringToUint32(const char* str, uint8_t str_length, uint32_t* integer);

/**
 * @brief Swap two elements. Swap the content of two byte arrays of the same size.
 *
 * @param first[in/out] Pointer to the first array.
 * @param second[in/out] Pointer to the second array.
 * @param size[in] Size of the element. The number of bytes in each array.
 */
void Utils_swapElements(byte_t* first, byte_t* second, uint32_t size);

/**
 * @brief Quickly calculates 10 raised to the power of the given exponent
 *        and returns the result in a uint32_t.
 *
 * @param exponent[in] The exponent of 10 to calculate.
 * @param result[out] Pointer to where the result will be stored.
 * @return true If the exponent is valid and the result was calculated.
 * @return false If the exponent is invalid and the result could not be calculated.
 *
 * @note This function uses a lookup table for quick calculation of 10^exponent.
 *       The lookup table contains the precomputed values of 10^0 to 10^9.
 *       If the given exponent is greater than 9, the function returns false.
 */
bool Utils_QuickUint32Pow10(uint8_t exponent, uint32_t* result);

/**
 * @brief Serialize a 8-bit value into a buffer (for little-endian and big-endian).
 *
 * @param buf[out] Pointer to the buffer where the serialized value will be written.
 * @param value[in] The 8-bit value to be serialized.
 *
 */
void Utils_Serialize8(byte_t* buf, uint8_t value);

/**
 * @brief Deserializes a 8-bit value from a byte buffer (for little-endian and big-endian).
 *
 * @param buf[in] Pointer to the input byte buffer containing the serialized value.
 * @return The deserialized 8-bit value.
 *
 */
uint8_t Utils_Deserialize8(const byte_t* buf);

/**
 * @brief Serialize a 16-bit value in big-endian format into a buffer.
 *
 * @param buf[out] Pointer to the buffer where the serialized value will be written.
 * @param value[in] The 16-bit value to be serialized.
 *
 * @note The buffer must be at least 2 bytes long to accommodate the serialized value.
 */
void Utils_Serialize16BE(byte_t* buf, uint16_t value);

/**
 * @brief Serialize a 24-bit value in big-endian format into a buffer.
 *
 * @param buf[out] Pointer to the buffer where the serialized value will be written.
 * @param value[in] The 24-bit value to be serialized.
 *
 * @note The buffer must be at least 3 bytes long to accommodate the serialized value.
 */
void Utils_Serialize24BE(byte_t* buf, uint32_t value);

/**
 * @brief Serialize a 32-bit value in big-endian format into a buffer.
 *
 * @param buf[out] Pointer to the buffer where the serialized value will be written.
 * @param value[in] The 32-bit value to be serialized.
 *
 * @note The buffer must be at least 4 bytes long to accommodate the serialized value.
 */
void Utils_Serialize32BE(byte_t* buf, uint32_t value);

/**
 * @brief Serialize a blob of data in big-endian format.
 *
 * This function serializes a blob(binary large object) of data in big-endian format.
 *
 * @param[out] buf Pointer to the output buffer where serialized data will be written.
 * @param[in] src Pointer to the source data buffer to be serialized.
 * @param[in] size Number of bytes to be serialized.
 */
void Utils_SerializeBlobBE(byte_t* buf, const byte_t* src, uint32_t size);

/**
 * @brief Deserializes a 16-bit value from a big-endian byte buffer.
 *
 * @param buf[in] Pointer to the input byte buffer containing the serialized value.
 * @return The deserialized 16-bit value.
 *
 * @note The buffer must be at least 2 bytes long to accommodate the deserialized value.
 */
uint16_t Utils_Deserialize16BE(const byte_t* buf);

/**
 * @brief Deserializes a 24-bit value from a big-endian byte buffer.
 *
 * @param buf[in] Pointer to the input byte buffer containing the serialized value.
 * @return The deserialized 24-bit value.
 *
 * @note The buffer must be at least 3 bytes long to accommodate the deserialized value.
 */
uint32_t Utils_Deserialize24BE(const byte_t* buf);

/**
 * @brief Deserializes a 32-bit value from a big-endian byte buffer.
 *
 * @param buf[in] Pointer to the input byte buffer containing the serialized value.
 * @return The deserialized 32-bit value.
 *
 * @note The buffer must be at least 4 bytes long to accommodate the deserialized value.
 */
uint32_t Utils_Deserialize32BE(const byte_t* buf);

/**
 * @brief Deserializes a blob(binary large object) in big-endian format.
 *
 * @param[in] buf The source buffer containing the blob to deserialize.
 * @param[out] dst The destination buffer where the deserialized blob will be stored.
 * @param[in] size The size in bytes of the blob to deserialize.
 */
void Utils_DeserializeBlobBE(const byte_t* buf, byte_t* dst, uint32_t size);

/**
 * @brief Serialize a 16-bit value in little-endian format into a buffer.
 *
 * @param buf[out] Pointer to the buffer where the serialized value will be written.
 * @param value[in] The 16-bit value to be serialized.
 *
 * @note The buffer must be at least 2 bytes long to accommodate the serialized value.
 */
void Utils_Serialize16LE(byte_t* buf, uint16_t value);

/**
 * @brief Serialize a 24-bit value in little-endian format into a buffer.
 *
 * @param buf[out] Pointer to the buffer where the serialized value will be written.
 * @param value[in] The 24-bit value to be serialized.
 *
 * @note The buffer must be at least 3 bytes long to accommodate the serialized value.
 */
void Utils_Serialize24LE(byte_t* buf, uint32_t value);

/**
 * @brief Serialize a 32-bit value in little-endian format into a buffer.
 *
 * @param buf Pointer to the buffer where the serialized value will be written.
 * @param value[in] The 32-bit value to be serialized.
 *
 * @note The buffer must be at least 4 bytes long to accommodate the serialized value.
 */
void Utils_Serialize32LE(byte_t* buf, uint32_t value);

/**
 * @brief Serialize a blob of data in little-endian format.
 *
 * This function serializes a blob(binary large object) of data in little-endian format.
 *
 * @param[out] buf Pointer to the output buffer where serialized data will be written.
 * @param[in] src Pointer to the source data buffer to be serialized.
 * @param[in] size Number of bytes to be serialized.
 */
void Utils_SerializeBlobLE(byte_t* buf, const byte_t* src, uint32_t size);

/**
 * @brief Deserializes a 16-bit value from a little-endian byte buffer.
 *
 * @param buf[in] Pointer to the input byte buffer containing the serialized value.
 * @return The deserialized 16-bit value.
 *
 * @note The buffer must be at least 2 bytes long to accommodate the deserialized value.
 */
uint16_t Utils_Deserialize16LE(const byte_t* buf);

/**
 * @brief Deserializes a 24-bit value from a little-endian byte buffer.
 *
 * @param buf[in] Pointer to the input byte buffer containing the serialized value.
 * @return The deserialized 24-bit value.
 *
 * @note The buffer must be at least 3 bytes long to accommodate the deserialized value.
 */
uint32_t Utils_Deserialize24LE(const byte_t* buf);

/**
 * @brief Deserializes a 32-bit value from a little-endian byte buffer.
 *
 * @param buf[in] Pointer to the input byte buffer containing the serialized value.
 * @return The deserialized 32-bit value.
 *
 * @note The buffer must be at least 4 bytes long to accommodate the deserialized value.
 */
uint32_t Utils_Deserialize32LE(const byte_t* buf);

/**
 * @brief Deserializes a blob(binary large object) in little-endian format.
 *
 * @param[in] buf The source buffer containing the blob to deserialize.
 * @param[out] dst The destination buffer where the deserialized blob will be stored.
 * @param[in] size The size in bytes of the blob to deserialize.
 */
void Utils_DeserializeBlobLE(const byte_t* buf, byte_t* dst, uint32_t size);


#endif /* UTILITY_UTILS_H_ */
