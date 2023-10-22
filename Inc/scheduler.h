/****************************************************************************
 *
 *   Copyright (c) 2023 IMProject Development Team. All rights reserved.
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

#ifndef UTILITY_SCHEDULER_H_
#define UTILITY_SCHEDULER_H_

#include "typedefs.h"

typedef struct {
    void (*function)(void);
    bool active;
} SchedulerTask_t;

/**
 * @brief Function used to initialize scheduler.
 *
 * @param[in, out] *tasks Pointer to tasks (tasks are represented as a structure that contains
 *                        pointer to function and status (active/not active)).
 * @param[in] num_of_tasks Number of tasks that will be initialized.
 */
void Scheduler_init(SchedulerTask_t* tasks, uint32_t num_of_tasks);

/**
 * @brief Function used to add new task in scheduler.
 *
 * @param[in, out] *tasks Pointer to tasks (array of tasks).
 * @param[in] max_num_tasks Maximum number of tasks that can be added in scheduler.
 * @param[in] *new_task Pointer to new task that will be added in scheduler.
 *
 * @return True if task is successfully added, otherwise false.
 */
bool Scheduler_addTask(SchedulerTask_t* tasks, uint32_t max_num_tasks, const SchedulerTask_t* new_task);

/**
 * @brief Function used to run tasks. Tasks will be performed only once, and only active tasks.
 *
 * @param[in] *task Pointer to tasks (array of tasks).
 * @param[in] num_of_tasks Number of tasks that will be performed.
 */
void Scheduler_run(const SchedulerTask_t* task, uint32_t num_of_tasks);

#endif /* UTILITY_SCHEDULER_H_ */
