/****************************************************************************
 *
 *   Copyright (c) 2025 IMProject Development Team. All rights reserved.
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

#include "merge_sort.h"

#include <string.h>

static void
MergeHalves(byte_t* buffer, int32_t element_size, int32_t left, int32_t mid, int32_t right,
            bool (*compareFun)(void* first, void* second)) {
    byte_t left_half[MAX_HALVES_SIZE];
    byte_t right_half[MAX_HALVES_SIZE];
    int32_t i;
    int32_t j;
    int32_t k;
    int32_t number_of_elements_1 = mid - left + 1;
    int32_t number_of_elements_2 =  right - mid;

    for (i = 0; i < number_of_elements_1; ++i) {
        memcpy(&left_half[i * element_size], &buffer[(left + i) * element_size], (size_t)element_size);
    }

    for (j = 0; j < number_of_elements_2; ++j) {
        memcpy(&right_half[j * element_size], &buffer[(mid + 1 + j) * element_size], (size_t)element_size);
    }

    i = 0;
    j = 0;
    k = left;

    while ((i < number_of_elements_1) && (j < number_of_elements_2)) {
        bool compare = compareFun(&right_half[j * element_size], &left_half[i * element_size]);
        if (compare) {
            memcpy(&buffer[k * element_size], &left_half[i * element_size], (size_t)element_size);
            ++i;
        } else {
            memcpy(&buffer[k * element_size], &right_half[j * element_size], (size_t)element_size);
            ++j;
        }
        ++k;
    }

    while (i < number_of_elements_1) {
        memcpy(&buffer[k * element_size], &left_half[i * element_size], (size_t)element_size);
        ++i;
        ++k;
    }

    while (j < number_of_elements_2) {
        memcpy(&buffer[k * element_size], &right_half[j * element_size], (size_t)element_size);
        ++j;
        ++k;
    }
}

void
MergeSort_sort(byte_t* buffer, int32_t number_of_elements, int32_t element_size,
               bool (*compareFun)(void* first, void* second)) {
    for (int32_t current_size = 1; current_size <= number_of_elements - 1; current_size *= 2) {
        for (int32_t left = 0; left < number_of_elements - 1; left += (2 * current_size)) {
            int32_t compare_first_1 = left + current_size - 1;
            int32_t compare_second = number_of_elements - 1;
            int32_t mid = (compare_first_1 < compare_second) ? compare_first_1 : compare_second;

            int32_t compare_first_2 = left + (2 * current_size) - 1;
            int32_t right = (compare_first_2 < compare_second) ? compare_first_2 : compare_second;

            MergeHalves(buffer, element_size, left, mid, right, compareFun);
        }
    }
}
