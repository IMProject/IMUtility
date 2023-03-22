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

#include "crc32_d.h"

#include "crc32_base.h"

#define INITIAL_CRC32_VALUE (0xFFFFFFFFU)
#define FINAL_XOR_VALUE (0xFFFFFFFFU)
#define REFLECTED_OUTPUT (true)
#define REFLECTED_INPUT (true)

uint32_t
Crc32_d(
    const uint8_t* crc_data_ptr,
    uint32_t crc_length,
    bool final_xor) {

    /* CRC32-D (Polynomial 0xA833982B) */
    static const uint32_t crc_table[256] = {
        0x00000000U, 0xA833982BU, 0xF854A87DU, 0x50673056U, 0x589AC8D1U, 0xF0A950FAU, 0xA0CE60ACU, 0x08FDF887U,
        0xB13591A2U, 0x19060989U, 0x496139DFU, 0xE152A1F4U, 0xE9AF5973U, 0x419CC158U, 0x11FBF10EU, 0xB9C86925U,
        0xCA58BB6FU, 0x626B2344U, 0x320C1312U, 0x9A3F8B39U, 0x92C273BEU, 0x3AF1EB95U, 0x6A96DBC3U, 0xC2A543E8U,
        0x7B6D2ACDU, 0xD35EB2E6U, 0x833982B0U, 0x2B0A1A9BU, 0x23F7E21CU, 0x8BC47A37U, 0xDBA34A61U, 0x7390D24AU,
        0x3C82EEF5U, 0x94B176DEU, 0xC4D64688U, 0x6CE5DEA3U, 0x64182624U, 0xCC2BBE0FU, 0x9C4C8E59U, 0x347F1672U,
        0x8DB77F57U, 0x2584E77CU, 0x75E3D72AU, 0xDDD04F01U, 0xD52DB786U, 0x7D1E2FADU, 0x2D791FFBU, 0x854A87D0U,
        0xF6DA559AU, 0x5EE9CDB1U, 0x0E8EFDE7U, 0xA6BD65CCU, 0xAE409D4BU, 0x06730560U, 0x56143536U, 0xFE27AD1DU,
        0x47EFC438U, 0xEFDC5C13U, 0xBFBB6C45U, 0x1788F46EU, 0x1F750CE9U, 0xB74694C2U, 0xE721A494U, 0x4F123CBFU,
        0x7905DDEAU, 0xD13645C1U, 0x81517597U, 0x2962EDBCU, 0x219F153BU, 0x89AC8D10U, 0xD9CBBD46U, 0x71F8256DU,
        0xC8304C48U, 0x6003D463U, 0x3064E435U, 0x98577C1EU, 0x90AA8499U, 0x38991CB2U, 0x68FE2CE4U, 0xC0CDB4CFU,
        0xB35D6685U, 0x1B6EFEAEU, 0x4B09CEF8U, 0xE33A56D3U, 0xEBC7AE54U, 0x43F4367FU, 0x13930629U, 0xBBA09E02U,
        0x0268F727U, 0xAA5B6F0CU, 0xFA3C5F5AU, 0x520FC771U, 0x5AF23FF6U, 0xF2C1A7DDU, 0xA2A6978BU, 0x0A950FA0U,
        0x4587331FU, 0xEDB4AB34U, 0xBDD39B62U, 0x15E00349U, 0x1D1DFBCEU, 0xB52E63E5U, 0xE54953B3U, 0x4D7ACB98U,
        0xF4B2A2BDU, 0x5C813A96U, 0x0CE60AC0U, 0xA4D592EBU, 0xAC286A6CU, 0x041BF247U, 0x547CC211U, 0xFC4F5A3AU,
        0x8FDF8870U, 0x27EC105BU, 0x778B200DU, 0xDFB8B826U, 0xD74540A1U, 0x7F76D88AU, 0x2F11E8DCU, 0x872270F7U,
        0x3EEA19D2U, 0x96D981F9U, 0xC6BEB1AFU, 0x6E8D2984U, 0x6670D103U, 0xCE434928U, 0x9E24797EU, 0x3617E155U,
        0xF20BBBD4U, 0x5A3823FFU, 0x0A5F13A9U, 0xA26C8B82U, 0xAA917305U, 0x02A2EB2EU, 0x52C5DB78U, 0xFAF64353U,
        0x433E2A76U, 0xEB0DB25DU, 0xBB6A820BU, 0x13591A20U, 0x1BA4E2A7U, 0xB3977A8CU, 0xE3F04ADAU, 0x4BC3D2F1U,
        0x385300BBU, 0x90609890U, 0xC007A8C6U, 0x683430EDU, 0x60C9C86AU, 0xC8FA5041U, 0x989D6017U, 0x30AEF83CU,
        0x89669119U, 0x21550932U, 0x71323964U, 0xD901A14FU, 0xD1FC59C8U, 0x79CFC1E3U, 0x29A8F1B5U, 0x819B699EU,
        0xCE895521U, 0x66BACD0AU, 0x36DDFD5CU, 0x9EEE6577U, 0x96139DF0U, 0x3E2005DBU, 0x6E47358DU, 0xC674ADA6U,
        0x7FBCC483U, 0xD78F5CA8U, 0x87E86CFEU, 0x2FDBF4D5U, 0x27260C52U, 0x8F159479U, 0xDF72A42FU, 0x77413C04U,
        0x04D1EE4EU, 0xACE27665U, 0xFC854633U, 0x54B6DE18U, 0x5C4B269FU, 0xF478BEB4U, 0xA41F8EE2U, 0x0C2C16C9U,
        0xB5E47FECU, 0x1DD7E7C7U, 0x4DB0D791U, 0xE5834FBAU, 0xED7EB73DU, 0x454D2F16U, 0x152A1F40U, 0xBD19876BU,
        0x8B0E663EU, 0x233DFE15U, 0x735ACE43U, 0xDB695668U, 0xD394AEEFU, 0x7BA736C4U, 0x2BC00692U, 0x83F39EB9U,
        0x3A3BF79CU, 0x92086FB7U, 0xC26F5FE1U, 0x6A5CC7CAU, 0x62A13F4DU, 0xCA92A766U, 0x9AF59730U, 0x32C60F1BU,
        0x4156DD51U, 0xE965457AU, 0xB902752CU, 0x1131ED07U, 0x19CC1580U, 0xB1FF8DABU, 0xE198BDFDU, 0x49AB25D6U,
        0xF0634CF3U, 0x5850D4D8U, 0x0837E48EU, 0xA0047CA5U, 0xA8F98422U, 0x00CA1C09U, 0x50AD2C5FU, 0xF89EB474U,
        0xB78C88CBU, 0x1FBF10E0U, 0x4FD820B6U, 0xE7EBB89DU, 0xEF16401AU, 0x4725D831U, 0x1742E867U, 0xBF71704CU,
        0x06B91969U, 0xAE8A8142U, 0xFEEDB114U, 0x56DE293FU, 0x5E23D1B8U, 0xF6104993U, 0xA67779C5U, 0x0E44E1EEU,
        0x7DD433A4U, 0xD5E7AB8FU, 0x85809BD9U, 0x2DB303F2U, 0x254EFB75U, 0x8D7D635EU, 0xDD1A5308U, 0x7529CB23U,
        0xCCE1A206U, 0x64D23A2DU, 0x34B50A7BU, 0x9C869250U, 0x947B6AD7U, 0x3C48F2FCU, 0x6C2FC2AAU, 0xC41C5A81U
    };

    return Crc32Base(
               crc_table,
               crc_data_ptr,
               crc_length,
               INITIAL_CRC32_VALUE,
               FINAL_XOR_VALUE,
               REFLECTED_OUTPUT,
               REFLECTED_INPUT,
               final_xor
           );
}