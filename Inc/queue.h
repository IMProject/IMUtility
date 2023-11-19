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

#ifndef UTILITY_QUEUE_H_
#define UTILITY_QUEUE_H_

#include "typedefs.h"

typedef struct {
    uint32_t front;
    uint32_t rear;
    uint32_t size;
    uint32_t capacity;
    uint32_t element_size;
    uint8_t* buffer;
} Queue_t;

/**
 * @brief Initialize queue.
 *
 * @param[out] *queue Pointer to queue (type Queue_t).
 * @param[in] capacity Queue capacity.
 * @param[in] element_size Size of the element, in bytes.
 * @param[in] *buffer Pointer to buffer where new elements will be saved.
 *
 * @return True if queue is successfully initialized, otherwise false.
 */
bool Queue_init(Queue_t* queue, uint32_t capacity, uint32_t element_size, uint8_t* buffer);

/**
 * @brief Check if queue is full.
 *
 * @param[in] *queue Pointer to queue (type Queue_t).
 *
 * @return True if queue is full, otherwise false.
 */
bool Queue_full(const Queue_t* queue);

/**
 * @brief Check if queue is empty.
 *
 * @param[in] *queue Pointer to queue (type Queue_t).
 *
 * @return True if queue is empty, otherwise false.
 */
bool Queue_empty(const Queue_t* queue);

/**
 * @brief Insert an element at the end of the queue.
 *
 * @param[in] *queue Pointer to queue (type Queue_t).
 * @param[in] *element Pointer to element that will be inserted in the queue.
 *
 * @return True if element is successfully inserted, otherwise false.
 */
bool Queue_enqueue(Queue_t* queue, const uint8_t* element);

/**
 * @brief Remove element from the end of the queue.
 *
 * @param[in] *queue Pointer to queue (type Queue_t).
 * @param[out] *element Pointer to element. Removed element will be saved here.
 *
 * @return True if element is successfully removed, otherwise false.
 */
bool Queue_dequeue(Queue_t* queue, uint8_t* element);

/**
 * @brief Get the element from the front of the queue. Element will not be removed.
 *
 * @param[in] *queue Pointer to queue (type Queue_t).
 * @param[out] *element Pointer to element. Front element will be saved here.
 *
 * @return True if front element is successfully fetched, otherwise false.
 */
bool Queue_front(const Queue_t* queue, uint8_t* element);

/**
 * @brief Get the element from the rear of the queue. Element will not be removed.
 *
 * @param[in] *queue Pointer to queue (type Queue_t).
 * @param[out] *element Pointer to element. Rear element will be saved here.
 *
 * @return True if rear element is successfully fetched, otherwise false.
 */
bool Queue_rear(const Queue_t* queue, uint8_t* element);

#endif /* UTILITY_QUEUE_H_ */
