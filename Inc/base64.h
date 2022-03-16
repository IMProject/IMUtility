#ifndef BOOTLOADER_UTILITY_INC_BASE64_H_
#define BOOTLOADER_UTILITY_INC_BASE64_H_

#include <stdint.h>
#include <string.h>

int Base64_encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize);
int Base64_decode (char* in, size_t inLen, unsigned char* out, size_t* outLen);

#endif /* BOOTLOADER_UTILITY_INC_BASE64_H_ */
