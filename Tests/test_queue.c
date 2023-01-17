#include "queue.h"

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Queue);

TEST_SETUP(Queue) {
}

TEST_TEAR_DOWN(Queue) {
}

TEST_GROUP_RUNNER(Queue) {
    RUN_TEST_CASE(Queue, Queue_enqueue_dequeue_uint32);
    RUN_TEST_CASE(Queue, Queue_enqueue_dequeue_float32_t);
    RUN_TEST_CASE(Queue, Queue_no_capacity);
}

TEST(Queue, Queue_enqueue_dequeue_uint32) {
    uint32_t array[100];
    const uint32_t capacity = sizeof(array) / sizeof(array[0]);
    Queue_t queue;
    TEST_ASSERT_TRUE(Queue_initQueue(&queue, capacity, sizeof(array[0]), (uint8_t*)array));

    TEST_ASSERT_FALSE(Queue_isFull(&queue));
    TEST_ASSERT_TRUE(Queue_isEmpty(&queue));
    uint32_t element;
    TEST_ASSERT_FALSE(Queue_dequeue(&queue, (uint8_t*)&element));

    // fill the queue
    uint32_t i;
    for (i = 0U; i < capacity; ++i) {
        TEST_ASSERT_TRUE(Queue_enqueue(&queue, (uint8_t*)&i));
    }

    // queue is full
    TEST_ASSERT_TRUE(Queue_isFull(&queue));
    TEST_ASSERT_FALSE(Queue_enqueue(&queue, (uint8_t*)&i));

    // check front element
    TEST_ASSERT_TRUE(Queue_front(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(0U, element);

    // check rear element
    TEST_ASSERT_TRUE(Queue_rear(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(i - 1U, element);

    // dequeue
    TEST_ASSERT_TRUE(Queue_dequeue(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(0U, element);

    // enqueue
    TEST_ASSERT_TRUE(Queue_enqueue(&queue, (uint8_t*)&i));
    TEST_ASSERT_TRUE(Queue_rear(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(i, element);
}

TEST(Queue, Queue_enqueue_dequeue_float32_t) {
    float32_t array[100];
    const uint32_t capacity = sizeof(array) / sizeof(array[0]);
    Queue_t queue;
    TEST_ASSERT_TRUE(Queue_initQueue(&queue, capacity, sizeof(array[0]), (uint8_t*)array));

    TEST_ASSERT_FALSE(Queue_isFull(&queue));
    TEST_ASSERT_TRUE(Queue_isEmpty(&queue));
    float32_t element = 1.0F;
    TEST_ASSERT_FALSE(Queue_dequeue(&queue, (uint8_t*)&element));

    // fill the queue
    uint32_t i;
    for (i = 0U; i < capacity; ++i) {
        float32_t element_temp = (float32_t)i + 1.1F;
        TEST_ASSERT_TRUE(Queue_enqueue(&queue, (uint8_t*)&element_temp));
    }

    // queue is full
    TEST_ASSERT_TRUE(Queue_isFull(&queue));
    TEST_ASSERT_FALSE(Queue_enqueue(&queue, (uint8_t*)&element));

    // check front element
    TEST_ASSERT_TRUE(Queue_front(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_FLOAT(1.1F, element);

    // check rear element
    TEST_ASSERT_TRUE(Queue_rear(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_FLOAT((float32_t)capacity - 1.0F + 1.1F, element);

    // dequeue
    TEST_ASSERT_TRUE(Queue_dequeue(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_FLOAT(1.1F, element);

    // enqueue
    element = 5.1F;
    TEST_ASSERT_TRUE(Queue_enqueue(&queue, (uint8_t*)&element));
    float32_t test_element;
    TEST_ASSERT_TRUE(Queue_rear(&queue, (uint8_t*)&test_element));
    TEST_ASSERT_EQUAL_FLOAT(test_element, element);
}

TEST(Queue, Queue_no_capacity) {
    float128_t array[100];
    Queue_t queue;
    TEST_ASSERT_FALSE(Queue_initQueue(&queue, 0U, sizeof(array[0]), (uint8_t*)array));
}
