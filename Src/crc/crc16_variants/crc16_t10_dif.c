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

#include "crc16_t10_dif.h"

#include "crc16_base.h"

#define INITIAL_CRC16_VALUE (0x0U)
#define FINAL_XOR_VALUE (0x0U)
#define REFLECTED_OUTPUT (false)
#define REFLECTED_INPUT (false)

uint16_t
Crc16_t10Dif(
    const uint8_t* crc_data_ptr,
    uint32_t crc_length) {

    /* Table for CRC-16 T10 DIF (Polynomial 0x8BB7) */
    static const uint16_t crc_table[256] = {
        0x0000U, 0x8BB7U, 0x9CD9U, 0x176EU, 0xB205U, 0x39B2U, 0x2EDCU, 0xA56BU, 0xEFBDU, 0x640AU, 0x7364U, 0xF8D3U, 0x5DB8U, 0xD60FU, 0xC161U, 0x4AD6U,
        0x54CDU, 0xDF7AU, 0xC814U, 0x43A3U, 0xE6C8U, 0x6D7FU, 0x7A11U, 0xF1A6U, 0xBB70U, 0x30C7U, 0x27A9U, 0xAC1EU, 0x0975U, 0x82C2U, 0x95ACU, 0x1E1BU,
        0xA99AU, 0x222DU, 0x3543U, 0xBEF4U, 0x1B9FU, 0x9028U, 0x8746U, 0x0CF1U, 0x4627U, 0xCD90U, 0xDAFEU, 0x5149U, 0xF422U, 0x7F95U, 0x68FBU, 0xE34CU,
        0xFD57U, 0x76E0U, 0x618EU, 0xEA39U, 0x4F52U, 0xC4E5U, 0xD38BU, 0x583CU, 0x12EAU, 0x995DU, 0x8E33U, 0x0584U, 0xA0EFU, 0x2B58U, 0x3C36U, 0xB781U,
        0xD883U, 0x5334U, 0x445AU, 0xCFEDU, 0x6A86U, 0xE131U, 0xF65FU, 0x7DE8U, 0x373EU, 0xBC89U, 0xABE7U, 0x2050U, 0x853BU, 0x0E8CU, 0x19E2U, 0x9255U,
        0x8C4EU, 0x07F9U, 0x1097U, 0x9B20U, 0x3E4BU, 0xB5FCU, 0xA292U, 0x2925U, 0x63F3U, 0xE844U, 0xFF2AU, 0x749DU, 0xD1F6U, 0x5A41U, 0x4D2FU, 0xC698U,
        0x7119U, 0xFAAEU, 0xEDC0U, 0x6677U, 0xC31CU, 0x48ABU, 0x5FC5U, 0xD472U, 0x9EA4U, 0x1513U, 0x027DU, 0x89CAU, 0x2CA1U, 0xA716U, 0xB078U, 0x3BCFU,
        0x25D4U, 0xAE63U, 0xB90DU, 0x32BAU, 0x97D1U, 0x1C66U, 0x0B08U, 0x80BFU, 0xCA69U, 0x41DEU, 0x56B0U, 0xDD07U, 0x786CU, 0xF3DBU, 0xE4B5U, 0x6F02U,
        0x3AB1U, 0xB106U, 0xA668U, 0x2DDFU, 0x88B4U, 0x0303U, 0x146DU, 0x9FDAU, 0xD50CU, 0x5EBBU, 0x49D5U, 0xC262U, 0x6709U, 0xECBEU, 0xFBD0U, 0x7067U,
        0x6E7CU, 0xE5CBU, 0xF2A5U, 0x7912U, 0xDC79U, 0x57CEU, 0x40A0U, 0xCB17U, 0x81C1U, 0x0A76U, 0x1D18U, 0x96AFU, 0x33C4U, 0xB873U, 0xAF1DU, 0x24AAU,
        0x932BU, 0x189CU, 0x0FF2U, 0x8445U, 0x212EU, 0xAA99U, 0xBDF7U, 0x3640U, 0x7C96U, 0xF721U, 0xE04FU, 0x6BF8U, 0xCE93U, 0x4524U, 0x524AU, 0xD9FDU,
        0xC7E6U, 0x4C51U, 0x5B3FU, 0xD088U, 0x75E3U, 0xFE54U, 0xE93AU, 0x628DU, 0x285BU, 0xA3ECU, 0xB482U, 0x3F35U, 0x9A5EU, 0x11E9U, 0x0687U, 0x8D30U,
        0xE232U, 0x6985U, 0x7EEBU, 0xF55CU, 0x5037U, 0xDB80U, 0xCCEEU, 0x4759U, 0x0D8FU, 0x8638U, 0x9156U, 0x1AE1U, 0xBF8AU, 0x343DU, 0x2353U, 0xA8E4U,
        0xB6FFU, 0x3D48U, 0x2A26U, 0xA191U, 0x04FAU, 0x8F4DU, 0x9823U, 0x1394U, 0x5942U, 0xD2F5U, 0xC59BU, 0x4E2CU, 0xEB47U, 0x60F0U, 0x779EU, 0xFC29U,
        0x4BA8U, 0xC01FU, 0xD771U, 0x5CC6U, 0xF9ADU, 0x721AU, 0x6574U, 0xEEC3U, 0xA415U, 0x2FA2U, 0x38CCU, 0xB37BU, 0x1610U, 0x9DA7U, 0x8AC9U, 0x017EU,
        0x1F65U, 0x94D2U, 0x83BCU, 0x080BU, 0xAD60U, 0x26D7U, 0x31B9U, 0xBA0EU, 0xF0D8U, 0x7B6FU, 0x6C01U, 0xE7B6U, 0x42DDU, 0xC96AU, 0xDE04U, 0x55B3U
    };

    return Crc16_base(
               crc_table,
               crc_data_ptr,
               crc_length,
               INITIAL_CRC16_VALUE,
               FINAL_XOR_VALUE,
               REFLECTED_OUTPUT,
               REFLECTED_INPUT,
               false
           );
}