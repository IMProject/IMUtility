#include "sort_functions.h"

bool
CompareInt32(void* first, void* second) {
    bool ret_val = false;
    const int32_t* first_element = first;
    const int32_t* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}

bool
CompareFloat64(void* first, void* second) {
    bool ret_val = false;
    const float64_t* first_element = first;
    const float64_t* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}

bool
CompareUint64(void* first, void* second) {
    bool ret_val = false;
    const uint64_t* first_element = first;
    const uint64_t* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}
