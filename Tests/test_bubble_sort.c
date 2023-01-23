#include "bubble_sort.h"

#include "unity.h"
#include "unity_fixture.h"

#include "Helper/sort_functions.h"

TEST_GROUP(BubbleSort);

TEST_SETUP(BubbleSort) {
}

TEST_TEAR_DOWN(BubbleSort) {
}

TEST_GROUP_RUNNER(BubbleSort) {
    RUN_TEST_CASE(BubbleSort, BubbleSort_int32);
    RUN_TEST_CASE(BubbleSort, BubbleSort_float64);
    RUN_TEST_CASE(BubbleSort, BubbleSort_uint64);
}

TEST(BubbleSort, BubbleSort_int32) {
    int32_t unsorted_array[] = {5, 2, 3, 1000000, 9, 10, 11, 8, 9, 100};
    const int32_t sorted_array[] = {2, 3, 5, 8, 9, 9, 10, 11, 100, 1000000};
    BubbleSort_sort((uint8_t*)unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareInt32);

    for (uint32_t i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_INT32(unsorted_array[i], sorted_array[i]);
    }
}

TEST(BubbleSort, BubbleSort_float64) {
    float64_t unsorted_array[] = {5.8, 2.2, 3.1, 1.1, 9.1, 10.3, 11.2, 8.4, 9.2, 100.9};
    const float64_t sorted_array[] = {1.1, 2.2, 3.1, 5.8, 8.4, 9.1, 9.2, 10.3, 11.2, 100.9};
    BubbleSort_sort((uint8_t*)unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareFloat64);

    for (uint32_t i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_DOUBLE(unsorted_array[i], sorted_array[i]);
    }
}

TEST(BubbleSort, BubbleSort_uint64) {
    uint64_t unsorted_array[] = {1111111U, 55555555U, 44444U, 10000000000000U, 212121U, 1111U, 1U, 2U, 5U, 3U};
    const uint64_t sorted_array[] = {1U, 2U, 3U, 5U, 1111U, 44444U, 212121U, 1111111U, 55555555U, 10000000000000U};
    BubbleSort_sort((uint8_t*)unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareUint64);

    for (uint32_t i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_UINT64(unsorted_array[i], sorted_array[i]);
    }
}
