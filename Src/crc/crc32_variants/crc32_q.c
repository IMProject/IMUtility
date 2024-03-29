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

#include "crc32_q.h"

#include "crc32_base.h"

#define INITIAL_CRC32_VALUE (0x0U)
#define FINAL_XOR_VALUE (0x0U)
#define REFLECTED_OUTPUT (false)
#define REFLECTED_INPUT (false)
#define FINAL_XOR (false)

uint32_t
Crc32_q(
    const uint8_t* crc_data_ptr,
    uint32_t crc_length,
    const uint32_t* last_crc_ptr) {

    /* CRC32-Q (Polynomial 0x4C11DB7) */
    static const uint32_t crc_table[256] = {
        0x00000000U, 0x814141ABU, 0x83C3C2FDU, 0x02828356U, 0x86C6C451U, 0x078785FAU, 0x050506ACU, 0x84444707U,
        0x8CCCC909U, 0x0D8D88A2U, 0x0F0F0BF4U, 0x8E4E4A5FU, 0x0A0A0D58U, 0x8B4B4CF3U, 0x89C9CFA5U, 0x08888E0EU,
        0x98D8D3B9U, 0x19999212U, 0x1B1B1144U, 0x9A5A50EFU, 0x1E1E17E8U, 0x9F5F5643U, 0x9DDDD515U, 0x1C9C94BEU,
        0x14141AB0U, 0x95555B1BU, 0x97D7D84DU, 0x169699E6U, 0x92D2DEE1U, 0x13939F4AU, 0x11111C1CU, 0x90505DB7U,
        0xB0F0E6D9U, 0x31B1A772U, 0x33332424U, 0xB272658FU, 0x36362288U, 0xB7776323U, 0xB5F5E075U, 0x34B4A1DEU,
        0x3C3C2FD0U, 0xBD7D6E7BU, 0xBFFFED2DU, 0x3EBEAC86U, 0xBAFAEB81U, 0x3BBBAA2AU, 0x3939297CU, 0xB87868D7U,
        0x28283560U, 0xA96974CBU, 0xABEBF79DU, 0x2AAAB636U, 0xAEEEF131U, 0x2FAFB09AU, 0x2D2D33CCU, 0xAC6C7267U,
        0xA4E4FC69U, 0x25A5BDC2U, 0x27273E94U, 0xA6667F3FU, 0x22223838U, 0xA3637993U, 0xA1E1FAC5U, 0x20A0BB6EU,
        0xE0A08C19U, 0x61E1CDB2U, 0x63634EE4U, 0xE2220F4FU, 0x66664848U, 0xE72709E3U, 0xE5A58AB5U, 0x64E4CB1EU,
        0x6C6C4510U, 0xED2D04BBU, 0xEFAF87EDU, 0x6EEEC646U, 0xEAAA8141U, 0x6BEBC0EAU, 0x696943BCU, 0xE8280217U,
        0x78785FA0U, 0xF9391E0BU, 0xFBBB9D5DU, 0x7AFADCF6U, 0xFEBE9BF1U, 0x7FFFDA5AU, 0x7D7D590CU, 0xFC3C18A7U,
        0xF4B496A9U, 0x75F5D702U, 0x77775454U, 0xF63615FFU, 0x727252F8U, 0xF3331353U, 0xF1B19005U, 0x70F0D1AEU,
        0x50506AC0U, 0xD1112B6BU, 0xD393A83DU, 0x52D2E996U, 0xD696AE91U, 0x57D7EF3AU, 0x55556C6CU, 0xD4142DC7U,
        0xDC9CA3C9U, 0x5DDDE262U, 0x5F5F6134U, 0xDE1E209FU, 0x5A5A6798U, 0xDB1B2633U, 0xD999A565U, 0x58D8E4CEU,
        0xC888B979U, 0x49C9F8D2U, 0x4B4B7B84U, 0xCA0A3A2FU, 0x4E4E7D28U, 0xCF0F3C83U, 0xCD8DBFD5U, 0x4CCCFE7EU,
        0x44447070U, 0xC50531DBU, 0xC787B28DU, 0x46C6F326U, 0xC282B421U, 0x43C3F58AU, 0x414176DCU, 0xC0003777U,
        0x40005999U, 0xC1411832U, 0xC3C39B64U, 0x4282DACFU, 0xC6C69DC8U, 0x4787DC63U, 0x45055F35U, 0xC4441E9EU,
        0xCCCC9090U, 0x4D8DD13BU, 0x4F0F526DU, 0xCE4E13C6U, 0x4A0A54C1U, 0xCB4B156AU, 0xC9C9963CU, 0x4888D797U,
        0xD8D88A20U, 0x5999CB8BU, 0x5B1B48DDU, 0xDA5A0976U, 0x5E1E4E71U, 0xDF5F0FDAU, 0xDDDD8C8CU, 0x5C9CCD27U,
        0x54144329U, 0xD5550282U, 0xD7D781D4U, 0x5696C07FU, 0xD2D28778U, 0x5393C6D3U, 0x51114585U, 0xD050042EU,
        0xF0F0BF40U, 0x71B1FEEBU, 0x73337DBDU, 0xF2723C16U, 0x76367B11U, 0xF7773ABAU, 0xF5F5B9ECU, 0x74B4F847U,
        0x7C3C7649U, 0xFD7D37E2U, 0xFFFFB4B4U, 0x7EBEF51FU, 0xFAFAB218U, 0x7BBBF3B3U, 0x793970E5U, 0xF878314EU,
        0x68286CF9U, 0xE9692D52U, 0xEBEBAE04U, 0x6AAAEFAFU, 0xEEEEA8A8U, 0x6FAFE903U, 0x6D2D6A55U, 0xEC6C2BFEU,
        0xE4E4A5F0U, 0x65A5E45BU, 0x6727670DU, 0xE66626A6U, 0x622261A1U, 0xE363200AU, 0xE1E1A35CU, 0x60A0E2F7U,
        0xA0A0D580U, 0x21E1942BU, 0x2363177DU, 0xA22256D6U, 0x266611D1U, 0xA727507AU, 0xA5A5D32CU, 0x24E49287U,
        0x2C6C1C89U, 0xAD2D5D22U, 0xAFAFDE74U, 0x2EEE9FDFU, 0xAAAAD8D8U, 0x2BEB9973U, 0x29691A25U, 0xA8285B8EU,
        0x38780639U, 0xB9394792U, 0xBBBBC4C4U, 0x3AFA856FU, 0xBEBEC268U, 0x3FFF83C3U, 0x3D7D0095U, 0xBC3C413EU,
        0xB4B4CF30U, 0x35F58E9BU, 0x37770DCDU, 0xB6364C66U, 0x32720B61U, 0xB3334ACAU, 0xB1B1C99CU, 0x30F08837U,
        0x10503359U, 0x911172F2U, 0x9393F1A4U, 0x12D2B00FU, 0x9696F708U, 0x17D7B6A3U, 0x155535F5U, 0x9414745EU,
        0x9C9CFA50U, 0x1DDDBBFBU, 0x1F5F38ADU, 0x9E1E7906U, 0x1A5A3E01U, 0x9B1B7FAAU, 0x9999FCFCU, 0x18D8BD57U,
        0x8888E0E0U, 0x09C9A14BU, 0x0B4B221DU, 0x8A0A63B6U, 0x0E4E24B1U, 0x8F0F651AU, 0x8D8DE64CU, 0x0CCCA7E7U,
        0x044429E9U, 0x85056842U, 0x8787EB14U, 0x06C6AABFU, 0x8282EDB8U, 0x03C3AC13U, 0x01412F45U, 0x80006EEEU
    };

    uint32_t crc_initial_value = INITIAL_CRC32_VALUE;

    if (NULL_PTR != last_crc_ptr) {
        crc_initial_value = *last_crc_ptr;
    }

    return Crc32Base(
               crc_table,
               crc_data_ptr,
               crc_length,
               crc_initial_value,
               FINAL_XOR_VALUE,
               REFLECTED_OUTPUT,
               REFLECTED_INPUT,
               FINAL_XOR
           );
}
