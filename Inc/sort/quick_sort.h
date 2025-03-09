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

#ifndef UTILITY_QUICK_SORT_H_
#define UTILITY_QUICK_SORT_H_

#include "typedefs.h"

#define MAX_NUM_OF_ELEMENTS (64)

/**
 * @brief Sort elements using quick sort algorithm. Quick sort algorithm works on divide and conquer
 * principle. Firstly, it selects an element from an array as a pivot. Secondly, partitioning is done
 * (array is arranged around the pivot). Elements smaller than the pivot will be on the left side,
 * elements that are greater than the pivot will be on the right side. Pivot will be in the correct
 * position. Repeat the process until the initial array is not sorted. This algorithm does not use
 * recursion since it is not MISRA compliant.
 * Time complexity: O(N log N)
 *
 * @param[in/out] *buffer Pointer to the buffer that contains elements that will be sorted.
 * @param[in] number_of_elements Number of elements in the buffer.
 * @param[in] element_size Size of the element, in bytes.
 * @param[in] *compareFun Pointer to compare function. Compare function has two parameters (pointer to
 *                        first element and pointer to second element). As a result, it returns boolean,
 *                        true if first element is greater than second element, otherwise false.
 */
void QuickSort_sort(byte_t* buffer, int32_t number_of_elements, int32_t element_size,
                    bool (*compareFun)(void* first, void* second));

#endif /* UTILITY_QUICK_SORT_H_ */
