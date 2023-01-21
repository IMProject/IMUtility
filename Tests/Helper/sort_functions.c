#include "sort_functions.h"

#include <stdint.h>

bool
CompareInt(void* first, void* second) {
    bool ret_val = false;
    int* first_element = first;
    int* second_element = second;
    if (*first_element > *second_element) {
        ret_val = true;
    }
    return ret_val;
}

bool
CompareDouble(void* first, void* second) {
    bool ret_val = false;
    double* first_element = first;
    double* second_element = second;
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
