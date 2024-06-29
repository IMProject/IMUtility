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

// Chacha20 definition document : https://datatracker.ietf.org/doc/html/rfc8439

#include "chacha20.h"

#include "bit_manipulation.h"
#include "utils.h"

#define KEY_STREAM_SIZE 64U
#define BLOCK_SIZE      64U

// Hex representation of Magic number: "expand 32-byte k"
#define CHACHA_MAGIC_NUMBER_PART_1 (0x61707865U)
#define CHACHA_MAGIC_NUMBER_PART_2 (0x3320646eU)
#define CHACHA_MAGIC_NUMBER_PART_3 (0x79622d32U)
#define CHACHA_MAGIC_NUMBER_PART_4 (0x6b206574U)

#define ARRAY_64_ZERO_VALUES { \
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, \
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, \
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, \
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, \
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, \
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, \
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, \
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U  \
    }

#define CHACHA20_ROUNDS 10U // 20 inner ChaCha20 rounds, 2 rounds per loop

static inline void
QuarterRound(uint32_t* a, uint32_t* b, uint32_t* c, uint32_t* d) {
    *a += *b;
    *d = BitManipulation_rotl32(*d ^ *a, 16);
    *c += *d;
    *b = BitManipulation_rotl32(*b ^ *c, 12);
    *a += *b;
    *d = BitManipulation_rotl32(*d ^ *a, 8);
    *c += *d;
    *b = BitManipulation_rotl32(*b ^ *c, 7);
}

static void
Block(const byte_t key[CHACHA20_KEY_SIZE], uint32_t counter, const byte_t nonce[CHACHA20_NONCE_SIZE],
      byte_t out[KEY_STREAM_SIZE]) {

    uint32_t x0  = CHACHA_MAGIC_NUMBER_PART_1;
    uint32_t x1  = CHACHA_MAGIC_NUMBER_PART_2;
    uint32_t x2  = CHACHA_MAGIC_NUMBER_PART_3;
    uint32_t x3  = CHACHA_MAGIC_NUMBER_PART_4;
    uint32_t x4  = Utils_deserialize32LE(&key[0]);
    uint32_t x5  = Utils_deserialize32LE(&key[4]);
    uint32_t x6  = Utils_deserialize32LE(&key[8]);
    uint32_t x7  = Utils_deserialize32LE(&key[12]);
    uint32_t x8  = Utils_deserialize32LE(&key[16]);
    uint32_t x9  = Utils_deserialize32LE(&key[20]);
    uint32_t x10 = Utils_deserialize32LE(&key[24]);
    uint32_t x11 = Utils_deserialize32LE(&key[28]);
    uint32_t x12 = counter;
    uint32_t x13 = Utils_deserialize32LE(&nonce[0]);
    uint32_t x14 = Utils_deserialize32LE(&nonce[4]);
    uint32_t x15 = Utils_deserialize32LE(&nonce[8]);

    for (uint8_t i = 0U; i < CHACHA20_ROUNDS; ++i) {
        QuarterRound(&x0, &x4,  &x8, &x12);
        QuarterRound(&x1, &x5,  &x9, &x13);
        QuarterRound(&x2, &x6, &x10, &x14);
        QuarterRound(&x3, &x7, &x11, &x15);
        QuarterRound(&x0, &x5, &x10, &x15);
        QuarterRound(&x1, &x6, &x11, &x12);
        QuarterRound(&x2, &x7,  &x8, &x13);
        QuarterRound(&x3, &x4,  &x9, &x14);
    }

    x0  += CHACHA_MAGIC_NUMBER_PART_1;
    x1  += CHACHA_MAGIC_NUMBER_PART_2;
    x2  += CHACHA_MAGIC_NUMBER_PART_3;
    x3  += CHACHA_MAGIC_NUMBER_PART_4;
    x4  += Utils_deserialize32LE(&key[0]);
    x5  += Utils_deserialize32LE(&key[4]);
    x6  += Utils_deserialize32LE(&key[8]);
    x7  += Utils_deserialize32LE(&key[12]);
    x8  += Utils_deserialize32LE(&key[16]);
    x9  += Utils_deserialize32LE(&key[20]);
    x10 += Utils_deserialize32LE(&key[24]);
    x11 += Utils_deserialize32LE(&key[28]);
    x12 += counter;
    x13 += Utils_deserialize32LE(&nonce[0]);
    x14 += Utils_deserialize32LE(&nonce[4]);
    x15 += Utils_deserialize32LE(&nonce[8]);

    /* -E> compliant MC3R1.R18.6 16 automatic storage pointed with "out" is not copied to values from this function */
    Utils_serialize32LE(&out[0],  x0);
    Utils_serialize32LE(&out[4],  x1);
    Utils_serialize32LE(&out[8],  x2);
    Utils_serialize32LE(&out[12], x3);
    Utils_serialize32LE(&out[16], x4);
    Utils_serialize32LE(&out[20], x5);
    Utils_serialize32LE(&out[24], x6);
    Utils_serialize32LE(&out[28], x7);
    Utils_serialize32LE(&out[32], x8);
    Utils_serialize32LE(&out[36], x9);
    Utils_serialize32LE(&out[40], x10);
    Utils_serialize32LE(&out[44], x11);
    Utils_serialize32LE(&out[48], x12);
    Utils_serialize32LE(&out[52], x13);
    Utils_serialize32LE(&out[56], x14);
    Utils_serialize32LE(&out[60], x15);
}

void
Chacha20_crypt(const byte_t* plaintext,
               uint32_t plaintext_len,
               const byte_t key[CHACHA20_KEY_SIZE],
               const byte_t nonce[CHACHA20_NONCE_SIZE],
               uint32_t inc,
               byte_t* result) {

    uint32_t blocks = plaintext_len / BLOCK_SIZE;
    uint32_t remaining_bytes = plaintext_len % BLOCK_SIZE;

    for (uint32_t j = 0; j < blocks; ++j) {
        byte_t key_stream[KEY_STREAM_SIZE] = ARRAY_64_ZERO_VALUES;
        Block(key, j + inc, nonce, key_stream);

        for (uint8_t i = 0; i < BLOCK_SIZE; ++i) {
            result[(j * BLOCK_SIZE) + i] = plaintext[(j * BLOCK_SIZE) + i] ^ key_stream[i];
        }
    }

    if (0U != remaining_bytes) {
        byte_t key_stream[KEY_STREAM_SIZE] = ARRAY_64_ZERO_VALUES;
        Block(key, blocks + inc, nonce, key_stream);

        for (uint32_t i = 0; i < remaining_bytes; ++i) {
            result[(blocks * BLOCK_SIZE) + i] = plaintext[(blocks * BLOCK_SIZE) + i] ^ key_stream[i];
        }
    }
}
