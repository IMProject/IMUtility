#include "sort_functions.h"

bool
CompareInt32(void* first, void* second) {
    bool ret_val = false;
    int32_t* first_element = first;
    int32_t* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}

bool
CompareFloat64(void* first, void* second) {
    bool ret_val = false;
    float64_t* first_element = first;
    float64_t* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}

bool
CompareUint64(void* first, void* second) {
    bool ret_val = false;
    uint64_t* first_element = first;
    uint64_t* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}
