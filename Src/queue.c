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
Queue_initQueue(Queue_t* const queue, const uint32_t capacity, const unsigned int element_size, uint8_t* buffer) {
    bool status = false;
    if (capacity != 0U) {
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
Queue_isFull(const Queue_t* const queue) {
    return (queue->size == queue->capacity);
}

bool
Queue_isEmpty(const Queue_t* const queue) {
    return (queue->size == 0U);
}

bool
Queue_enqueue(Queue_t* const queue, const void* const element) {
    bool status = false;
    if (!Queue_isFull(queue)) {
        queue->rear = (queue->rear + 1U) % queue->capacity;
        uint8_t* buffer = queue->buffer;
        if (memcpy(&buffer[queue->rear * queue->element_size], element, queue->element_size) != NULL_PTR) {
            queue->size = queue->size + 1U;
            status = true;
        }
    }
    return status;
}

bool
Queue_dequeue(Queue_t* const queue, void* const element) {
    bool status = false;
    if (!Queue_isEmpty(queue)) {
        const uint8_t* buffer = (const uint8_t*)queue->buffer;
        if (memcpy(element, &buffer[queue->front * queue->element_size], queue->element_size) != NULL_PTR) {
            queue->front = (queue->front + 1U) % queue->capacity;
            queue->size = queue->size - 1U;
            status = true;
        }
    }
    return status;
}

bool
Queue_front(const Queue_t* const queue, void* const element) {
    bool status = false;
    if (!Queue_isEmpty(queue)) {
        const uint8_t* buffer = (const uint8_t*)queue->buffer;
        if (memcpy(element, &buffer[queue->front * queue->element_size], queue->element_size) != NULL_PTR) {
            status = true;
        }
    }
    return status;
}

bool
Queue_rear(const Queue_t* const queue, void* const element) {
    bool status = false;
    if (!Queue_isEmpty(queue)) {
        const uint8_t* buffer = (const uint8_t*)queue->buffer;
        if (memcpy(element, &buffer[queue->rear * queue->element_size], queue->element_size) != NULL_PTR) {
            status = true;
        }
    }
    return status;
}
