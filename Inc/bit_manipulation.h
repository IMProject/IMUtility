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

#ifndef UTILITY_BIT_MANIPULATION_H_
#define UTILITY_BIT_MANIPULATION_H_

#include "typedefs.h"

/**
 * @brief This function reflects the bits in data around the center bit.
 *
 * @param[in] data The input data to be reflected.
 * @param[in] n_bits The number of bits in the input data to be reflected.
 *
 * @return The reflected data.
 */
uint32_t BitManipulation_reflect(uint32_t data, uint8_t n_bits);

/**
 * @brief This function checks if the bit at nth position is set. Parameter n must be between 0 and 31.
 *
 * @param[in] data The input data.
 * @param[in] n The position of the bit in the input data that will be checked.
 * @param[out] *bit_set True if bit at nth position is set, otherwise false.
 *
 * @return True if function is successfully performed, otherwise false.
 */
bool BitManipulation_bitSet(uint32_t data, uint8_t n, bool* bit_set);

/**
 * @brief This function sets the bit at nth position and returns the result. Parameter n must be between 0 and 31.
 *
 * @param[in] data The input data.
 * @param[in] n The position of the bit in the input data that will be set.
 * @param[out] *out The result of the input data where the bit at the nth position is set.
 *
 * @return True if function is successfully performed, otherwise false.
 */
bool BitManipulation_setBit(uint32_t data, uint8_t n, uint32_t* out);

/**
 * @brief This function clears the bit at nth position and returns the result. Parameter n must be between 0 and 31.
 *
 * @param[in] data The input data.
 * @param[in] n The position of the bit in the input data that will be cleared.
 * @param[out] *out The result of the input data where the bit at the nth position is cleared.
 *
 * @return True if function is successfully performed, otherwise false.
 */
bool BitManipulation_clearBit(uint32_t data, uint8_t n, uint32_t* out);

/**
 * @brief This function toggles the bit at nth position and returns the result. Parameter n must be between 0 and 31.
 *
 * @param[in] data The input data.
 * @param[in] n The position of the bit in the input data that will be toggled.
 * @param[out] *out The result of the input data where the bit at the nth position is toggled.
 *
 * @return True if function is successfully performed, otherwise false.
 */
bool BitManipulation_toggleBit(uint32_t data, uint8_t n, uint32_t* out);

#endif /* UTILITY_BIT_MANIPULATION_H_ */
