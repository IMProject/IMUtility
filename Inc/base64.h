#ifndef UTILITY_BASE64_H_
#define UTILITY_BASE64_H_

#include "typedefs.h"

#include <string.h>

/**
 * @brief Base64 encode function.
 *
 * @param[in] *data Pointer to data that will be encoded.
 * @param[in] data_length Data length.
 * @param[out] *result Pointer to result, encoded data.
 * @param[in] max_result_length Maximum result length.
 *
 * @return 0 = success, in case of fail value different than 0 is returned.
 */
int32_t Base64_encode(const char* data, size_t data_length, char* result, size_t max_result_length);

/**
 * @brief Base64 decode function.
 *
 * @param[in] *in Pointer to data that will be decoded.
 * @param[in] in_len Input data length.
 * @param[out] *out Pointer to result data, decoded data.
 * @param[in] max_out_len Maximum output length.
 *
 * @return 0 = success, in case of fail value different than 0 is returned.
 */
int32_t Base64_decode(const char* in, size_t in_len, uint8_t* out, size_t max_out_len);

#endif /* UTILITY_BASE64_H_ */
