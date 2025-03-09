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

#include "quick_sort.h"

#include "utils.h"

static int32_t
Partition(byte_t* buffer, int32_t start_index, int32_t end_index, int32_t element_size, bool (*compareFun)(void* first,
          void* second)) {
    int32_t pivot_pos = start_index - 1;

    for (int32_t i = start_index; i <= (end_index - 1); ++i) {
        bool compare = compareFun(&buffer[end_index * element_size], &buffer[i * element_size]);
        if (compare) {
            ++pivot_pos;
            Utils_swapElements(&buffer[pivot_pos * element_size], &buffer[i * element_size], (uint32_t)element_size);
        }
    }
    Utils_swapElements(&buffer[(pivot_pos + 1) * element_size], &buffer[end_index * element_size], (uint32_t)element_size);
    ++pivot_pos;
    return pivot_pos;
}

void
QuickSort_sort(byte_t* buffer, int32_t number_of_elements, int32_t element_size,
               bool (*compareFun)(void* first, void* second)) {
    int32_t indexes[MAX_NUM_OF_ELEMENTS] = {0, number_of_elements - 1};

    int32_t top = 1;

    while (top > 0) {
        int32_t end_index = indexes[top];
        --top;
        int32_t start_index = indexes[top];
        --top;

        int32_t pivot_index = Partition(buffer, start_index, end_index, element_size, compareFun);

        if ((pivot_index - 1) > start_index) {
            ++top;
            indexes[top] = start_index;
            ++top;
            indexes[top] = pivot_index - 1;
        }

        if ((pivot_index + 1) < end_index) {
            ++top;
            indexes[top] = pivot_index + 1;
            ++top;
            indexes[top] = end_index;
        }
    }
}
