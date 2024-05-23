/****************************************************************************
 *
 *   Copyright (c) 2024 IMProject Development Team. All rights reserved.
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

#include "caesar_cipher.h"

#include <string.h>

#include "utils.h"

#define MAX_SHIFT       (26U)
#define UPPER_A_ASCII   (65U)
#define LOWER_A_ASCII   (97U)

void
CaesarCipher_encrypt(char* msg, uint8_t shift) {
    const size_t length = strlen(msg);
    for (size_t i = 0U; i < length; ++i) {
        if (Utils_isAlpha(msg[i])) {
            uint8_t encrypted_char;
            if (Utils_isUpperChar(msg[i])) {
                encrypted_char = (((uint8_t)msg[i] + shift - UPPER_A_ASCII) % MAX_SHIFT) + UPPER_A_ASCII;
            } else {
                encrypted_char = (((uint8_t)msg[i] + shift - LOWER_A_ASCII) % MAX_SHIFT) + LOWER_A_ASCII;
            }
            msg[i] = (char)encrypted_char;
        }
    }
}

void
CaesarCipher_decrypt(char* msg, uint8_t shift) {
    const size_t length = strlen(msg);
    for (size_t i = 0U; i < length; ++i) {
        if (Utils_isAlpha(msg[i])) {
            uint8_t decrypted_char;
            if (Utils_isUpperChar(msg[i])) {
                decrypted_char = (((uint8_t)msg[i] - shift - UPPER_A_ASCII) % MAX_SHIFT) + UPPER_A_ASCII;
            } else {
                decrypted_char = (((uint8_t)msg[i] - shift - LOWER_A_ASCII) % MAX_SHIFT) + LOWER_A_ASCII;
            }
            msg[i] = (char)decrypted_char;
        }
    }
}
