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
    RUN_TEST_CASE(Queue, Queue_element_size_zero);
    RUN_TEST_CASE(Queue, Queue_buffer_null_ptr);
}

TEST(Queue, Queue_enqueue_dequeue_uint32) {
    uint32_t array[100];
    const uint32_t capacity = sizeof(array) / sizeof(array[0]);
    Queue_t queue;
    TEST_ASSERT_TRUE(Queue_init(&queue, capacity, sizeof(array[0]), (uint8_t*)array));

    // queue is not full
    TEST_ASSERT_FALSE(Queue_full(&queue));

    // queue is empty
    TEST_ASSERT_TRUE(Queue_empty(&queue));

    uint32_t element;

    // check front element, queue empty
    TEST_ASSERT_FALSE(Queue_front(&queue, (uint8_t*)&element));

    // check rear element, queue empty
    TEST_ASSERT_FALSE(Queue_rear(&queue, (uint8_t*)&element));

    TEST_ASSERT_FALSE(Queue_dequeue(&queue, (uint8_t*)&element));

    // fill the queue
    uint32_t i;
    for (i = 0U; i < capacity; ++i) {
        TEST_ASSERT_TRUE(Queue_enqueue(&queue, (uint8_t*)&i));
    }

    // queue is full
    TEST_ASSERT_TRUE(Queue_full(&queue));
    TEST_ASSERT_FALSE(Queue_enqueue(&queue, (uint8_t*)&i));

    // check front element, queue = NULL_PTR
    TEST_ASSERT_FALSE(Queue_front(NULL_PTR, (uint8_t*)&element));

    // check front element, element = NULL_PTR
    TEST_ASSERT_FALSE(Queue_front(&queue, NULL_PTR));

    // check front element
    TEST_ASSERT_TRUE(Queue_front(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(0U, element);

    // check rear element, queue = NULL_PTR
    TEST_ASSERT_FALSE(Queue_rear(NULL_PTR, (uint8_t*)&element));

    // check rear element, element = NULL_PTR
    TEST_ASSERT_FALSE(Queue_rear(&queue, NULL_PTR));

    // check rear element
    TEST_ASSERT_TRUE(Queue_rear(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(i - 1U, element);

    // dequeue, queue = NULL_PTR
    TEST_ASSERT_FALSE(Queue_dequeue(NULL_PTR, (uint8_t*)&element));

    // dequeue, element = NULL_PTR
    TEST_ASSERT_FALSE(Queue_dequeue(&queue, NULL_PTR));

    // dequeue
    TEST_ASSERT_TRUE(Queue_dequeue(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(0U, element);

    // enqueue, queue = NULL_PTR
    TEST_ASSERT_FALSE(Queue_enqueue(NULL_PTR, (uint8_t*)&i));

    // enqueue, element = NULL_PTR
    TEST_ASSERT_FALSE(Queue_enqueue(&queue, NULL_PTR));

    // enqueue
    TEST_ASSERT_TRUE(Queue_enqueue(&queue, (uint8_t*)&i));
    TEST_ASSERT_TRUE(Queue_rear(&queue, (uint8_t*)&element));
    TEST_ASSERT_EQUAL_UINT32(i, element);
}

TEST(Queue, Queue_enqueue_dequeue_float32_t) {
    float32_t array[100];
    const uint32_t capacity = sizeof(array) / sizeof(array[0]);
    Queue_t queue;
    TEST_ASSERT_TRUE(Queue_init(&queue, capacity, sizeof(array[0]), (uint8_t*)array));

    TEST_ASSERT_FALSE(Queue_full(&queue));
    TEST_ASSERT_TRUE(Queue_empty(&queue));
    float32_t element = 1.0F;
    TEST_ASSERT_FALSE(Queue_dequeue(&queue, (uint8_t*)&element));

    // fill the queue
    uint32_t i;
    for (i = 0U; i < capacity; ++i) {
        float32_t element_temp = (float32_t)i + 1.1F;
        TEST_ASSERT_TRUE(Queue_enqueue(&queue, (uint8_t*)&element_temp));
    }

    // queue is full
    TEST_ASSERT_TRUE(Queue_full(&queue));
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
    TEST_ASSERT_FALSE(Queue_init(&queue, 0U, sizeof(array[0]), (uint8_t*)array));
}

TEST(Queue, Queue_element_size_zero) {
    float128_t array[100];
    Queue_t queue;
    TEST_ASSERT_FALSE(Queue_init(&queue, sizeof(array) / sizeof(array[0]), 0U, (uint8_t*)array));
}

TEST(Queue, Queue_buffer_null_ptr) {
    float128_t array[100];
    Queue_t queue;
    TEST_ASSERT_FALSE(Queue_init(&queue, sizeof(array) / sizeof(array[0]), sizeof(array[0]), NULL_PTR));
}
