/****************************************************************************
 *
 *   Copyright (c) 2023 IMProject Development Team. All rights reserved.
 *   Authors: Igor Misic <igy1000mb@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name IMProject nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

#include "crc16_en_13757.h"

#include "crc16_base.h"

#define INITIAL_CRC16_VALUE (0x0U)
#define FINAL_XOR_VALUE (0xFFFFU)
#define REFLECTED_OUTPUT (false)
#define REFLECTED_INPUT (false)
#define FINAL_XOR (true)

uint16_t
Crc16_en13757(
    const uint8_t* crc_data_ptr,
    uint32_t crc_length,
    bool final_crc,
    const uint16_t* last_crc_ptr) {

    /* Table for CRC-16 EN 13757 (Polynomial 0x3D65) */
    static const uint16_t crc_table[256] = {
        0x0000U, 0x3D65U, 0x7ACAU, 0x47AFU, 0xF594U, 0xC8F1U, 0x8F5EU, 0xB23BU, 0xD64DU, 0xEB28U, 0xAC87U, 0x91E2U, 0x23D9U, 0x1EBCU, 0x5913U, 0x6476U,
        0x91FFU, 0xAC9AU, 0xEB35U, 0xD650U, 0x646BU, 0x590EU, 0x1EA1U, 0x23C4U, 0x47B2U, 0x7AD7U, 0x3D78U, 0x001DU, 0xB226U, 0x8F43U, 0xC8ECU, 0xF589U,
        0x1E9BU, 0x23FEU, 0x6451U, 0x5934U, 0xEB0FU, 0xD66AU, 0x91C5U, 0xACA0U, 0xC8D6U, 0xF5B3U, 0xB21CU, 0x8F79U, 0x3D42U, 0x0027U, 0x4788U, 0x7AEDU,
        0x8F64U, 0xB201U, 0xF5AEU, 0xC8CBU, 0x7AF0U, 0x4795U, 0x003AU, 0x3D5FU, 0x5929U, 0x644CU, 0x23E3U, 0x1E86U, 0xACBDU, 0x91D8U, 0xD677U, 0xEB12U,
        0x3D36U, 0x0053U, 0x47FCU, 0x7A99U, 0xC8A2U, 0xF5C7U, 0xB268U, 0x8F0DU, 0xEB7BU, 0xD61EU, 0x91B1U, 0xACD4U, 0x1EEFU, 0x238AU, 0x6425U, 0x5940U,
        0xACC9U, 0x91ACU, 0xD603U, 0xEB66U, 0x595DU, 0x6438U, 0x2397U, 0x1EF2U, 0x7A84U, 0x47E1U, 0x004EU, 0x3D2BU, 0x8F10U, 0xB275U, 0xF5DAU, 0xC8BFU,
        0x23ADU, 0x1EC8U, 0x5967U, 0x6402U, 0xD639U, 0xEB5CU, 0xACF3U, 0x9196U, 0xF5E0U, 0xC885U, 0x8F2AU, 0xB24FU, 0x0074U, 0x3D11U, 0x7ABEU, 0x47DBU,
        0xB252U, 0x8F37U, 0xC898U, 0xF5FDU, 0x47C6U, 0x7AA3U, 0x3D0CU, 0x0069U, 0x641FU, 0x597AU, 0x1ED5U, 0x23B0U, 0x918BU, 0xACEEU, 0xEB41U, 0xD624U,
        0x7A6CU, 0x4709U, 0x00A6U, 0x3DC3U, 0x8FF8U, 0xB29DU, 0xF532U, 0xC857U, 0xAC21U, 0x9144U, 0xD6EBU, 0xEB8EU, 0x59B5U, 0x64D0U, 0x237FU, 0x1E1AU,
        0xEB93U, 0xD6F6U, 0x9159U, 0xAC3CU, 0x1E07U, 0x2362U, 0x64CDU, 0x59A8U, 0x3DDEU, 0x00BBU, 0x4714U, 0x7A71U, 0xC84AU, 0xF52FU, 0xB280U, 0x8FE5U,
        0x64F7U, 0x5992U, 0x1E3DU, 0x2358U, 0x9163U, 0xAC06U, 0xEBA9U, 0xD6CCU, 0xB2BAU, 0x8FDFU, 0xC870U, 0xF515U, 0x472EU, 0x7A4BU, 0x3DE4U, 0x0081U,
        0xF508U, 0xC86DU, 0x8FC2U, 0xB2A7U, 0x009CU, 0x3DF9U, 0x7A56U, 0x4733U, 0x2345U, 0x1E20U, 0x598FU, 0x64EAU, 0xD6D1U, 0xEBB4U, 0xAC1BU, 0x917EU,
        0x475AU, 0x7A3FU, 0x3D90U, 0x00F5U, 0xB2CEU, 0x8FABU, 0xC804U, 0xF561U, 0x9117U, 0xAC72U, 0xEBDDU, 0xD6B8U, 0x6483U, 0x59E6U, 0x1E49U, 0x232CU,
        0xD6A5U, 0xEBC0U, 0xAC6FU, 0x910AU, 0x2331U, 0x1E54U, 0x59FBU, 0x649EU, 0x00E8U, 0x3D8DU, 0x7A22U, 0x4747U, 0xF57CU, 0xC819U, 0x8FB6U, 0xB2D3U,
        0x59C1U, 0x64A4U, 0x230BU, 0x1E6EU, 0xAC55U, 0x9130U, 0xD69FU, 0xEBFAU, 0x8F8CU, 0xB2E9U, 0xF546U, 0xC823U, 0x7A18U, 0x477DU, 0x00D2U, 0x3DB7U,
        0xC83EU, 0xF55BU, 0xB2F4U, 0x8F91U, 0x3DAAU, 0x00CFU, 0x4760U, 0x7A05U, 0x1E73U, 0x2316U, 0x64B9U, 0x59DCU, 0xEBE7U, 0xD682U, 0x912DU, 0xAC48U
    };

    bool final_xor = false;
    uint16_t crc_initial_value = INITIAL_CRC16_VALUE;

    if (NULL_PTR != last_crc_ptr) {
        crc_initial_value = *last_crc_ptr;
    }

    if (final_crc) {
        final_xor = FINAL_XOR;
    }

    return Crc16Base(
               crc_table,
               crc_data_ptr,
               crc_length,
               crc_initial_value,
               FINAL_XOR_VALUE,
               REFLECTED_OUTPUT,
               REFLECTED_INPUT,
               final_xor
           );
}
