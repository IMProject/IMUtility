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

#ifndef UTILITY_UTILS_H_
#define UTILITY_UTILS_H_

#include "typedefs.h"

uint32_t Utils_StringToUint32(const char* buf, const uint32_t lenght);
void Utils_SwapElements(uint8_t* first, uint8_t* second, const uint32_t size);

// Big-endian
void Utils_SerializeBlobBE(uint8_t* buf, const uint8_t* src, uint32_t size);
void Utils_Serialize32BE(uint8_t* buf, uint32_t value);
void Utils_Serialize24BE(uint8_t* buf, uint32_t value);
void Utils_Serialize16BE(uint8_t* buf, uint16_t value);
void Utils_Serialize8BE(uint8_t* buf, uint8_t value);
void Utils_DeserializeBlobBE(const uint8_t* buf, uint8_t* dst, uint32_t size);
void Utils_Deserialize32BE(const uint8_t* buf, uint32_t* value);
void Utils_Deserialize16BE(const uint8_t* buf, uint16_t* value);
void Utils_Deserialize8BE(const uint8_t* buf, uint8_t* value);

// Little-endian
void Utils_SerializeBlobLE(uint8_t* buf, const uint8_t* src, uint32_t size);
void Utils_DeserializeBlobLE(const uint8_t* buf, uint8_t* dst, uint32_t size);


#endif /* UTILITY_UTILS_H_ */
