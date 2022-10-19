#include "priority_queue.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(PriorityQueue);

TEST_SETUP(PriorityQueue) {
}

TEST_TEAR_DOWN(PriorityQueue) {
}

TEST_GROUP_RUNNER(PriorityQueue) {
    RUN_TEST_CASE(PriorityQueue, PriorityQueue_enqueue_dequeue_uint32);
    RUN_TEST_CASE(PriorityQueue, PriorityQueue_enqueue_dequeue_float);
}

TEST(PriorityQueue, PriorityQueue_enqueue_dequeue_uint32) {
    uint32_t buffer[100];
    unsigned int priority_array[100];
    PriorityQueueItem_t items;
    items.element = buffer;
    items.priority = priority_array;
    const unsigned int capacity = sizeof(buffer) / sizeof(buffer[0]);
    PriorityQueue_t queue;
    PriorityQueue_initQueue(&queue, capacity, sizeof(buffer[0]), &items);

    TEST_ASSERT_TRUE(PriorityQueue_isEmpty(&queue));
    uint32_t element;
    TEST_ASSERT_FALSE(PriorityQueue_dequeue(&queue, &element));

    // fill the queue
    PriorityQueueItem_t item;
    uint32_t i;
    unsigned int priority;
    item.priority = &priority;
    for (i = 0U; i < capacity; ++i) {
        priority = 1U;
        item.element = &i;
        if (i == 50U) {
            priority = 2U;
        }
        TEST_ASSERT_TRUE(PriorityQueue_enqueue(&queue, &item));
    }

    // queue is full
    // add element with priority that is not higher than the current lowest priority
    TEST_ASSERT_FALSE(PriorityQueue_enqueue(&queue, &item));

    // add element with higher priority than the current lowest priority
    priority = 9U;
    TEST_ASSERT_TRUE(PriorityQueue_enqueue(&queue, &item));

    // dequeue
    TEST_ASSERT_TRUE(PriorityQueue_dequeue(&queue, &element));
    TEST_ASSERT_EQUAL_UINT32(100U, element);
    TEST_ASSERT_TRUE(PriorityQueue_dequeue(&queue, &element));
    TEST_ASSERT_EQUAL_UINT32(50U, element);
}

TEST(PriorityQueue, PriorityQueue_enqueue_dequeue_float) {
    float buffer[100];
    unsigned int priority_array[100];
    PriorityQueueItem_t items;
    items.element = buffer;
    items.priority = priority_array;
    const unsigned int capacity = sizeof(buffer) / sizeof(buffer[0]);
    PriorityQueue_t queue;
    PriorityQueue_initQueue(&queue, capacity, sizeof(buffer[0]), &items);

    TEST_ASSERT_TRUE(PriorityQueue_isEmpty(&queue));
    float element;
    TEST_ASSERT_FALSE(PriorityQueue_dequeue(&queue, &element));

    // fill the queue
    PriorityQueueItem_t item;
    uint32_t i;
    unsigned int priority;
    item.priority = &priority;
    item.element = &element;
    element = 0.0F;
    for (i = 0U; i < capacity; ++i) {
        priority = 1U;
        if (i == 50U) {
            priority = 2U;
        }
        TEST_ASSERT_TRUE(PriorityQueue_enqueue(&queue, &item));
        element += 1.0F;
    }

    // queue is full
    // add element with priority that is not higher than the current lowest priority
    TEST_ASSERT_FALSE(PriorityQueue_enqueue(&queue, &item));

    // add element with higher priority than the current lowest priority
    priority = 9U;
    TEST_ASSERT_TRUE(PriorityQueue_enqueue(&queue, &item));

    // dequeue
    TEST_ASSERT_TRUE(PriorityQueue_dequeue(&queue, &element));
    TEST_ASSERT_EQUAL_FLOAT(100.0F, element);
    TEST_ASSERT_TRUE(PriorityQueue_dequeue(&queue, &element));
    TEST_ASSERT_EQUAL_FLOAT(50.0F, element);
}
