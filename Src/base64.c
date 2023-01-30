/*
 * Base64 Decode
 * Polfosol
 *
 * Base64 encoding/decoding (RFC1341)
 * Copyright (c) 2005-2011, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 *
 */

// Source code from Polfosol: https://stackoverflow.com/questions/180947/base64-decode-snippet-in-c/13935718
// Source code from Jouni Malinen: https://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c


// Encode/Decode functions are modified by Juraj Ciberlin (jciberlin1@gmail.com) to be MISRA C 2012 compliant

#include "base64.h"

int32_t
Base64_encode(const char* data, size_t data_length, char* result, size_t max_result_length) {
    int32_t success = 0;
    const uint8_t base64_table[65] = {
        (uint8_t)'A', (uint8_t)'B', (uint8_t)'C', (uint8_t)'D',
        (uint8_t)'E', (uint8_t)'F', (uint8_t)'G', (uint8_t)'H',
        (uint8_t)'I', (uint8_t)'J', (uint8_t)'K', (uint8_t)'L',
        (uint8_t)'M', (uint8_t)'N', (uint8_t)'O', (uint8_t)'P',
        (uint8_t)'Q', (uint8_t)'R', (uint8_t)'S', (uint8_t)'T',
        (uint8_t)'U', (uint8_t)'V', (uint8_t)'W', (uint8_t)'X',
        (uint8_t)'Y', (uint8_t)'Z', (uint8_t)'a', (uint8_t)'b',
        (uint8_t)'c', (uint8_t)'d', (uint8_t)'e', (uint8_t)'f',
        (uint8_t)'g', (uint8_t)'h', (uint8_t)'i', (uint8_t)'j',
        (uint8_t)'k', (uint8_t)'l', (uint8_t)'m', (uint8_t)'n',
        (uint8_t)'o', (uint8_t)'p', (uint8_t)'q', (uint8_t)'r',
        (uint8_t)'s', (uint8_t)'t', (uint8_t)'u', (uint8_t)'v',
        (uint8_t)'w', (uint8_t)'x', (uint8_t)'y', (uint8_t)'z',
        (uint8_t)'0', (uint8_t)'1', (uint8_t)'2', (uint8_t)'3',
        (uint8_t)'4', (uint8_t)'5', (uint8_t)'6', (uint8_t)'7',
        (uint8_t)'8', (uint8_t)'9', (uint8_t)'+', (uint8_t)'/',
        (uint8_t)'\0'
    };
    uint8_t* out;
    const uint8_t* in = (const uint8_t*) data;

    size_t len = 4U * ((data_length + 2U) / 3U);

    if (len < data_length) {
        success = 1;
    }

    if (success == 0) {
        size_t current_length = 0U;
        size_t in_position = 0U;
        out = (uint8_t*)&result[0];
        uint8_t* pos = out;
        while ((data_length - in_position) >= 3U) {
            current_length += 4U;
            if (current_length > max_result_length) {
                success = 1;
                break;
            }
            *pos = base64_table[in[0] >> 2];
            ++pos;
            *pos = base64_table[((in[0] & 0x03U) << 4) | (in[1] >> 4)];
            ++pos;
            *pos = base64_table[((in[1] & 0x0FU) << 2) | (in[2] >> 6)];
            ++pos;
            *pos = base64_table[in[2] & 0x3FU];
            ++pos;
            ++in;
            ++in;
            ++in;
            in_position += 3U;
        }

        if ((success == 0) && ((data_length - in_position) != 0U)) {
            current_length += 4U;
            if (current_length > max_result_length) {
                success = 1;
            }

            if (success == 0) {
                *pos = base64_table[in[0] >> 2];
                ++pos;
                if ((data_length - in_position) == 1U) {
                    *pos = base64_table[(in[0] & 0x03U) << 4];
                    ++pos;
                    *pos = (uint8_t)'=';
                    ++pos;
                } else {
                    *pos = base64_table[((in[0] & 0x03U) << 4) | (in[1] >> 4)];
                    ++pos;
                    *pos = base64_table[(in[1] & 0x0FU) << 2];
                    ++pos;
                }
                *pos = (uint8_t)'=';
                ++pos;
            }
        }

        *pos = (uint8_t)'\0';
    }

    return success;
}

int32_t
Base64_decode(const char* in, size_t in_len, uint8_t* out, size_t max_out_len) {
    int32_t success = 0;
    const uint32_t base64_index[256] = {
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 62U, 63U, 62U, 62U, 63U, 52U, 53U, 54U, 55U, 56U, 57U, 58U, 59U, 60U,
        61U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U, 11U,
        12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U, 21U, 22U, 23U, 24U, 25U, 0U, 0U, 0U,
        0U, 63U, 0U, 26U, 27U, 28U, 29U, 30U, 31U, 32U, 33U, 34U, 35U, 36U, 37U, 38U, 39U,
        40U, 41U, 42U, 43U, 44U, 45U, 46U, 47U, 48U, 49U, 50U, 51U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U, 0U,
        0U
    };
    const uint8_t* in_data_uchar = (const uint8_t*)in;
    bool pad_bool = (in_len > 0U) && (((in_len % 4U) != 0U) || (in_data_uchar[in_len - 1U] == (uint8_t)'='));
    uint32_t pad_uint = 0U;
    if (pad_bool) {
        pad_uint = 1U;
    }
    const size_t len = (((in_len + 3U) / 4U) - pad_uint) * 4U;
    const size_t out_len = ((len / 4U) * 3U) + pad_uint;

    if (out_len > max_out_len) {
        success = 1;
    }

    if (success == 0) {
        size_t j = 0U;
        for (size_t i = 0U; i < len; i += 4U) {
            uint32_t n = (base64_index[in_data_uchar[i]] << 18U) | (base64_index[in_data_uchar[i + 1U]] << 12U) |
                         (base64_index[in_data_uchar[i + 2U]] << 6U) | (base64_index[in_data_uchar[i + 3U]]);
            out[j] = (uint8_t)(n >> 16U);
            ++j;
            out[j] = (uint8_t)((n >> 8U) & 0xFFU);
            ++j;
            out[j] = (uint8_t)(n & 0xFFU);
            ++j;
        }
        if (pad_bool) {
            uint32_t n = (base64_index[in_data_uchar[len]] << 18U) | (base64_index[in_data_uchar[len + 1U]] << 12U);
            out[out_len - 1U] = (uint8_t)(n >> 16U);

            if ((in_len > (len + 2U)) && (in_data_uchar[len + 2U] != (uint8_t)'=')) {
                if ((out_len + 1U) > max_out_len) {
                    success = 1;
                } else {
                    n |= base64_index[in_data_uchar[len + 2U]] << 6U;
                    out[out_len] = (uint8_t)((n >> 8U) & 0xFFU);
                }
            }
        }
    }

    return success;
}
