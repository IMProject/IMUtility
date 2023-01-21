#include "scheduler.h"

#include <stdio.h>

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Scheduler);

TEST_SETUP(Scheduler) {
}

TEST_TEAR_DOWN(Scheduler) {
}

TEST_GROUP_RUNNER(Scheduler) {
    RUN_TEST_CASE(Scheduler, Scheduler_run);
}

void
Function1(void) {
    printf("\nFunction1 called");
}

void
Function2(void) {
    printf("\nFunction2 called");
}

TEST(Scheduler, Scheduler_run) {
    SchedulerTask_t tasks[2];
    SchedulerTask_t new_task;

    Scheduler_init(tasks, sizeof(tasks) / sizeof(tasks[0]));

    new_task.active = true;
    new_task.function = &Function1;
    TEST_ASSERT_TRUE(Scheduler_addTask(tasks, sizeof(tasks) / sizeof(tasks[0]), &new_task));

    new_task.active = true;
    new_task.function = &Function2;
    TEST_ASSERT_TRUE(Scheduler_addTask(tasks, sizeof(tasks) / sizeof(tasks[0]), &new_task));

    TEST_ASSERT_FALSE(Scheduler_addTask(tasks, sizeof(tasks) / sizeof(tasks[0]), &new_task));

    Scheduler_run(tasks, sizeof(tasks) / sizeof(tasks[0]));
}
