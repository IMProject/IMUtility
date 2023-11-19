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

#ifndef UTILITY_MAP_H_
#define UTILITY_MAP_H_

#include "typedefs.h"

typedef struct {
    byte_t* keys;
    byte_t* values;
    int32_t key_size;
    int32_t value_size;
    int32_t max_map_size;
    int32_t current_size;
} Map_t;

/**
 * @brief Initialize map.
 *
 * @param[out] *map Pointer to the map (type Map_t).
 * @param[in] *keys Pointer to keys in the map.
 * @param[in] *values Pointer to values in the map.
 * @param[in] key_size Size of the key in the map.
 * @param[in] value_size Size of the value in the map.
 * @param[in] max_map_size Max size of the map.
 *
 * @return True if map is successfully initialized, otherwise false.
 */
bool Map_init(Map_t* map, byte_t* keys, byte_t* values, int32_t key_size, int32_t value_size,
              int32_t max_map_size);

/**
 * @brief Insert new element in the map.
 *
 * @param[in/out] *map Pointer to the map (type Map_t).
 * @param[in] *key Pointer to the key that will be inserted in the map.
 * @param[in] *value Pointer to the value that will be inserted in the map.
 *
 * @return True if new element is successfully inserted in the map, otherwise false.
 */
bool Map_insert(Map_t* map, const byte_t* key, const byte_t* value);

/**
 * @brief Get a value from the map using the key.
 *
 * @param[in] *map Pointer to the map (type Map_t).
 * @param[in] *key Pointer to the key.
 * @param[out] *value Pointer to the value that is mapped with the particular key.
 *
 * @return True if the value is successfully gotten using the key, otherwise false.
 */
bool Map_getValue(const Map_t* map, const byte_t* key, byte_t* value);

#endif /* UTILITY_MAP_H_ */
