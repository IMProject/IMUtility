/****************************************************************************
 *
 *   Copyright (c) 2021-2023 IMProject Development Team. All rights reserved.
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

#ifndef UTILITY_JSON_H_
#define UTILITY_JSON_H_

#include <string.h>

#include "typedefs.h"

/**
 * @brief Start a JSON string in the given buffer
 *
 * This function starts a JSON string in the provided buffer by copying the opening brace character "{"
 * to the beginning of the buffer. The function will set the success flag to true if the buffer size
 * is greater than or equal to the minimum size required to hold the opening brace character.
 *
 * @param buffer The buffer to write the JSON string to
 * @param buffer_size The size of the buffer in bytes
 * @return Returns true if the JSON string was successfully started, false otherwise
 */
bool Json_startString(char* buffer, size_t buffer_size);

/**
 * @brief Add key-value pair to JSON string in the given buffer
 *
 * This function adds a key-value pair to the JSON string in the provided buffer by concatenating the
 * key and value strings with their respective formatting characters to the end of the buffer. The
 * function will set the success flag to true if the resulting string size does not exceed the buffer
 * size and if the key-value pair is successfully added to the JSON string.
 *
 * @param buffer The buffer to write the JSON string to
 * @param buffer_size The size of the buffer in bytes
 * @param key The key string to add to the JSON object
 * @param value The value string to add to the JSON object
 * @return Returns true if the key-value pair was successfully added to the JSON string, false otherwise
 */
bool Json_addData(char* buffer, size_t buffer_size, const char* key, const char* value);

/**
 * @brief End a JSON string in the given buffer
 *
 * This function adds the closing brace character to the end of the JSON string in the provided buffer.
 * The function will set the success flag to true if the resulting string size does not exceed the buffer
 * size and if the closing brace character is successfully added to the JSON string.
 *
 * @param buffer The buffer to write the JSON string to
 * @param buffer_size The size of the buffer in bytes
 * @return Returns true if the JSON string was successfully ended with a closing brace character, false otherwise
 */
bool Json_endString(char* buffer, size_t buffer_size);

/**
 * @brief Searches for a key in a JSON buffer and returns its value.
 *
 * @param buffer The JSON buffer to search.
 * @param buffer_size The size of the buffer.
 * @param key The key to search for.
 * @param value The output buffer for the value.
 * @param max_value_size The maximum size of the value buffer.
 * @return true If the key was found and the value was copied to the output buffer.
 * @return false If the key was not found or the output buffer was too small.
 */
bool Json_findByKey(const char* buffer, size_t buffer_size, const char* key, char* value, size_t max_value_size);


#endif /* UTILITY_JSON_H_ */
