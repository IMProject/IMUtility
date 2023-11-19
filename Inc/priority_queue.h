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

#ifndef UTILITY_PRIORITY_QUEUE_H_
#define UTILITY_PRIORITY_QUEUE_H_

#include "typedefs.h"

typedef struct {
    uint32_t* priority;
    uint8_t* element;
} PriorityQueueItem_t;

typedef struct {
    uint32_t size;
    uint32_t capacity;
    uint32_t element_size;
    uint32_t* priority_array;
    uint8_t* buffer;
} PriorityQueue_t;

/**
 * @brief Initialize priority queue.
 *
 * @param[out] *queue Pointer to priority queue (type PriorityQueue_t).
 * @param[in] capacity Priority queue capacity.
 * @param[in] element_size Size of the element, in bytes.
 * @param[in] *items Pointer to items where all new elements will be stored (priority + *element).
 *
 * @return True if priority queue is successfully initialized, otherwise false.
 */
bool PriorityQueue_init(PriorityQueue_t* queue, uint32_t capacity, uint32_t element_size,
                        const PriorityQueueItem_t* items);

/**
 * @brief Check if priority queue is empty.
 *
 * @param[in] *queue Pointer to priority queue (type PriorityQueue_t).
 *
 * @return True if priority queue is empty, otherwise false.
 */
bool PriorityQueue_empty(const PriorityQueue_t* queue);

/**
 * @brief Insert an element at the end of the priority queue. If priority queue is full,
 * check if the new element has higher priority than the lowest priority in the priority queue,
 * if yes, remove the element with the lowest priority from the priority queue and insert the new
 * element at the end of the priority queue.
 *
 * @param[in] *queue Pointer to priority queue (type PriorityQueue_t).
 * @param[in] *item Pointer to the item that will be inserted in the priority queue.
 *
 * @return True if element is successfully inserted, otherwise false.
 */
bool PriorityQueue_enqueue(PriorityQueue_t* queue, const PriorityQueueItem_t* item);

/**
 * @brief Remove the element with the highest priority from the priority queue.
 *
 * @param[in] *queue Pointer to priority queue (type PriorityQueue_t).
 * @param[out] *element Pointer to element. Removed element will be stored here.
 *
 * @return True if element is successfully removed, otherwise false.
 */
bool PriorityQueue_dequeue(PriorityQueue_t* queue, uint8_t* element);

#endif /* UTILITY_PRIORITY_QUEUE_H_ */
