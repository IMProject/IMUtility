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

#include "utils.h"

#define MINIMAL_SIZE 2U // size of '{' or '}' + '\0'

bool
Json_startString(char* buffer, size_t buffer_size) {
    bool success = false;

    if (buffer_size >= MINIMAL_SIZE) {
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case, therefore it is not used
        strcpy(&buffer[0], "{");
        success = true;
    }

    return success;
}

bool
Json_addData(char* buffer, size_t buffer_size, const char* key, const char* value) {
    bool success = false;

    size_t index = strlen(buffer);
    size_t total_size = strlen("\"\":\"\"") + strlen(key) + strlen(value) + 1U;

    if (0 == strcmp(&buffer[index - 1U], "\"")) {
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case, therefore it is not used
        strcpy(&buffer[index], ",");
        ++index;
    }

    if ((total_size + index) <= buffer_size) {
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case, therefore it is not used
        strcpy(&buffer[index], "\"");
        index += strlen("\"");
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case, therefore it is not used
        /* -E> compliant MC3R1.R19.1 1 Overlap will not happen because of the check in if statement. */
        strcpy(&buffer[index], key);
        index += strlen(key);
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case, therefore it is not used
        strcpy(&buffer[index], "\":\"");
        index += strlen("\":\"");
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case, therefore it is not used
        /* -E> compliant MC3R1.R19.1 1 Overlap will not happen because of the check in if statement. */
        strcpy(&buffer[index], value);
        index += strlen(value);
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case, therefore it is not used
        strcpy(&buffer[index], "\"");

        success = true;
    }

    return success;
}

bool
Json_endString(char* buffer, size_t buffer_size) {
    bool success = false;

    size_t index = strlen(buffer);
    if (buffer_size >= (MINIMAL_SIZE + index)) {
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case, therefore it is not used
        strcpy(&buffer[index], "}");
        success = true;
    }

    return success;
}

bool
Json_findByKey(const char* buffer, size_t buffer_size, const char* key, char* value, size_t max_value_size) {
    bool success = false;

    size_t key_size = strlen(key);
    uint32_t max_search_size = 0U;
    uint32_t index;

    if (buffer_size > key_size) {
        max_search_size = (uint32_t)(buffer_size - key_size);
    }

    for (index = 0U; index < max_search_size; ++index) {

        /* -E> compliant MC3R1.R21.18 2 strncmp is guarded in for loop condition to not go out of buffer boundaries
        by calculating max_search_size from buffer size and key size */
        if (0 == strncmp(&buffer[index], key, key_size)) {

            if (buffer[index + key_size] == '"') {
                success = true;
            }

            break;
        }
    }

    if (success) {

        success = false;
        for (index += (uint32_t)(key_size + 1U); index < buffer_size; ++index) {

            if (buffer[index] == '"') {
                break;
            }
        }

        size_t value_size = 0;
        ++index;

        while ((index < buffer_size) && (value_size < max_value_size)) {
            value[value_size] = buffer[index];

            if (buffer[index] == '"') {
                value[value_size] = '\0';
                success = true;
                break;
            }

            ++value_size;
            ++index;
        }
    }

    return success;
}
