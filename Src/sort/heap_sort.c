/****************************************************************************
 *
 *   Copyright (c) 2022 IMProject Development Team. All rights reserved.
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

#include "heap_sort.h"

#include "utils.h"

static void
Heapify(byte_t* buffer, int32_t n, int32_t i, int32_t element_size,
        bool (*compareFun)(void* first, void* second)) {
    bool continue_iterating = true;
    int32_t index = i;

    while (continue_iterating) {
        int32_t largest = index;
        int32_t left = (2 * index) + 1;
        int32_t right = (2 * index) + 2;

        bool compare_ret_value = compareFun(&buffer[left * element_size],
                                            &buffer[largest * element_size]);

        if ((left < n) && (compare_ret_value)) {
            largest = left;
        }

        compare_ret_value = compareFun(&buffer[right * element_size], &buffer[largest * element_size]);

        if ((right < n) && (compare_ret_value)) {
            largest = right;
        }

        if (largest != index) {
            Utils_swapElements(&buffer[index * element_size], &buffer[largest * element_size], (uint32_t)element_size);
            index = largest;
        } else {
            continue_iterating = false;
        }
    }
}

void
HeapSort_sort(byte_t* buffer, int32_t number_of_elements, int32_t element_size,
              bool (*compareFun)(void* first, void* second)) {
    int32_t i;
    for (i = (number_of_elements / 2) - 1; i >= 0; --i) {
        Heapify(buffer, number_of_elements, i, element_size, compareFun);
    }

    for (i = number_of_elements - 1; i >= 0; --i) {
        Utils_swapElements(&buffer[0], &buffer[i * element_size], (uint32_t)element_size);
        Heapify(buffer, i, 0, element_size, compareFun);
    }
}
