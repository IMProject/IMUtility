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

#include "insertion_sort.h"

#include <string.h>

void
InsertionSort_sort(byte_t* buffer, int32_t number_of_elements, int32_t element_size,
                   bool (*compareFun)(void* first, void* second)) {
    byte_t* elements = buffer;
    static byte_t max_element[MAX_ELEMENT_SIZE];
    byte_t* element = &max_element[0];

    for (int32_t i = 1; i < number_of_elements; ++i) {
        /* -E> compliant MC3R1.R21.18 4 Buffer overflow will not happen, all elements in buffer
         * have same size, and their size is stored in element_size variable. Precondition is that
         * element_size must be less than or equal to MAX_ELEMENT_SIZE. */
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
        memcpy(element, &elements[i * element_size], (size_t)element_size);

        int32_t j = i - 1;
        bool compare = compareFun(&elements[j * element_size], element);

        while ((j >= 0) && compare) {
            /* -E> compliant MC3R1.R19.1 3 Overlap will not happen, all elements in buffer
             * have same size, and their size is stored in element_size variable. */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(&elements[(j + 1) * element_size], &elements[j * element_size], (size_t)element_size);
            --j;
            compare = compareFun(&elements[j * element_size], element);
        }
        /* -E> compliant MC3R1.R21.18 4 Buffer overflow will not happen, all elements in buffer
         * have same size, and their size is stored in element_size variable. Precondition is that
         * element_size must be less than or equal to MAX_ELEMENT_SIZE. */
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
        memcpy(&elements[(j + 1) * element_size], element, (size_t)element_size);
    }
}
