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

#include "priority_queue.h"

#include <string.h>

static bool
Full(const PriorityQueue_t* queue) {
    return (queue->size == queue->capacity);
}

static uint32_t
GetHighestPriorityIndex(const PriorityQueue_t* queue) {
    uint32_t highest_priority = queue->priority_array[0];
    uint32_t index = 0U;

    for (uint32_t i = 0U; i < queue->size; ++i) {
        if (highest_priority < queue->priority_array[i]) {
            highest_priority = queue->priority_array[i];
            index = i;
        }
    }

    return index;
}

static uint32_t
GetLowestPriorityIndex(const PriorityQueue_t* queue) {
    uint32_t lowest_priority = queue->priority_array[0];
    uint32_t index = 0U;

    for (uint32_t i = 0U; i < queue->size; ++i) {
        if (lowest_priority > queue->priority_array[i]) {
            lowest_priority = queue->priority_array[i];
            index = i;
        }
    }

    return index;
}

bool
PriorityQueue_init(PriorityQueue_t* queue, uint32_t capacity, uint32_t element_size,
                   const PriorityQueueItem_t* items) {
    bool status = false;
    if ((queue != NULL_PTR) && (capacity != 0U) && (element_size != 0U) && (items != NULL_PTR)) {
        queue->capacity = capacity;
        queue->size = 0U;
        queue->element_size = element_size;
        queue->priority_array = items->priority;
        queue->buffer = items->element;
        status = true;
    }
    return status;
}

bool
PriorityQueue_empty(const PriorityQueue_t* queue) {
    return (queue->size == 0U);
}

bool
PriorityQueue_enqueue(PriorityQueue_t* queue, const PriorityQueueItem_t* item) {
    bool status = false;
    if (!Full(queue)) {
        uint8_t* buffer = queue->buffer;
        /* -E> compliant MC3R1.R21.18 3 Buffer overflow will not happen, there is a guard that checks that priority
         * queue is not full. */
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
        memcpy(&buffer[queue->size * queue->element_size], item->element, queue->element_size);
        queue->priority_array[queue->size] = *(item->priority);
        queue->size = queue->size + 1U;
        status = true;
    } else {
        uint32_t lowest_priority_index = GetLowestPriorityIndex(queue);
        if (queue->priority_array[lowest_priority_index] < (*(item->priority))) {
            status = true;
            uint8_t* buffer = queue->buffer;
            queue->size = queue->size - 1U;
            const uint32_t current_size = queue->size;
            for (uint32_t i = lowest_priority_index; i < current_size; ++i) {
                /* -E> compliant MC3R1.R19.1 4 Overlap will not happen because iteration will be performed until current
                 * queue size is reached which is previous size - 1. Therefore, last valid element that will be used in
                 * memcpy function is placed in current size + 1. */
                // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
                memcpy(&buffer[i * queue->element_size], &buffer[(i * queue->element_size) + queue->element_size],
                       queue->element_size);
                queue->priority_array[i] = queue->priority_array[i + 1U];
            }
            /* -E> compliant MC3R1.R21.18 4 Buffer overflow will not happen, there will be one more place in buffer to
             * insert a new element because of removing element with the lowest priority (performed in the above code,
             * in the same function). */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(&buffer[queue->size * queue->element_size], item->element, queue->element_size);
            queue->priority_array[queue->size] = *(item->priority);
            queue->size = queue->size + 1U;
        }
    }
    return status;
}

bool
PriorityQueue_dequeue(PriorityQueue_t* queue, uint8_t* element) {
    bool status = false;
    if (!PriorityQueue_empty(queue)) {
        status = true;
        uint32_t highest_priority_index = GetHighestPriorityIndex(queue);
        uint8_t* buffer = queue->buffer;
        /* -E> compliant MC3R1.R21.18 3 Buffer overflow will not happen, element has same size as one element
         * in buffer, and their size is stored in element_size member. */
        // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
        memcpy(element, &buffer[highest_priority_index * queue->element_size], queue->element_size);
        queue->size = queue->size - 1U;
        const uint32_t current_size = queue->size;
        for (uint32_t i = highest_priority_index; i < current_size; ++i) {
            /* -E> compliant MC3R1.R19.1 4 Overlap will not happen because iteration will be performed until current
             * queue size is reached which is previous size - 1. Therefore, last valid element that will be used in
             * memcpy function is placed in current size + 1. */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(&buffer[i * queue->element_size], &buffer[(i * queue->element_size) + queue->element_size],
                   queue->element_size);
            queue->priority_array[i] = queue->priority_array[i + 1U];
        }
    }
    return status;
}
