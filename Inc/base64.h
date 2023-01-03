#ifndef UTILITY_BASE64_H_
#define UTILITY_BASE64_H_

#include <stdint.h>
#include <string.h>

int Base64_encode(const void* data, size_t data_length, char* result, size_t max_result_length);
int Base64_decode(const char* in, size_t in_len, unsigned char* out, size_t max_out_len);

#endif /* UTILITY_BASE64_H_ */
