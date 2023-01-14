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
    RUN_TEST_CASE(Queue, Queue_enqueue_dequeue_float);
}

TEST(Queue, Queue_enqueue_dequeue_uint32) {
    uint32_t array[100];
    const unsigned int capacity = sizeof(array) / sizeof(array[0]);
    Queue_t queue;
    Queue_initQueue(&queue, capacity, sizeof(array[0]), (uint8_t*)array);

    TEST_ASSERT_FALSE(Queue_isFull(&queue));
    TEST_ASSERT_TRUE(Queue_isEmpty(&queue));
    uint32_t element;
    TEST_ASSERT_FALSE(Queue_dequeue(&queue, &element));

    // fill the queue
    uint32_t i;
    for (i = 0U; i < capacity; ++i) {
        TEST_ASSERT_TRUE(Queue_enqueue(&queue, &i));
    }

    // queue is full
    TEST_ASSERT_TRUE(Queue_isFull(&queue));
    TEST_ASSERT_FALSE(Queue_enqueue(&queue, &i));

    // check front element
    TEST_ASSERT_TRUE(Queue_front(&queue, &element));
    TEST_ASSERT_EQUAL_UINT32(0U, element);

    // check rear element
    TEST_ASSERT_TRUE(Queue_rear(&queue, &element));
    TEST_ASSERT_EQUAL_UINT32(i - 1U, element);

    // dequeue
    TEST_ASSERT_TRUE(Queue_dequeue(&queue, &element));
    TEST_ASSERT_EQUAL_UINT32(0U, element);

    // enqueue
    TEST_ASSERT_TRUE(Queue_enqueue(&queue, &i));
    TEST_ASSERT_TRUE(Queue_rear(&queue, &element));
    TEST_ASSERT_EQUAL_UINT32(i, element);
}

TEST(Queue, Queue_enqueue_dequeue_float) {
    float array[100];
    const unsigned int capacity = sizeof(array) / sizeof(array[0]);
    Queue_t queue;
    Queue_initQueue(&queue, capacity, sizeof(array[0]), (uint8_t*)array);

    TEST_ASSERT_FALSE(Queue_isFull(&queue));
    TEST_ASSERT_TRUE(Queue_isEmpty(&queue));
    float element = 1.0f;
    TEST_ASSERT_FALSE(Queue_dequeue(&queue, &element));

    // fill the queue
    uint32_t i;
    for (i = 0U; i < capacity; ++i) {
        float element_temp = (float)i + 1.1f;
        TEST_ASSERT_TRUE(Queue_enqueue(&queue, &element_temp));
    }

    // queue is full
    TEST_ASSERT_TRUE(Queue_isFull(&queue));
    TEST_ASSERT_FALSE(Queue_enqueue(&queue, &element));

    // check front element
    TEST_ASSERT_TRUE(Queue_front(&queue, &element));
    TEST_ASSERT_EQUAL_FLOAT(1.1f, element);

    // check rear element
    TEST_ASSERT_TRUE(Queue_rear(&queue, &element));
    TEST_ASSERT_EQUAL_FLOAT((float)capacity - 1.0f + 1.1f, element);

    // dequeue
    TEST_ASSERT_TRUE(Queue_dequeue(&queue, &element));
    TEST_ASSERT_EQUAL_FLOAT(1.1f, element);

    // enqueue
    element = 5.1f;
    TEST_ASSERT_TRUE(Queue_enqueue(&queue, &element));
    float test_element;
    TEST_ASSERT_TRUE(Queue_rear(&queue, &test_element));
    TEST_ASSERT_EQUAL_FLOAT(test_element, element);
}
