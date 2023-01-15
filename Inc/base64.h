#ifndef UTILITY_BASE64_H_
#define UTILITY_BASE64_H_

#include "typedefs.h"

#include <string.h>

int Base64_encode(const char* data, size_t data_length, char* result, size_t max_result_length);
int Base64_decode(const char* in, size_t in_len, uint8_t* out, size_t max_out_len);

#endif /* UTILITY_BASE64_H_ */
