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

#include "scheduler.h"

void
Scheduler_init(SchedulerTask_t* tasks, uint32_t num_of_tasks) {
    for (uint32_t i = 0U; i < num_of_tasks; ++i) {
        tasks[i].function = NULL_PTR;
        tasks[i].active = false;
    }
}

bool
Scheduler_addTask(SchedulerTask_t* tasks, uint32_t max_num_tasks, const SchedulerTask_t* new_task) {
    bool status = false;
    for (uint32_t i = 0U; i < max_num_tasks; ++i) {
        if (tasks[i].function == NULL_PTR) {
            tasks[i].function = new_task->function;
            tasks[i].active = new_task->active;
            status = true;
            break;
        }
    }
    return status;
}

void
Scheduler_run(const SchedulerTask_t* task, uint32_t num_of_tasks) {
    for (uint32_t i = 0U; i < num_of_tasks; ++i) {
        if ((task[i].function != NULL_PTR) && (task[i].active)) {
            task[i].function();
        }
    }
}
