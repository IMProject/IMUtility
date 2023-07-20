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

#include "crc16_cdma2000.h"

#include "crc16_base.h"

#define INITIAL_CRC16_VALUE (0xFFFFU)
#define FINAL_XOR_VALUE (0x0U)
#define REFLECTED_OUTPUT (false)
#define REFLECTED_INPUT (false)

uint16_t
Crc16_cdma2000(
    const uint8_t* crc_data_ptr,
    uint32_t crc_length) {

    /* Table for CRC-16 CDMA2000 (Polynomial 0xC867) */
    static const uint16_t crc_table[256] = {
        0x0000U, 0xC867U, 0x58A9U, 0x90CEU, 0xB152U, 0x7935U, 0xE9FBU, 0x219CU, 0xAAC3U, 0x62A4U, 0xF26AU, 0x3A0DU, 0x1B91U, 0xD3F6U, 0x4338U, 0x8B5FU,
        0x9DE1U, 0x5586U, 0xC548U, 0x0D2FU, 0x2CB3U, 0xE4D4U, 0x741AU, 0xBC7DU, 0x3722U, 0xFF45U, 0x6F8BU, 0xA7ECU, 0x8670U, 0x4E17U, 0xDED9U, 0x16BEU,
        0xF3A5U, 0x3BC2U, 0xAB0CU, 0x636BU, 0x42F7U, 0x8A90U, 0x1A5EU, 0xD239U, 0x5966U, 0x9101U, 0x01CFU, 0xC9A8U, 0xE834U, 0x2053U, 0xB09DU, 0x78FAU,
        0x6E44U, 0xA623U, 0x36EDU, 0xFE8AU, 0xDF16U, 0x1771U, 0x87BFU, 0x4FD8U, 0xC487U, 0x0CE0U, 0x9C2EU, 0x5449U, 0x75D5U, 0xBDB2U, 0x2D7CU, 0xE51BU,
        0x2F2DU, 0xE74AU, 0x7784U, 0xBFE3U, 0x9E7FU, 0x5618U, 0xC6D6U, 0x0EB1U, 0x85EEU, 0x4D89U, 0xDD47U, 0x1520U, 0x34BCU, 0xFCDBU, 0x6C15U, 0xA472U,
        0xB2CCU, 0x7AABU, 0xEA65U, 0x2202U, 0x039EU, 0xCBF9U, 0x5B37U, 0x9350U, 0x180FU, 0xD068U, 0x40A6U, 0x88C1U, 0xA95DU, 0x613AU, 0xF1F4U, 0x3993U,
        0xDC88U, 0x14EFU, 0x8421U, 0x4C46U, 0x6DDAU, 0xA5BDU, 0x3573U, 0xFD14U, 0x764BU, 0xBE2CU, 0x2EE2U, 0xE685U, 0xC719U, 0x0F7EU, 0x9FB0U, 0x57D7U,
        0x4169U, 0x890EU, 0x19C0U, 0xD1A7U, 0xF03BU, 0x385CU, 0xA892U, 0x60F5U, 0xEBAAU, 0x23CDU, 0xB303U, 0x7B64U, 0x5AF8U, 0x929FU, 0x0251U, 0xCA36U,
        0x5E5AU, 0x963DU, 0x06F3U, 0xCE94U, 0xEF08U, 0x276FU, 0xB7A1U, 0x7FC6U, 0xF499U, 0x3CFEU, 0xAC30U, 0x6457U, 0x45CBU, 0x8DACU, 0x1D62U, 0xD505U,
        0xC3BBU, 0x0BDCU, 0x9B12U, 0x5375U, 0x72E9U, 0xBA8EU, 0x2A40U, 0xE227U, 0x6978U, 0xA11FU, 0x31D1U, 0xF9B6U, 0xD82AU, 0x104DU, 0x8083U, 0x48E4U,
        0xADFFU, 0x6598U, 0xF556U, 0x3D31U, 0x1CADU, 0xD4CAU, 0x4404U, 0x8C63U, 0x073CU, 0xCF5BU, 0x5F95U, 0x97F2U, 0xB66EU, 0x7E09U, 0xEEC7U, 0x26A0U,
        0x301EU, 0xF879U, 0x68B7U, 0xA0D0U, 0x814CU, 0x492BU, 0xD9E5U, 0x1182U, 0x9ADDU, 0x52BAU, 0xC274U, 0x0A13U, 0x2B8FU, 0xE3E8U, 0x7326U, 0xBB41U,
        0x7177U, 0xB910U, 0x29DEU, 0xE1B9U, 0xC025U, 0x0842U, 0x988CU, 0x50EBU, 0xDBB4U, 0x13D3U, 0x831DU, 0x4B7AU, 0x6AE6U, 0xA281U, 0x324FU, 0xFA28U,
        0xEC96U, 0x24F1U, 0xB43FU, 0x7C58U, 0x5DC4U, 0x95A3U, 0x056DU, 0xCD0AU, 0x4655U, 0x8E32U, 0x1EFCU, 0xD69BU, 0xF707U, 0x3F60U, 0xAFAEU, 0x67C9U,
        0x82D2U, 0x4AB5U, 0xDA7BU, 0x121CU, 0x3380U, 0xFBE7U, 0x6B29U, 0xA34EU, 0x2811U, 0xE076U, 0x70B8U, 0xB8DFU, 0x9943U, 0x5124U, 0xC1EAU, 0x098DU,
        0x1F33U, 0xD754U, 0x479AU, 0x8FFDU, 0xAE61U, 0x6606U, 0xF6C8U, 0x3EAFU, 0xB5F0U, 0x7D97U, 0xED59U, 0x253EU, 0x04A2U, 0xCCC5U, 0x5C0BU, 0x946CU
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
