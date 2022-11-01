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

static void
SwapElements(void* first, void* second, const unsigned int size) {
    unsigned char temp;
    // cppcheck-suppress misra-c2012-11.5; conversion from void* is needed here to have generic buffer
    unsigned char* first_element = (unsigned char*)first;
    // cppcheck-suppress misra-c2012-11.5; conversion from void* is needed here to have generic buffer
    unsigned char* second_element = (unsigned char*)second;
    unsigned int index = size;
    while ((index--) != 0) {
        temp = first_element[index];
        first_element[index] = second_element[index];
        second_element[index] = temp;
    }
}

static void
Heapify(void* buffer, const int n, const int i, const unsigned int element_size, bool (*compareFun)(void*, void*)) {
    bool continue_iterating = true;
    int index = i;
    // cppcheck-suppress misra-c2012-11.5; conversion from void* is needed here to have generic buffer
    unsigned char* elements = (unsigned char*)buffer;

    while (continue_iterating) {
        int largest = index;

        int left = (2 * index) + 1;

        int right = (2 * index) + 2;

        if ((left < n) && (compareFun(&elements[left * (int)element_size], &elements[largest * (int)element_size]))) {
            largest = left;
        }

        if ((right < n) && (compareFun(&elements[right * (int)element_size], &elements[largest * (int)element_size]))) {
            largest = right;
        }

        if (largest != index) {
            SwapElements(&elements[index * (int)element_size], &elements[largest * (int)element_size], element_size);
            index = largest;
        } else {
            continue_iterating = false;
        }
    }
}

void
HeapSort_sort(void* buffer, const int number_of_elements, const unsigned int element_size, bool (*compareFun)(void*, void*)) {
    int i;
    // cppcheck-suppress misra-c2012-11.5; conversion from void* is needed here to have generic buffer
    unsigned char* elements = (unsigned char*)buffer;
    for (i = (number_of_elements / 2) - 1; i >= 0; --i) {
        Heapify(elements, number_of_elements, i, element_size, compareFun);
    }

    for (i = number_of_elements - 1; i >= 0; --i) {
        SwapElements(&elements[0], &elements[i * (int)element_size], element_size);
        Heapify(elements, i, 0, element_size, compareFun);
    }
}
