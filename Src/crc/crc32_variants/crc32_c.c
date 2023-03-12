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

#include "crc32_c.h"

#include "crc32_base.h"

#define INITIAL_CRC32_VALUE (0xFFFFFFFFU)
#define FINAL_XOR_VALUE (0xFFFFFFFFU)
#define REFLECTED_OUTPUT (true)
#define REFLECTED_INPUT (true)

uint32_t
Crc32_c(
    const uint8_t* crc_data_ptr,
    uint32_t crc_length,
    bool final_xor) {

    /* CRC32-C (Castagnoli) (Polynomial 0x1EDC6F41) */
    static const uint32_t crc_table[256] = {
        0x00000000U, 0x1EDC6F41U, 0x3DB8DE82U, 0x2364B1C3U, 0x7B71BD04U, 0x65ADD245U, 0x46C96386U, 0x58150CC7U,
        0xF6E37A08U, 0xE83F1549U, 0xCB5BA48AU, 0xD587CBCBU, 0x8D92C70CU, 0x934EA84DU, 0xB02A198EU, 0xAEF676CFU,
        0xF31A9B51U, 0xEDC6F410U, 0xCEA245D3U, 0xD07E2A92U, 0x886B2655U, 0x96B74914U, 0xB5D3F8D7U, 0xAB0F9796U,
        0x05F9E159U, 0x1B258E18U, 0x38413FDBU, 0x269D509AU, 0x7E885C5DU, 0x6054331CU, 0x433082DFU, 0x5DECED9EU,
        0xF8E959E3U, 0xE63536A2U, 0xC5518761U, 0xDB8DE820U, 0x8398E4E7U, 0x9D448BA6U, 0xBE203A65U, 0xA0FC5524U,
        0x0E0A23EBU, 0x10D64CAAU, 0x33B2FD69U, 0x2D6E9228U, 0x757B9EEFU, 0x6BA7F1AEU, 0x48C3406DU, 0x561F2F2CU,
        0x0BF3C2B2U, 0x152FADF3U, 0x364B1C30U, 0x28977371U, 0x70827FB6U, 0x6E5E10F7U, 0x4D3AA134U, 0x53E6CE75U,
        0xFD10B8BAU, 0xE3CCD7FBU, 0xC0A86638U, 0xDE740979U, 0x866105BEU, 0x98BD6AFFU, 0xBBD9DB3CU, 0xA505B47DU,
        0xEF0EDC87U, 0xF1D2B3C6U, 0xD2B60205U, 0xCC6A6D44U, 0x947F6183U, 0x8AA30EC2U, 0xA9C7BF01U, 0xB71BD040U,
        0x19EDA68FU, 0x0731C9CEU, 0x2455780DU, 0x3A89174CU, 0x629C1B8BU, 0x7C4074CAU, 0x5F24C509U, 0x41F8AA48U,
        0x1C1447D6U, 0x02C82897U, 0x21AC9954U, 0x3F70F615U, 0x6765FAD2U, 0x79B99593U, 0x5ADD2450U, 0x44014B11U,
        0xEAF73DDEU, 0xF42B529FU, 0xD74FE35CU, 0xC9938C1DU, 0x918680DAU, 0x8F5AEF9BU, 0xAC3E5E58U, 0xB2E23119U,
        0x17E78564U, 0x093BEA25U, 0x2A5F5BE6U, 0x348334A7U, 0x6C963860U, 0x724A5721U, 0x512EE6E2U, 0x4FF289A3U,
        0xE104FF6CU, 0xFFD8902DU, 0xDCBC21EEU, 0xC2604EAFU, 0x9A754268U, 0x84A92D29U, 0xA7CD9CEAU, 0xB911F3ABU,
        0xE4FD1E35U, 0xFA217174U, 0xD945C0B7U, 0xC799AFF6U, 0x9F8CA331U, 0x8150CC70U, 0xA2347DB3U, 0xBCE812F2U,
        0x121E643DU, 0x0CC20B7CU, 0x2FA6BABFU, 0x317AD5FEU, 0x696FD939U, 0x77B3B678U, 0x54D707BBU, 0x4A0B68FAU,
        0xC0C1D64FU, 0xDE1DB90EU, 0xFD7908CDU, 0xE3A5678CU, 0xBBB06B4BU, 0xA56C040AU, 0x8608B5C9U, 0x98D4DA88U,
        0x3622AC47U, 0x28FEC306U, 0x0B9A72C5U, 0x15461D84U, 0x4D531143U, 0x538F7E02U, 0x70EBCFC1U, 0x6E37A080U,
        0x33DB4D1EU, 0x2D07225FU, 0x0E63939CU, 0x10BFFCDDU, 0x48AAF01AU, 0x56769F5BU, 0x75122E98U, 0x6BCE41D9U,
        0xC5383716U, 0xDBE45857U, 0xF880E994U, 0xE65C86D5U, 0xBE498A12U, 0xA095E553U, 0x83F15490U, 0x9D2D3BD1U,
        0x38288FACU, 0x26F4E0EDU, 0x0590512EU, 0x1B4C3E6FU, 0x435932A8U, 0x5D855DE9U, 0x7EE1EC2AU, 0x603D836BU,
        0xCECBF5A4U, 0xD0179AE5U, 0xF3732B26U, 0xEDAF4467U, 0xB5BA48A0U, 0xAB6627E1U, 0x88029622U, 0x96DEF963U,
        0xCB3214FDU, 0xD5EE7BBCU, 0xF68ACA7FU, 0xE856A53EU, 0xB043A9F9U, 0xAE9FC6B8U, 0x8DFB777BU, 0x9327183AU,
        0x3DD16EF5U, 0x230D01B4U, 0x0069B077U, 0x1EB5DF36U, 0x46A0D3F1U, 0x587CBCB0U, 0x7B180D73U, 0x65C46232U,
        0x2FCF0AC8U, 0x31136589U, 0x1277D44AU, 0x0CABBB0BU, 0x54BEB7CCU, 0x4A62D88DU, 0x6906694EU, 0x77DA060FU,
        0xD92C70C0U, 0xC7F01F81U, 0xE494AE42U, 0xFA48C103U, 0xA25DCDC4U, 0xBC81A285U, 0x9FE51346U, 0x81397C07U,
        0xDCD59199U, 0xC209FED8U, 0xE16D4F1BU, 0xFFB1205AU, 0xA7A42C9DU, 0xB97843DCU, 0x9A1CF21FU, 0x84C09D5EU,
        0x2A36EB91U, 0x34EA84D0U, 0x178E3513U, 0x09525A52U, 0x51475695U, 0x4F9B39D4U, 0x6CFF8817U, 0x7223E756U,
        0xD726532BU, 0xC9FA3C6AU, 0xEA9E8DA9U, 0xF442E2E8U, 0xAC57EE2FU, 0xB28B816EU, 0x91EF30ADU, 0x8F335FECU,
        0x21C52923U, 0x3F194662U, 0x1C7DF7A1U, 0x02A198E0U, 0x5AB49427U, 0x4468FB66U, 0x670C4AA5U, 0x79D025E4U,
        0x243CC87AU, 0x3AE0A73BU, 0x198416F8U, 0x075879B9U, 0x5F4D757EU, 0x41911A3FU, 0x62F5ABFCU, 0x7C29C4BDU,
        0xD2DFB272U, 0xCC03DD33U, 0xEF676CF0U, 0xF1BB03B1U, 0xA9AE0F76U, 0xB7726037U, 0x9416D1F4U, 0x8ACABEB5U
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