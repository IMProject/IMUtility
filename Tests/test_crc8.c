#include "crc8.h"
#include "crc8_8h2f.h"
#include "crc8_base.h"
#include "crc8_cdma2000.h"
#include "crc8_darc.h"
#include "crc8_dvb_s2.h"
#include "crc8_ebu.h"
#include "crc8_icode.h"
#include "crc8_itu.h"
#include "crc8_maxim.h"
#include "crc8_rohc.h"
#include "crc8_sae_j1850.h"
#include "crc8_sae_j1850_zero.h"
#include "crc8_wcdma.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Crc8);

static uint8_t message1[] = { 0x00U, 0x00U, 0x00U, 0x00U };
static uint8_t message2[] = { 0xF2U, 0x01U, 0x83U };
static uint8_t message3[] = { 0x0FU, 0xAAU, 0x00U, 0x55U };
static uint8_t message4[] = { 0x00U, 0xFFU, 0x55U, 0x11U };
static uint8_t message5[] = { 0x33U, 0x22U, 0x55U, 0xAAU, 0xBBU, 0xCCU, 0xDDU, 0xEEU, 0xFFU };
static uint8_t message6[] = { 0x92U, 0x6BU, 0x55U };
static uint8_t message7[] = { 0xFFU, 0xFFU, 0xFFU, 0xFFU };

TEST_SETUP(Crc8) {
}

TEST_TEAR_DOWN(Crc8) {
}

TEST_GROUP_RUNNER(Crc8) {
    RUN_TEST_CASE(Crc8, Crc8Base_tableCalculator);
    RUN_TEST_CASE(Crc8, Crc8);
    RUN_TEST_CASE(Crc8, Crc8_8h2f);
    RUN_TEST_CASE(Crc8, Crc8_cdma2000);
    RUN_TEST_CASE(Crc8, Crc8_darc);
    RUN_TEST_CASE(Crc8, Crc8_dvbS2);
    RUN_TEST_CASE(Crc8, Crc8_ebu);
    RUN_TEST_CASE(Crc8, Crc8_icode);
    RUN_TEST_CASE(Crc8, Crc8_itu);
    RUN_TEST_CASE(Crc8, Crc8_maxim);
    RUN_TEST_CASE(Crc8, Crc8_rohc);
    RUN_TEST_CASE(Crc8, Crc8_saeJ1850);
    RUN_TEST_CASE(Crc8, Crc8_saeJ1850Zero);
    RUN_TEST_CASE(Crc8, Crc8_wcdma);
}

