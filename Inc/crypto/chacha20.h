/****************************************************************************
 *
 *   Copyright (c) 2024 IMProject Development Team. All rights reserved.
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

#ifndef UTILITY_CHACHA20_H_
#define UTILITY_CHACHA20_H_

#include "typedefs.h"

#define CHACHA20_KEY_SIZE           32U
#define CHACHA20_NONCE_SIZE         12U

/**
 * @brief Encrypts or decrypts a plaintext message using the ChaCha20 stream cipher.
 *
 * This function encrypts or decrypts a plaintext message using the ChaCha20 stream cipher algorithm.
 * ChaCha20 is a symmetric encryption algorithm that operates on 64-byte blocks, producing a stream of keystream bytes
 * which are XORed with the plaintext to produce the ciphertext, or vice versa.
 *
 * @param[in] plaintext Pointer to the plaintext message to be encrypted or decrypted.
 * @param[in] plaintext_len Length of the plaintext message in bytes.
 * @param[in] key Array containing the key for encryption/decryption. It must be of size CHACHA20_KEY_SIZE bytes.
 * @param[in] nonce Array containing the nonce value. It must be of size CHACHA20_NONCE_SIZE bytes.
 * @param[in] inc Initial block counter value (usually starts from 0 and incremented for each block).
 * @param[out] result Pointer to the buffer where the resulting encrypted or decrypted message will be stored.
 *                          The buffer must have enough space to hold the resulting ciphertext or plaintext, which is
 *                          the same size as the plaintext message.
 *
 * @note The length of the key must be CHACHA20_KEY_SIZE (32 bytes).
 * @note The length of the nonce must be CHACHA20_NONCE_SIZE (12 bytes).
 * @note The encrypted_message buffer must have enough space to accommodate the resulting ciphertext or plaintext,
 *       which will be the same size as the plaintext message.
 *
 * @warning This function does not perform any bounds checking on the input buffers. It is the responsibility of the
 *          caller to ensure that the buffers are valid and have the correct sizes.
 */

void Chacha20_crypt(const byte_t* plaintext,
                    uint32_t plaintext_len,
                    const byte_t key[CHACHA20_KEY_SIZE],
                    const byte_t nonce[CHACHA20_NONCE_SIZE],
                    uint32_t inc,
                    byte_t* result);

#endif /* UTILITY_CHACHA20_H_ */
