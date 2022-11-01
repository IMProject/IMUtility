#include "heap_sort.h"

#include <stdint.h>

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(HeapSort);

TEST_SETUP(HeapSort) {
}

TEST_TEAR_DOWN(HeapSort) {
}

TEST_GROUP_RUNNER(HeapSort) {
    RUN_TEST_CASE(HeapSort, HeapSort_int);
    RUN_TEST_CASE(HeapSort, HeapSort_double);
    RUN_TEST_CASE(HeapSort, HeapSort_uint64);
}

bool CompareInt(void* first, void* second) {
    bool ret_val = false;
    int* first_element = first;
    int* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}

bool CompareDouble(void* first, void* second) {
    bool ret_val = false;
    double* first_element = first;
    double* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}

bool CompareUint64(void* first, void* second) {
    bool ret_val = false;
    uint64_t* first_element = first;
    uint64_t* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}

TEST(HeapSort, HeapSort_int) {
    int unsorted_array[] = {5, 2, 3, 1000000, 9, 10, 11, 8, 9, 100};
    const int sorted_array[] = {2, 3, 5, 8, 9, 9, 10, 11, 100, 1000000};
    HeapSort_sort(unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareInt);

    unsigned int i;
    for (i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_INT(unsorted_array[i], sorted_array[i]);
    }
}

TEST(HeapSort, HeapSort_double) {
    double unsorted_array[] = {5.8, 2.2, 3.1, 1.1, 9.1, 10.3, 11.2, 8.4, 9.2, 100.9};
    const double sorted_array[] = {1.1, 2.2, 3.1, 5.8, 8.4, 9.1, 9.2, 10.3, 11.2, 100.9};
    HeapSort_sort(unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareDouble);

    unsigned int i;
    for (i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_DOUBLE(unsorted_array[i], sorted_array[i]);
    }
}

TEST(HeapSort, HeapSort_uint64) {
    uint64_t unsorted_array[] = {1111111, 55555555, 44444, 10000000000000, 212121, 1111, 1, 2, 5, 3};
    const uint64_t sorted_array[] = {1, 2, 3, 5, 1111, 44444, 212121, 1111111, 55555555, 10000000000000};
    HeapSort_sort(unsorted_array, sizeof(unsorted_array) / sizeof(unsorted_array[0]), sizeof(unsorted_array[0]), CompareUint64);

    unsigned int i;
    for (i = 0U; i < (sizeof(unsorted_array) / sizeof(unsorted_array[0])); ++i) {
        TEST_ASSERT_EQUAL_UINT64(unsorted_array[i], sorted_array[i]);
    }
}
