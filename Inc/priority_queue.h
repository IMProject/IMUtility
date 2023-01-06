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

#include <stdbool.h>

typedef struct PriorityQueueItem {
    unsigned int* priority;
    void* element;
} PriorityQueueItem_t;

typedef struct PriorityQueue {
    unsigned int size;
    unsigned int capacity;
    unsigned int element_size;
    unsigned int* priority_array;
    void* buffer;
} PriorityQueue_t;

void PriorityQueue_initQueue(PriorityQueue_t* const queue, const int capacity, const unsigned int element_size, const PriorityQueueItem_t* items);
bool PriorityQueue_isEmpty(const PriorityQueue_t* const queue);
bool PriorityQueue_enqueue(PriorityQueue_t* const queue, const PriorityQueueItem_t* const item);
bool PriorityQueue_dequeue(PriorityQueue_t* const queue, void* const element);

#endif /* UTILITY_PRIORITY_QUEUE_H_ */