TEST(Crc8, Crc8Base_tableCalculator) {
    /* Table for CRC-8 8H2F (Polynomial 0x2F) */
    const uint8_t crc_table_8h2f[256] = {
        0x00U, 0x2FU, 0x5EU, 0x71U, 0xBCU, 0x93U, 0xE2U, 0xCDU, 0x57U, 0x78U, 0x09U, 0x26U, 0xEBU, 0xC4U, 0xB5U, 0x9AU,
        0xAEU, 0x81U, 0xF0U, 0xDFU, 0x12U, 0x3DU, 0x4CU, 0x63U, 0xF9U, 0xD6U, 0xA7U, 0x88U, 0x45U, 0x6AU, 0x1BU, 0x34U,
        0x73U, 0x5CU, 0x2DU, 0x02U, 0xCFU, 0xE0U, 0x91U, 0xBEU, 0x24U, 0x0BU, 0x7AU, 0x55U, 0x98U, 0xB7U, 0xC6U, 0xE9U,
        0xDDU, 0xF2U, 0x83U, 0xACU, 0x61U, 0x4EU, 0x3FU, 0x10U, 0x8AU, 0xA5U, 0xD4U, 0xFBU, 0x36U, 0x19U, 0x68U, 0x47U,
        0xE6U, 0xC9U, 0xB8U, 0x97U, 0x5AU, 0x75U, 0x04U, 0x2BU, 0xB1U, 0x9EU, 0xEFU, 0xC0U, 0x0DU, 0x22U, 0x53U, 0x7CU,
        0x48U, 0x67U, 0x16U, 0x39U, 0xF4U, 0xDBU, 0xAAU, 0x85U, 0x1FU, 0x30U, 0x41U, 0x6EU, 0xA3U, 0x8CU, 0xFDU, 0xD2U,
        0x95U, 0xBAU, 0xCBU, 0xE4U, 0x29U, 0x06U, 0x77U, 0x58U, 0xC2U, 0xEDU, 0x9CU, 0xB3U, 0x7EU, 0x51U, 0x20U, 0x0FU,
        0x3BU, 0x14U, 0x65U, 0x4AU, 0x87U, 0xA8U, 0xD9U, 0xF6U, 0x6CU, 0x43U, 0x32U, 0x1DU, 0xD0U, 0xFFU, 0x8EU, 0xA1U,
        0xE3U, 0xCCU, 0xBDU, 0x92U, 0x5FU, 0x70U, 0x01U, 0x2EU, 0xB4U, 0x9BU, 0xEAU, 0xC5U, 0x08U, 0x27U, 0x56U, 0x79U,
        0x4DU, 0x62U, 0x13U, 0x3CU, 0xF1U, 0xDEU, 0xAFU, 0x80U, 0x1AU, 0x35U, 0x44U, 0x6BU, 0xA6U, 0x89U, 0xF8U, 0xD7U,
        0x90U, 0xBFU, 0xCEU, 0xE1U, 0x2CU, 0x03U, 0x72U, 0x5DU, 0xC7U, 0xE8U, 0x99U, 0xB6U, 0x7BU, 0x54U, 0x25U, 0x0AU,
        0x3EU, 0x11U, 0x60U, 0x4FU, 0x82U, 0xADU, 0xDCU, 0xF3U, 0x69U, 0x46U, 0x37U, 0x18U, 0xD5U, 0xFAU, 0x8BU, 0xA4U,
        0x05U, 0x2AU, 0x5BU, 0x74U, 0xB9U, 0x96U, 0xE7U, 0xC8U, 0x52U, 0x7DU, 0x0CU, 0x23U, 0xEEU, 0xC1U, 0xB0U, 0x9FU,
        0xABU, 0x84U, 0xF5U, 0xDAU, 0x17U, 0x38U, 0x49U, 0x66U, 0xFCU, 0xD3U, 0xA2U, 0x8DU, 0x40U, 0x6FU, 0x1EU, 0x31U,
        0x76U, 0x59U, 0x28U, 0x07U, 0xCAU, 0xE5U, 0x94U, 0xBBU, 0x21U, 0x0EU, 0x7FU, 0x50U, 0x9DU, 0xB2U, 0xC3U, 0xECU,
        0xD8U, 0xF7U, 0x86U, 0xA9U, 0x64U, 0x4BU, 0x3AU, 0x15U, 0x8FU, 0xA0U, 0xD1U, 0xFEU, 0x33U, 0x1CU, 0x6DU, 0x42U
    };

    uint8_t polynomial = 0x2F;
    uint8_t crc_table_calc[256];

    Crc8Base_tableCalculator(polynomial, crc_table_calc);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(crc_table_8h2f, crc_table_calc, sizeof(crc_table_calc));

    /* Table for CRC-8 SAE J1850  (Polynomial 0x1D)*/
    const uint8_t crc_table_sae_j1850[256] = {
        0x00U, 0x1DU, 0x3AU, 0x27U, 0x74U, 0x69U, 0x4EU, 0x53U, 0xE8U, 0xF5U, 0xD2U, 0xCFU, 0x9CU, 0x81U, 0xA6U, 0xBBU,
        0xCDU, 0xD0U, 0xF7U, 0xEAU, 0xB9U, 0xA4U, 0x83U, 0x9EU, 0x25U, 0x38U, 0x1FU, 0x02U, 0x51U, 0x4CU, 0x6BU, 0x76U,
        0x87U, 0x9AU, 0xBDU, 0xA0U, 0xF3U, 0xEEU, 0xC9U, 0xD4U, 0x6FU, 0x72U, 0x55U, 0x48U, 0x1BU, 0x06U, 0x21U, 0x3CU,
        0x4AU, 0x57U, 0x70U, 0x6DU, 0x3EU, 0x23U, 0x04U, 0x19U, 0xA2U, 0xBFU, 0x98U, 0x85U, 0xD6U, 0xCBU, 0xECU, 0xF1U,
        0x13U, 0x0EU, 0x29U, 0x34U, 0x67U, 0x7AU, 0x5DU, 0x40U, 0xFBU, 0xE6U, 0xC1U, 0xDCU, 0x8FU, 0x92U, 0xB5U, 0xA8U,
        0xDEU, 0xC3U, 0xE4U, 0xF9U, 0xAAU, 0xB7U, 0x90U, 0x8DU, 0x36U, 0x2BU, 0x0CU, 0x11U, 0x42U, 0x5FU, 0x78U, 0x65U,
        0x94U, 0x89U, 0xAEU, 0xB3U, 0xE0U, 0xFDU, 0xDAU, 0xC7U, 0x7CU, 0x61U, 0x46U, 0x5BU, 0x08U, 0x15U, 0x32U, 0x2FU,
        0x59U, 0x44U, 0x63U, 0x7EU, 0x2DU, 0x30U, 0x17U, 0x0AU, 0xB1U, 0xACU, 0x8BU, 0x96U, 0xC5U, 0xD8U, 0xFFU, 0xE2U,
        0x26U, 0x3BU, 0x1CU, 0x01U, 0x52U, 0x4FU, 0x68U, 0x75U, 0xCEU, 0xD3U, 0xF4U, 0xE9U, 0xBAU, 0xA7U, 0x80U, 0x9DU,
        0xEBU, 0xF6U, 0xD1U, 0xCCU, 0x9FU, 0x82U, 0xA5U, 0xB8U, 0x03U, 0x1EU, 0x39U, 0x24U, 0x77U, 0x6AU, 0x4DU, 0x50U,
        0xA1U, 0xBCU, 0x9BU, 0x86U, 0xD5U, 0xC8U, 0xEFU, 0xF2U, 0x49U, 0x54U, 0x73U, 0x6EU, 0x3DU, 0x20U, 0x07U, 0x1AU,
        0x6CU, 0x71U, 0x56U, 0x4BU, 0x18U, 0x05U, 0x22U, 0x3FU, 0x84U, 0x99U, 0xBEU, 0xA3U, 0xF0U, 0xEDU, 0xCAU, 0xD7U,
        0x35U, 0x28U, 0x0FU, 0x12U, 0x41U, 0x5CU, 0x7BU, 0x66U, 0xDDU, 0xC0U, 0xE7U, 0xFAU, 0xA9U, 0xB4U, 0x93U, 0x8EU,
        0xF8U, 0xE5U, 0xC2U, 0xDFU, 0x8CU, 0x91U, 0xB6U, 0xABU, 0x10U, 0x0DU, 0x2AU, 0x37U, 0x64U, 0x79U, 0x5EU, 0x43U,
        0xB2U, 0xAFU, 0x88U, 0x95U, 0xC6U, 0xDBU, 0xFCU, 0xE1U, 0x5AU, 0x47U, 0x60U, 0x7DU, 0x2EU, 0x33U, 0x14U, 0x09U,
        0x7FU, 0x62U, 0x45U, 0x58U, 0x0BU, 0x16U, 0x31U, 0x2CU, 0x97U, 0x8AU, 0xADU, 0xB0U, 0xE3U, 0xFEU, 0xD9U, 0xC4U
    };

    polynomial = 0x1D;
    Crc8Base_tableCalculator(polynomial, crc_table_calc);
    TEST_ASSERT_EQUAL_HEX8_ARRAY(crc_table_sae_j1850, crc_table_calc, sizeof(crc_table_calc));
}

