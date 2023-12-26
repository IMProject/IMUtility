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

#include "utils.h"

#define MAX_UINT32_POW_10_EXPONENT 10U

bool
Utils_StringToUint32(const char* str, uint8_t str_length, uint32_t* integer) {
    bool success = true;
    bool check_overflow = false;
    uint8_t i = 0U;
    *integer = 0U;
    uint8_t length = str_length;

    if (str_length == MAX_UINT32_POW_10_EXPONENT) {
        check_overflow = true;
        length = str_length - 1U;
    }

    while ((length > i) && success) {

        if ((str[i] >= '0') && (str[i] <= '9')) {

            const int8_t digit = (int8_t)((int8_t)str[i] - (int8_t)'0');
            const uint8_t unsigned_power = length - (i + 1U);
            uint32_t result = 0U;
            success = Utils_QuickUint32Pow10(unsigned_power, &result);
            *integer += (uint32_t)digit * result;
            ++i;

        } else {
            success = false;
        }
    }

    if (check_overflow && success) {

        const uint8_t last_digit_index = MAX_UINT32_POW_10_EXPONENT - 1U;

        if ((str[last_digit_index] >= '0') && (str[last_digit_index] <= '9')) {

            const int8_t digit = (int8_t)((int8_t)str[last_digit_index] - (int8_t)'0');

            if ((*integer > (UINT32_MAX / 10U)) || ((*integer == (UINT32_MAX / 10U)) && ((uint32_t)digit > (UINT32_MAX % 10U)))) {
                //Overflow detected
                success = false;
            } else {
                *integer *= 10U;
                *integer += (uint32_t)digit;
            }
        } else {
            success = false;
        }
    }

    return success;
}

void
Utils_swapElements(byte_t* first, byte_t* second, uint32_t size) {
    byte_t* first_element = first;
    byte_t* second_element = second;
    uint32_t index = size;
    while ((index--) != 0U) {
        byte_t temp = first_element[index];
        first_element[index] = second_element[index];
        second_element[index] = temp;
    }
}

bool
Utils_QuickUint32Pow10(uint8_t exponent, uint32_t* result) {
    bool success = false;

    const uint32_t pow10[MAX_UINT32_POW_10_EXPONENT] = {
        1U, 10U, 100U, 1000U, 10000U,
        100000U, 1000000U, 10000000U, 100000000U, 1000000000U
    };

    if (exponent < MAX_UINT32_POW_10_EXPONENT) {
        *result = pow10[exponent];
        success = true;
    }

    return success;
}

void
Utils_Serialize8(byte_t* buf, uint8_t value) {
    buf[0] = (uint8_t)(value) & 0xFFu;
}

uint8_t
Utils_Deserialize8(const byte_t* buf) {
    uint8_t value = buf[0];
    return value;
}

void
Utils_Serialize16BE(byte_t* buf, uint16_t value) {
    buf[0] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[1] = (uint8_t)(value) & 0xFFu;
}

void
Utils_Serialize24BE(byte_t* buf, uint32_t value) {
    buf[0] = (uint8_t)(value >> 16u) & 0xFFu;
    buf[1] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[2] = (uint8_t)(value) & 0xFFu;
}

void
Utils_Serialize32BE(byte_t* buf, uint32_t value) {
    buf[0] = (uint8_t)(value >> 24u) & 0xFFu;
    buf[1] = (uint8_t)(value >> 16u) & 0xFFu;
    buf[2] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[3] = (uint8_t)(value) & 0xFFu;
}

void
Utils_SerializeBlobBE(byte_t* buf, const byte_t* src, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        buf[i] = src[i];
    }
}

uint16_t
Utils_Deserialize16BE(const byte_t* buf) {
    uint16_t value;
    value = (uint16_t)buf[0] << 8U;
    value |= (uint16_t)buf[1];
    return value;
}

uint32_t
Utils_Deserialize24BE(const byte_t* buf) {
    uint32_t value;
    value = (uint32_t)buf[0] << 16u;
    value |= (uint32_t)buf[1] << 8u;
    value |= (uint32_t)buf[2];
    return value;
}

uint32_t
Utils_Deserialize32BE(const byte_t* buf) {
    uint32_t value;
    value = (uint32_t)buf[0] << 24u;
    value |= (uint32_t)buf[1] << 16u;
    value |= (uint32_t)buf[2] << 8u;
    value |= (uint32_t)buf[3];
    return value;
}

void
Utils_DeserializeBlobBE(const byte_t* buf, byte_t* dst, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        dst[i] = buf[i];
    }
}

void
Utils_Serialize16LE(byte_t* buf, uint16_t value) {
    buf[1] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[0] = (uint8_t)(value) & 0xFFu;
}

void
Utils_Serialize24LE(byte_t* buf, uint32_t value) {
    buf[2] = (uint8_t)(value >> 16u) & 0xFFu;
    buf[1] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[0] = (uint8_t)(value) & 0xFFu;
}

void
Utils_Serialize32LE(byte_t* buf, uint32_t value) {
    buf[3] = (uint8_t)(value >> 24u) & 0xFFu;
    buf[2] = (uint8_t)(value >> 16u) & 0xFFu;
    buf[1] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[0] = (uint8_t)(value) & 0xFFu;
}

void
Utils_SerializeBlobLE(byte_t* buf, const byte_t* src, uint32_t size) {
    int32_t j = 0;
    for (int32_t i = ((int32_t)size - 1); i >= 0; --i) {
        buf[j] = src[i];
        ++j;
    }
}

uint16_t
Utils_Deserialize16LE(const byte_t* buf) {
    uint16_t value;
    value = (uint16_t)buf[1] << 8U;
    value |= (uint16_t)buf[0];
    return value;
}

uint32_t
Utils_Deserialize24LE(const byte_t* buf) {
    uint32_t value;
    value = (uint32_t)buf[2] << 16u;
    value |= (uint32_t)buf[1] << 8u;
    value |= (uint32_t)buf[0];
    return value;
}

uint32_t
Utils_Deserialize32LE(const byte_t* buf) {
    uint32_t value;
    value = (uint32_t)buf[3] << 24u;
    value |= (uint32_t)buf[2] << 16u;
    value |= (uint32_t)buf[1] << 8u;
    value |= (uint32_t)buf[0];
    return value;
}

void
Utils_DeserializeBlobLE(const byte_t* buf, byte_t* dst, uint32_t size) {
    int32_t  j = 0;
    for (int32_t i = ((int32_t)size - 1); i >= 0; --i) {
        dst[j] = buf[i];
        ++j;
    }
}
