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

#include "queue.h"

#include <string.h>

bool
Queue_init(Queue_t* queue, uint32_t capacity, uint32_t element_size, uint8_t* buffer) {
    bool status = false;
    if ((element_size != 0U) && (capacity != 0U) && (buffer != NULL_PTR)) {
        queue->capacity = capacity;
        queue->front = 0U;
        queue->size = 0U;
        queue->rear = capacity - 1U;
        queue->element_size = element_size;
        queue->buffer = buffer;
        status = true;
    }
    return status;
}

bool
Queue_full(const Queue_t* queue) {
    return (queue->size == queue->capacity);
}

bool
Queue_empty(const Queue_t* queue) {
    return (queue->size == 0U);
}

bool
Queue_enqueue(Queue_t* queue, const uint8_t* element) {
    bool status = false;
    if ((queue != NULL_PTR) && (element != NULL_PTR)) {
        if (!Queue_full(queue)) {
            uint8_t* buffer = queue->buffer;
            /* -E> compliant MC3R1.R21.18 4 Buffer overflow will not happen, element has same size as one element
             * in buffer, and their size is stored in element_size member. Also, there is a guard that checks that
             * queue is not full. */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(&buffer[((queue->rear + 1U) % queue->capacity) * queue->element_size], element, queue->element_size);
            queue->rear = (queue->rear + 1U) % queue->capacity;
            queue->size = queue->size + 1U;
            status = true;
        }
    }
    return status;
}

bool
Queue_dequeue(Queue_t* queue, uint8_t* element) {
    bool status = false;
    if ((queue != NULL_PTR) && (element != NULL_PTR)) {
        if (!Queue_empty(queue)) {
            const uint8_t* buffer = (const uint8_t*)queue->buffer;
            /* -E> compliant MC3R1.R21.18 3 Buffer overflow will not happen, element has same size as one element
             * in buffer, and their size is stored in element_size member. */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(element, &buffer[queue->front * queue->element_size], queue->element_size);
            queue->front = (queue->front + 1U) % queue->capacity;
            queue->size = queue->size - 1U;
            status = true;
        }
    }
    return status;
}

bool
Queue_front(const Queue_t* queue, uint8_t* element) {
    bool status = false;
    if ((queue != NULL_PTR) && (element != NULL_PTR)) {
        if (!Queue_empty(queue)) {
            const uint8_t* buffer = (const uint8_t*)queue->buffer;
            /* -E> compliant MC3R1.R21.18 3 Buffer overflow will not happen, element has same size as one element
             * in buffer, and their size is stored in element_size member. */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(element, &buffer[queue->front * queue->element_size], queue->element_size);
            status = true;
        }
    }
    return status;
}

bool
Queue_rear(const Queue_t* queue, uint8_t* element) {
    bool status = false;
    if ((queue != NULL_PTR) && (element != NULL_PTR)) {
        if (!Queue_empty(queue)) {
            const uint8_t* buffer = (const uint8_t*)queue->buffer;
            /* -E> compliant MC3R1.R21.18 3 Buffer overflow will not happen, element has same size as one element
             * in buffer, and their size is stored in element_size member. */
            // cppcheck-suppress misra-c2012-17.7; return value is not needed in this case
            memcpy(element, &buffer[queue->rear * queue->element_size], queue->element_size);
            status = true;
        }
    }
    return status;
}
