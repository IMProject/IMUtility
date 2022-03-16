/****************************************************************************
 *
 *   Copyright (c) 2021 IMProject Development Team. All rights reserved.
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

#include "json.h"

#define MINIMAL_SIZE 2U // size of '{' or '}' + '\0'

bool
Json_startString(char* buffer, size_t size) {

    bool success = false;

    if (size >  MINIMAL_SIZE) {
        // cppcheck-suppress misra-c2012-17.7
        strcpy(&buffer[0], "{");
        success = true;
    }

    return success;
}

bool
Json_addData(char* buffer, size_t size, const char* key,  const char* value) {

    bool success = false;

    size_t index = strlen(buffer);
    size_t total_size = 0U;
    total_size += strlen("\"\":\"\"") + strlen(key) + strlen(value) + 1U;

    if (0 == strcmp(&buffer[index - 1U], "\"")) {
        // cppcheck-suppress misra-c2012-17.7
        strcpy(&buffer[index], ",");
        ++index;
    }

    if (total_size <= (size - index)) {

        // cppcheck-suppress misra-c2012-17.7
        strcpy(&buffer[index], "\"");
        index += strlen("\"");
        // cppcheck-suppress misra-c2012-17.7
        strcpy(&buffer[index], key);
        index += strlen(key);
        // cppcheck-suppress misra-c2012-17.7
        strcpy(&buffer[index], "\":\"");
        index += strlen("\":\"");
        // cppcheck-suppress misra-c2012-17.7
        strcpy(&buffer[index], value);
        index += strlen(value);
        // cppcheck-suppress misra-c2012-17.7
        strcpy(&buffer[index], "\"");

        success = true;
    }

    return success;
}
bool
Json_endString(char* buffer, size_t size) {

    bool success = false;

    size_t index = strlen(buffer);
    if (size >= (MINIMAL_SIZE + index)) {
        // cppcheck-suppress misra-c2012-17.7
        strcpy(&buffer[index], "}");
        success = true;
    }

    return success;
}
