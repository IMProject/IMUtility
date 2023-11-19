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
    RUN_TEST_CASE(PriorityQueue, PriorityQueue_enqueue_dequeue_float32_t);
    RUN_TEST_CASE(PriorityQueue, PriorityQueue_queue_null_ptr);
    RUN_TEST_CASE(PriorityQueue, PriorityQueue_no_capacity);
    RUN_TEST_CASE(PriorityQueue, PriorityQueue_element_size_zero);
    RUN_TEST_CASE(PriorityQueue, PriorityQueue_items_null_ptr);
}

TEST(PriorityQueue, PriorityQueue_enqueue_dequeue_uint32) {
    uint32_t buffer[100];
    uint32_t priority_array[100];
    PriorityQueueItem_t items;
    items.element = (uint8_t*)buffer;
    items.priority = priority_array;
    const uint32_t capacity = sizeof(buffer) / sizeof(buffer[0]);
    PriorityQueue_t queue;
    TEST_ASSERT_TRUE(PriorityQueue_init(&queue, capacity, sizeof(buffer[0]), &items));

    TEST_ASSERT_TRUE(PriorityQueue_empty(&queue));
    uint32_t element;
    TEST_ASSERT_FALSE(PriorityQueue_dequeue(&queue, (uint8_t*)&element));

    // fill the queue
    PriorityQueueItem_t item;
    uint32_t i;
    uint32_t priority;
    item.priority = &priority;
    for (i = 0U; i < capacity; ++i) {
        *(item.priority) = 2U;
        item.element = (uint8_t*)&i;
        if (i == 50U) {
            *(item.priority) = 1U;
        }
        TEST_ASSERT_TRUE(PriorityQueue_enqueue(&queue, &item));
    }

    // queue is full
    // add element with priority that is not higher than the current lowest priority
    *(item.priority) = 1U;
    TEST_ASSERT_FALSE(PriorityQueue_enqueue(&queue, &item));

    // add element with higher priority than the current lowest priority
    *(item.priority) = 9U;
    TEST_ASSERT_TRUE(PriorityQueue_enqueue(&queue, &item));

    // dequeue
    TEST_ASSERT_TRUE(PriorityQueue_dequeue(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(100U, element);
    TEST_ASSERT_TRUE(PriorityQueue_dequeue(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(0U, element);
}

TEST(PriorityQueue, PriorityQueue_enqueue_dequeue_float32_t) {
    float32_t buffer[100];
    uint32_t priority_array[100];
    PriorityQueueItem_t items;
    items.element = (uint8_t*)buffer;
    items.priority = priority_array;
    const uint32_t capacity = sizeof(buffer) / sizeof(buffer[0]);
    PriorityQueue_t queue;
    TEST_ASSERT_TRUE(PriorityQueue_init(&queue, capacity, sizeof(buffer[0]), &items));

    TEST_ASSERT_TRUE(PriorityQueue_empty(&queue));
    float32_t element;
    TEST_ASSERT_FALSE(PriorityQueue_dequeue(&queue, (uint8_t*)&element));

    // fill the queue
    PriorityQueueItem_t item;
    uint32_t i;
    uint32_t priority;
    item.priority = &priority;
    item.element = (uint8_t*)&element;
    element = 0.0F;
    for (i = 0U; i < capacity; ++i) {
        *(item.priority) = 1U;
        if (i == 50U) {
            *(item.priority) = 2U;
        }
        TEST_ASSERT_TRUE(PriorityQueue_enqueue(&queue, &item));
        element += 1.0F;
    }

    // queue is full
    // add element with priority that is not higher than the current lowest priority
    TEST_ASSERT_FALSE(PriorityQueue_enqueue(&queue, &item));

    // add element with higher priority than the current lowest priority
    *(item.priority) = 9U;
    TEST_ASSERT_TRUE(PriorityQueue_enqueue(&queue, &item));

    // dequeue
    TEST_ASSERT_TRUE(PriorityQueue_dequeue(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_FLOAT(100.0F, element);
    TEST_ASSERT_TRUE(PriorityQueue_dequeue(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_FLOAT(50.0F, element);
}

TEST(PriorityQueue, PriorityQueue_queue_null_ptr) {
    float64_t buffer[100];
    PriorityQueueItem_t items = {};
    TEST_ASSERT_FALSE(PriorityQueue_init(NULL_PTR, sizeof(buffer) / sizeof(buffer[0]), sizeof(buffer[0]), &items));
}

TEST(PriorityQueue, PriorityQueue_no_capacity) {
    float64_t buffer[100];
    PriorityQueueItem_t items = {};
    PriorityQueue_t queue;
    TEST_ASSERT_FALSE(PriorityQueue_init(&queue, 0U, sizeof(buffer[0]), &items));
}

TEST(PriorityQueue, PriorityQueue_element_size_zero) {
    float64_t buffer[100];
    PriorityQueueItem_t items = {};
    PriorityQueue_t queue;
    TEST_ASSERT_FALSE(PriorityQueue_init(&queue, sizeof(buffer) / sizeof(buffer[0]), 0U, &items));
}

TEST(PriorityQueue, PriorityQueue_items_null_ptr) {
    float64_t buffer[100];
    PriorityQueue_t queue;
    TEST_ASSERT_FALSE(PriorityQueue_init(&queue, sizeof(buffer) / sizeof(buffer[0]), sizeof(buffer[0]), NULL_PTR));
}