TEST(Crc8, Crc8) {
    TEST_ASSERT_EQUAL_HEX8(0x00U, Crc8(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x2FU, Crc8(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xB1U, Crc8(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x11U, Crc8(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x59U, Crc8(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xB1U, Crc8(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xDEU, Crc8(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8(&message5[0], 2U, NULL_PTR);
    crc_result = Crc8(&message5[2], 5U, &crc_result);
    crc_result = Crc8(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x59U, crc_result);
}

TEST(Crc8, Crc8_8h2f) {
    TEST_ASSERT_EQUAL_HEX8(0x12U, Crc8_8h2f(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xC2U, Crc8_8h2f(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xC6U, Crc8_8h2f(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x77U, Crc8_8h2f(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x11U, Crc8_8h2f(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x33U, Crc8_8h2f(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x6CU, Crc8_8h2f(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_8h2f(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc8_8h2f(&message5[2], 5U, false, &crc_result);
    crc_result = Crc8_8h2f(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x11U, crc_result);
}

TEST(Crc8, Crc8_cdma2000) {
    TEST_ASSERT_EQUAL_HEX8(0xAFU, Crc8_cdma2000(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xCBU, Crc8_cdma2000(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xA9U, Crc8_cdma2000(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xAFU, Crc8_cdma2000(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x3CU, Crc8_cdma2000(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xD7U, Crc8_cdma2000(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x0CU, Crc8_cdma2000(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_cdma2000(&message5[0], 2U, NULL_PTR);
    crc_result = Crc8_cdma2000(&message5[2], 5U, &crc_result);
    crc_result = Crc8_cdma2000(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x3CU, crc_result);
}

TEST(Crc8, Crc8_darc) {
    TEST_ASSERT_EQUAL_HEX8(0x00U, Crc8_darc(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x0DU, Crc8_darc(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x4FU, Crc8_darc(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xE2U, Crc8_darc(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x99U, Crc8_darc(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x43U, Crc8_darc(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x03U, Crc8_darc(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_darc(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc8_darc(&message5[2], 5U, false, &crc_result);
    crc_result = Crc8_darc(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x99U, crc_result);
}

TEST(Crc8, Crc8_dvbS2) {
    TEST_ASSERT_EQUAL_HEX8(0x00U, Crc8_dvbS2(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x1AU, Crc8_dvbS2(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x72U, Crc8_dvbS2(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xEDU, Crc8_dvbS2(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x77U, Crc8_dvbS2(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xA9U, Crc8_dvbS2(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x21U, Crc8_dvbS2(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_dvbS2(&message5[0], 2U, NULL_PTR);
    crc_result = Crc8_dvbS2(&message5[2], 5U, &crc_result);
    crc_result = Crc8_dvbS2(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x77U, crc_result);
}

TEST(Crc8, Crc8_ebu) {
    TEST_ASSERT_EQUAL_HEX8(0x65U, Crc8_ebu(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x90U, Crc8_ebu(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x57U, Crc8_ebu(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x18U, Crc8_ebu(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x42U, Crc8_ebu(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x3DU, Crc8_ebu(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xD1U, Crc8_ebu(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_ebu(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc8_ebu(&message5[2], 5U, false, &crc_result);
    crc_result = Crc8_ebu(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x42U, crc_result);
}

TEST(Crc8, Crc8_icode) {
    TEST_ASSERT_EQUAL_HEX8(0x81U, Crc8_icode(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xCBU, Crc8_icode(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xA1U, Crc8_icode(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x60U, Crc8_icode(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xFEU, Crc8_icode(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x70U, Crc8_icode(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xACU, Crc8_icode(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_icode(&message5[0], 2U, NULL_PTR);
    crc_result = Crc8_icode(&message5[2], 5U, &crc_result);
    crc_result = Crc8_icode(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xFEU, crc_result);
}

TEST(Crc8, Crc8_itu) {
    TEST_ASSERT_EQUAL_HEX8(0x55U, Crc8_itu(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x7AU, Crc8_itu(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xE4U, Crc8_itu(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x44U, Crc8_itu(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x0CU, Crc8_itu(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xE4U, Crc8_itu(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x8BU, Crc8_itu(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_itu(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc8_itu(&message5[2], 5U, false, &crc_result);
    crc_result = Crc8_itu(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x0CU, crc_result);
}

TEST(Crc8, Crc8_maxim) {
    TEST_ASSERT_EQUAL_HEX8(0x00U, Crc8_maxim(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x68U, Crc8_maxim(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xE2U, Crc8_maxim(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x99U, Crc8_maxim(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xEBU, Crc8_maxim(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xFAU, Crc8_maxim(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x8DU, Crc8_maxim(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_maxim(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc8_maxim(&message5[2], 5U, false, &crc_result);
    crc_result = Crc8_maxim(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xEBU, crc_result);
}

TEST(Crc8, Crc8_rohc) {
    TEST_ASSERT_EQUAL_HEX8(0x8BU, Crc8_rohc(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xA8U, Crc8_rohc(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x96U, Crc8_rohc(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x8BU, Crc8_rohc(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x1DU, Crc8_rohc(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x30U, Crc8_rohc(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xF0U, Crc8_rohc(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_rohc(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc8_rohc(&message5[2], 5U, false, &crc_result);
    crc_result = Crc8_rohc(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x1DU, crc_result);
}

TEST(Crc8, Crc8_saeJ1850) {
    TEST_ASSERT_EQUAL_HEX8(0x59U, Crc8_saeJ1850(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x37U, Crc8_saeJ1850(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x79U, Crc8_saeJ1850(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xB8U, Crc8_saeJ1850(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xCBU, Crc8_saeJ1850(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x8CU, Crc8_saeJ1850(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x74U, Crc8_saeJ1850(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_saeJ1850(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc8_saeJ1850(&message5[2], 5U, false, &crc_result);
    crc_result = Crc8_saeJ1850(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xCBU, crc_result);
}

TEST(Crc8, Crc8_saeJ1850Zero) {
    TEST_ASSERT_EQUAL_HEX8(0x00U, Crc8_saeJ1850Zero(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xC6U, Crc8_saeJ1850Zero(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x20U, Crc8_saeJ1850Zero(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xE1U, Crc8_saeJ1850Zero(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xB7U, Crc8_saeJ1850Zero(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x7DU, Crc8_saeJ1850Zero(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x2DU, Crc8_saeJ1850Zero(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_saeJ1850Zero(&message5[0], 2U, NULL_PTR);
    crc_result = Crc8_saeJ1850Zero(&message5[2], 5U, &crc_result);
    crc_result = Crc8_saeJ1850Zero(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xB7U, crc_result);
}

TEST(Crc8, Crc8_wcdma) {
    TEST_ASSERT_EQUAL_HEX8(0x00U, Crc8_wcdma(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x76U, Crc8_wcdma(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x28U, Crc8_wcdma(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0x50U, Crc8_wcdma(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xF9U, Crc8_wcdma(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xE7U, Crc8_wcdma(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX8(0xC5U, Crc8_wcdma(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint8_t crc_result = Crc8_wcdma(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc8_wcdma(&message5[2], 5U, false, &crc_result);
    crc_result = Crc8_wcdma(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xF9U, crc_result);
}
