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

void
Utils_Memcpy(uint8_t* to, const uint8_t* from, const uint32_t size) {
    for (uint32_t i = 0U; i < size; ++i) {
        to[i] = from[i];
    }
}

bool
Utils_QuickUint32Pow10(const uint8_t exponent, uint32_t* result) {
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
Utils_Strcpy(char* to, const char* from) {
    uint32_t i = 0U;
    while (from[i] != '\0') {
        to[i] = from[i];
        ++i;
    }

    to[i] = '\0';
}

bool
Utils_StringToUint32(const char* str, const uint8_t str_length, uint32_t* integer) {
    bool success = true;
    bool check_overflow = false;
    uint8_t i = 0U;
    *integer = 0U;
    uint8_t length = str_length;

    if (str_length == MAX_UINT32_POW_10_EXPONENT) {
        check_overflow = true;
        length = str_length - 1U;
    }

    while ((str[i] != '\0') && (length > i) && success) {

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

int32_t
Utils_Strncmp(const char* str1, const char* str2, const uint32_t num) {

    int32_t ret_val = 0;

    for (uint32_t i = 0U; (i < num) && (str1[i] != '\0') && (str2[i] != '\0'); ++i) {

        if (str1[i] != str2[i]) {
            ret_val = str1[i] - str2[i];
            break;
        }
    }

    return ret_val;
}

void
Utils_SwapElements(uint8_t* first, uint8_t* second, const uint32_t size) {
    uint8_t temp;
    uint8_t* first_element = first;
    uint8_t* second_element = second;
    uint32_t index = size;
    while ((index--) != 0U) {
        temp = first_element[index];
        first_element[index] = second_element[index];
        second_element[index] = temp;
    }
}

void
Utils_SerializeBlobBE(uint8_t* buf, const uint8_t* src, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        buf[i] = src[i];
    }
}

void
Utils_Serialize32BE(uint8_t* buf, uint32_t value) {
    buf[0] = (uint8_t)(value >> 24u) & 0xFFu;
    buf[1] = (uint8_t)(value >> 16u) & 0xFFu;
    buf[2] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[3] = (uint8_t)(value) & 0xFFu;
}

void
Utils_Serialize24BE(uint8_t* buf, uint32_t value) {
    buf[0] = (uint8_t)(value >> 16u) & 0xFFu;
    buf[1] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[2] = (uint8_t)(value) & 0xFFu;
}

void
Utils_Serialize16BE(uint8_t* buf, uint16_t value) {
    buf[0] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[1] = (uint8_t)(value) & 0xFFu;
}

void
Utils_Serialize8BE(uint8_t* buf, uint8_t value) {
    buf[0] = (uint8_t)(value) & 0xFFu;
}

void
Utils_DeserializeBlobBE(const uint8_t* buf, uint8_t* dst, uint32_t size) {
    for (uint32_t i = 0; i < size; i++) {
        dst[i] = buf[i];
    }
}

void
Utils_SerializeBlobLE(uint8_t* buf, const uint8_t* src, uint32_t size) {
    int32_t j = 0;
    for (int32_t i = ((int32_t)size - 1); i >= 0; --i) {
        buf[j] = src[i];
        ++j;
    }
}

void
Utils_DeserializeBlobLE(const uint8_t* buf, uint8_t* dst, uint32_t size) {
    int32_t  j = 0;
    for (int32_t i = ((int32_t)size - 1); i >= 0; --i) {
        dst[j] = buf[i];
        ++j;
    }
}

void
Utils_Deserialize32BE(const uint8_t* buf, uint32_t* value) {
    *value = (uint32_t)buf[0] << 24u;
    *value |= (uint32_t)buf[1] << 16u;
    *value |= (uint32_t)buf[2] << 8u;
    *value |= (uint32_t)buf[3];
}

void
Utils_Deserialize24BE(const uint8_t* buf, uint32_t* value) {
    *value = (uint32_t)buf[0] << 16u;
    *value |= (uint32_t)buf[1] << 8u;
    *value |= (uint32_t)buf[2];
}

void
Utils_Deserialize16BE(const uint8_t* buf, uint16_t* value) {
    *value = (uint16_t)buf[0] << 8U;
    *value |= (uint16_t)buf[1];
}

void
Utils_Deserialize8BE(const uint8_t* buf, uint8_t* value) {
    *value = buf[0];
}
