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

#include "vernam_cipher.h"

#include <string.h>

#include "utils.h"

#define UPPER_A_ASCII   (65)
#define LOWER_A_ASCII   (97)
#define NUM_OF_ALPHA    (26)

bool
VernamCipher_encrypt(char* msg, const char* key, int32_t key_length) {
    bool status = false;
    const size_t msg_length = strlen(msg);
    if ((int32_t)msg_length == key_length) {
        for (int32_t i = 0; i < key_length; ++i) {
            if (Utils_isAlpha(msg[i])) {
                int8_t c;
                if (Utils_isLowerChar(key[i])) {
                    c = LOWER_A_ASCII;
                } else {
                    c = UPPER_A_ASCII;
                }

                int32_t ascii_val;
                if (Utils_isUpperChar(msg[i])) {
                    ascii_val = UPPER_A_ASCII;
                } else {
                    ascii_val = LOWER_A_ASCII;
                }

                int32_t temp = (((int8_t)msg[i] - ascii_val + (int8_t)key[i] - c) % NUM_OF_ALPHA);
                int32_t cipher = temp + ascii_val;
                msg[i] = (char)cipher;
            }
        }
        status = true;
    }
    return status;
}

bool
VernamCipher_decrypt(char* msg, const char* key, int32_t key_length) {
    bool status = false;
    const size_t msg_length = strlen(msg);
    if ((int32_t)msg_length == key_length) {
        for (int32_t i = 0; i < key_length; ++i) {
            if (Utils_isAlpha(msg[i])) {
                int8_t c;
                if (Utils_isLowerChar(key[i])) {
                    c = LOWER_A_ASCII;
                } else {
                    c = UPPER_A_ASCII;
                }

                int32_t ascii_val;
                if (Utils_isUpperChar(msg[i])) {
                    ascii_val = UPPER_A_ASCII;
                } else {
                    ascii_val = LOWER_A_ASCII;
                }

                int32_t cipher = ((msg[i] - ascii_val) - (key[i] - c));
                cipher = (cipher < 0) ? (cipher + NUM_OF_ALPHA + ascii_val) : (cipher + ascii_val);
                msg[i] = (char)cipher;
            }
        }
        status = true;
    }
    return status;
}
