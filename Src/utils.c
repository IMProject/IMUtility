/****************************************************************************
 *
 *   Copyright (c) 2021 - 2022 IMProject Development Team. All rights reserved.
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

#include <utils.h>
#include <math.h>

uint32_t
Utils_StringToUint32(const unsigned char* buf, const uint32_t lenght) {
    uint32_t integer = 0U;
    uint32_t i = 0U;

    while ((buf[i] != (unsigned char)'\0') && (lenght > i)) {
        integer += (uint32_t)(buf[i] - (unsigned char)'0') * (uint32_t)pow(10.0, (lenght - (i + 1U)));
        ++i;
    }
    return integer;
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
    buf[3] = (uint8_t)(value >> 0u) & 0xFFu;
}

void
Utils_Serialize24BE(uint8_t* buf, uint32_t value) {
    buf[0] = (uint8_t)(value >> 16u) & 0xFFu;
    buf[1] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[2] = (uint8_t)(value >> 0u) & 0xFFu;
}

void
Utils_Serialize16BE(uint8_t* buf, uint16_t value) {
    buf[0] = (uint8_t)(value >> 8u) & 0xFFu;
    buf[1] = (uint8_t)(value >> 0u) & 0xFFu;
}

void
Utils_Serialize8BE(uint8_t* buf, uint8_t value) {
    buf[0] = (uint8_t)(value >> 0u) & 0xFFu;
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
Utils_Deserialize32BE(uint8_t* buf, uint32_t* value) {
    *value = (uint32_t)(buf[0] << 24u);
    *value |= (uint32_t)(buf[1] << 16u);
    *value |= (uint32_t)(buf[2] << 8u);
    *value |= (uint32_t)(buf[3] << 0u);
}

void
Utils_Deserialize16BE(uint8_t* buf, uint16_t* value) {
    *value = (uint32_t)(buf[0] << 8u);
    *value |= (uint32_t)(buf[1] << 0u);
}

void
Utils_Deserialize8BE(uint8_t* buf, uint8_t* value) {
    *value = (uint32_t)(buf[0] << 0u);
}
