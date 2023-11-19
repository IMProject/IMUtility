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

#include "map.h"

#include <string.h>

#define INDEX_NOT_FOUND (-1)

static int32_t
GetIndex(const Map_t* map, const byte_t* key, int32_t size) {
    int32_t index = INDEX_NOT_FOUND;
    for (int32_t i = 0; i < size; ++i) {
        /* -E> compliant MC3R1.R21.18 1 map->key_size is a size of the key in the map and it has appropriate value. */
        if (memcmp(&map->keys[i * map->key_size], key, (size_t)map->key_size) == 0) {
            index = i;
            break;
        }
    }
    return index;
}

bool
Map_init(Map_t* map, byte_t* keys, byte_t* values, int32_t key_size, int32_t value_size,
         int32_t max_map_size) {
    bool status = false;
    if ((key_size != 0) && (value_size != 0) && (max_map_size != 0) && (keys != NULL_PTR) && (values != NULL_PTR)) {
        map->keys = keys;
        map->values = values;
        map->key_size = key_size;
        map->value_size = value_size;
        map->max_map_size = max_map_size;
        map->current_size = 0;
        status = true;
    }
    return status;
}

bool
Map_insert(Map_t* map, const byte_t* key, const byte_t* value) {
    bool status = false;
    if (map != NULL_PTR) {
        int32_t index = GetIndex(map, key, map->current_size);
        if (index == INDEX_NOT_FOUND) {
            if (map->current_size != map->max_map_size) {
                /* -E> compliant MC3R1.R21.18 4 map->key_size is a size of the key in the map and it has appropriate value. */
                /* -E> compliant MC3R1.R19.1 3 Overlap will not happen because there is a check if current map size reached
                 * max map size. */
                // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
                memcpy(&map->keys[map->current_size * map->key_size], key, (size_t)map->key_size);
                /* -E> compliant MC3R1.R21.18 4 map->value_size is a size of the value in the map and it has appropriate value. */
                /* -E> compliant MC3R1.R19.1 3 Overlap will not happen because there is a check if current map size reached
                 * max map size. */
                // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
                memcpy(&map->values[map->current_size * map->value_size], value, (size_t)map->value_size);
                ++map->current_size;
                status = true;
            }
        } else {
            /* -E> compliant MC3R1.R21.18 4 map->value_size is a size of the value in the map and it has appropriate value. */
            /* -E> compliant MC3R1.R19.1 3 Overlap will not happen since the current key is the same as the key that is
             * previously inserted in the map. Therefore, new value will be mapped to that key. */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(&map->values[index * map->value_size], value, (size_t)map->value_size);
            status = true;
        }
    }
    return status;
}

bool
Map_getValue(const Map_t* map, const byte_t* key, byte_t* value) {
    bool status = false;
    if (map != NULL_PTR) {
        int32_t index = GetIndex(map, key, map->current_size);
        if (index != INDEX_NOT_FOUND) {
            /* -E> compliant MC3R1.R21.18 4 map->value_size is a size of the value in the map and it has appropriate value. */
            /* -E> compliant MC3R1.R19.1 3 Overlap will not happen because the map->value_size is the size of the value
             * and every element in map->values has that size */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(value, &map->values[index * map->value_size], (size_t)map->value_size);
            status = true;
        }
    }
    return status;
}
