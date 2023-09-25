#include "crc16_base.h"
#include "crc16_a.h"
#include "crc16_arc.h"
#include "crc16_aug_ccit.h"
#include "crc16_buypass.h"
#include "crc16_ccit_false.h"
#include "crc16_ccit_zero.h"
#include "crc16_cdma2000.h"
#include "crc16_dds110.h"
#include "crc16_dect_r.h"
#include "crc16_dect_x.h"
#include "crc16_dnp.h"
#include "crc16_en_13757.h"
#include "crc16_genibus.h"
#include "crc16_kermit.h"
#include "crc16_maxim.h"
#include "crc16_mcrf4xx.h"
#include "crc16_modbus.h"
#include "crc16_riello.h"
#include "crc16_t10_dif.h"
#include "crc16_teledisk.h"
#include "crc16_tms37157.h"
#include "crc16_usb.h"
#include "crc16_x_25.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Crc16);

static uint8_t message1[] = { 0x00U, 0x00U, 0x00U, 0x00U };
static uint8_t message2[] = { 0xF2U, 0x01U, 0x83U };
static uint8_t message3[] = { 0x0FU, 0xAAU, 0x00U, 0x55U };
static uint8_t message4[] = { 0x00U, 0xFFU, 0x55U, 0x11U };
static uint8_t message5[] = { 0x33U, 0x22U, 0x55U, 0xAAU, 0xBBU, 0xCCU, 0xDDU, 0xEEU, 0xFFU };
static uint8_t message6[] = { 0x92U, 0x6BU, 0x55U };
static uint8_t message7[] = { 0xFFU, 0xFFU, 0xFFU, 0xFFU };

TEST_SETUP(Crc16) {
}

TEST_TEAR_DOWN(Crc16) {
}

TEST_GROUP_RUNNER(Crc16) {
    RUN_TEST_CASE(Crc16, Crc16Base_tableCalculator);
    RUN_TEST_CASE(Crc16, Crc16_a);
    RUN_TEST_CASE(Crc16, Crc16_arc);
    RUN_TEST_CASE(Crc16, Crc16_augCcit);
    RUN_TEST_CASE(Crc16, Crc16_buypass);
    RUN_TEST_CASE(Crc16, Crc16_ccitFalse);
    RUN_TEST_CASE(Crc16, Crc16_ccitZero);
    RUN_TEST_CASE(Crc16, Crc16_cdma2000);
    RUN_TEST_CASE(Crc16, Crc16_dds110);
    RUN_TEST_CASE(Crc16, Crc16_dectR);
    RUN_TEST_CASE(Crc16, Crc16_dectX);
    RUN_TEST_CASE(Crc16, Crc16_dnp);
    RUN_TEST_CASE(Crc16, Crc16_en13757);
    RUN_TEST_CASE(Crc16, Crc16_genibus);
    RUN_TEST_CASE(Crc16, Crc16_kermit);
    RUN_TEST_CASE(Crc16, Crc16_maxim);
    RUN_TEST_CASE(Crc16, Crc16_mcrf4xx);
    RUN_TEST_CASE(Crc16, Crc16_modbus);
    RUN_TEST_CASE(Crc16, Crc16_riello);
    RUN_TEST_CASE(Crc16, Crc16_t10Dif);
    RUN_TEST_CASE(Crc16, Crc16_teledisk);
    RUN_TEST_CASE(Crc16, Crc16_tms37157);
    RUN_TEST_CASE(Crc16, Crc16_usb);
    RUN_TEST_CASE(Crc16, Crc16_x25);
}

TEST(Crc16, Crc16Base_tableCalculator) {
    /* Table for CRC-16 CCIT ZERO (Polynomial 0x1021) */
    const uint16_t crc_table_ccit_zero[256] = {
        0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50A5U, 0x60C6U, 0x70E7U, 0x8108U, 0x9129U, 0xA14AU, 0xB16BU, 0xC18CU, 0xD1ADU, 0xE1CEU, 0xF1EFU,
        0x1231U, 0x0210U, 0x3273U, 0x2252U, 0x52B5U, 0x4294U, 0x72F7U, 0x62D6U, 0x9339U, 0x8318U, 0xB37BU, 0xA35AU, 0xD3BDU, 0xC39CU, 0xF3FFU, 0xE3DEU,
        0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64E6U, 0x74C7U, 0x44A4U, 0x5485U, 0xA56AU, 0xB54BU, 0x8528U, 0x9509U, 0xE5EEU, 0xF5CFU, 0xC5ACU, 0xD58DU,
        0x3653U, 0x2672U, 0x1611U, 0x0630U, 0x76D7U, 0x66F6U, 0x5695U, 0x46B4U, 0xB75BU, 0xA77AU, 0x9719U, 0x8738U, 0xF7DFU, 0xE7FEU, 0xD79DU, 0xC7BCU,
        0x48C4U, 0x58E5U, 0x6886U, 0x78A7U, 0x0840U, 0x1861U, 0x2802U, 0x3823U, 0xC9CCU, 0xD9EDU, 0xE98EU, 0xF9AFU, 0x8948U, 0x9969U, 0xA90AU, 0xB92BU,
        0x5AF5U, 0x4AD4U, 0x7AB7U, 0x6A96U, 0x1A71U, 0x0A50U, 0x3A33U, 0x2A12U, 0xDBFDU, 0xCBDCU, 0xFBBFU, 0xEB9EU, 0x9B79U, 0x8B58U, 0xBB3BU, 0xAB1AU,
        0x6CA6U, 0x7C87U, 0x4CE4U, 0x5CC5U, 0x2C22U, 0x3C03U, 0x0C60U, 0x1C41U, 0xEDAEU, 0xFD8FU, 0xCDECU, 0xDDCDU, 0xAD2AU, 0xBD0BU, 0x8D68U, 0x9D49U,
        0x7E97U, 0x6EB6U, 0x5ED5U, 0x4EF4U, 0x3E13U, 0x2E32U, 0x1E51U, 0x0E70U, 0xFF9FU, 0xEFBEU, 0xDFDDU, 0xCFFCU, 0xBF1BU, 0xAF3AU, 0x9F59U, 0x8F78U,
        0x9188U, 0x81A9U, 0xB1CAU, 0xA1EBU, 0xD10CU, 0xC12DU, 0xF14EU, 0xE16FU, 0x1080U, 0x00A1U, 0x30C2U, 0x20E3U, 0x5004U, 0x4025U, 0x7046U, 0x6067U,
        0x83B9U, 0x9398U, 0xA3FBU, 0xB3DAU, 0xC33DU, 0xD31CU, 0xE37FU, 0xF35EU, 0x02B1U, 0x1290U, 0x22F3U, 0x32D2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U,
        0xB5EAU, 0xA5CBU, 0x95A8U, 0x8589U, 0xF56EU, 0xE54FU, 0xD52CU, 0xC50DU, 0x34E2U, 0x24C3U, 0x14A0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U,
        0xA7DBU, 0xB7FAU, 0x8799U, 0x97B8U, 0xE75FU, 0xF77EU, 0xC71DU, 0xD73CU, 0x26D3U, 0x36F2U, 0x0691U, 0x16B0U, 0x6657U, 0x7676U, 0x4615U, 0x5634U,
        0xD94CU, 0xC96DU, 0xF90EU, 0xE92FU, 0x99C8U, 0x89E9U, 0xB98AU, 0xA9ABU, 0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18C0U, 0x08E1U, 0x3882U, 0x28A3U,
        0xCB7DU, 0xDB5CU, 0xEB3FU, 0xFB1EU, 0x8BF9U, 0x9BD8U, 0xABBBU, 0xBB9AU, 0x4A75U, 0x5A54U, 0x6A37U, 0x7A16U, 0x0AF1U, 0x1AD0U, 0x2AB3U, 0x3A92U,
        0xFD2EU, 0xED0FU, 0xDD6CU, 0xCD4DU, 0xBDAAU, 0xAD8BU, 0x9DE8U, 0x8DC9U, 0x7C26U, 0x6C07U, 0x5C64U, 0x4C45U, 0x3CA2U, 0x2C83U, 0x1CE0U, 0x0CC1U,
        0xEF1FU, 0xFF3EU, 0xCF5DU, 0xDF7CU, 0xAF9BU, 0xBFBAU, 0x8FD9U, 0x9FF8U, 0x6E17U, 0x7E36U, 0x4E55U, 0x5E74U, 0x2E93U, 0x3EB2U, 0x0ED1U, 0x1EF0U
    };


    uint16_t polynomial = 0x1021;
    uint16_t crc_table_calc[256];

    Crc16Base_tableCalculator(polynomial, crc_table_calc);
    TEST_ASSERT_EQUAL_HEX16_ARRAY(crc_table_ccit_zero, crc_table_calc, 256);

    /* Table for CRC-16 USB (Polynomial 0x8005) */
    const uint16_t crc_table_usb[256] = {
        0x0000U, 0x8005U, 0x800FU, 0x000AU, 0x801BU, 0x001EU, 0x0014U, 0x8011U, 0x8033U, 0x0036U, 0x003CU, 0x8039U, 0x0028U, 0x802DU, 0x8027U, 0x0022U,
        0x8063U, 0x0066U, 0x006CU, 0x8069U, 0x0078U, 0x807DU, 0x8077U, 0x0072U, 0x0050U, 0x8055U, 0x805FU, 0x005AU, 0x804BU, 0x004EU, 0x0044U, 0x8041U,
        0x80C3U, 0x00C6U, 0x00CCU, 0x80C9U, 0x00D8U, 0x80DDU, 0x80D7U, 0x00D2U, 0x00F0U, 0x80F5U, 0x80FFU, 0x00FAU, 0x80EBU, 0x00EEU, 0x00E4U, 0x80E1U,
        0x00A0U, 0x80A5U, 0x80AFU, 0x00AAU, 0x80BBU, 0x00BEU, 0x00B4U, 0x80B1U, 0x8093U, 0x0096U, 0x009CU, 0x8099U, 0x0088U, 0x808DU, 0x8087U, 0x0082U,
        0x8183U, 0x0186U, 0x018CU, 0x8189U, 0x0198U, 0x819DU, 0x8197U, 0x0192U, 0x01B0U, 0x81B5U, 0x81BFU, 0x01BAU, 0x81ABU, 0x01AEU, 0x01A4U, 0x81A1U,
        0x01E0U, 0x81E5U, 0x81EFU, 0x01EAU, 0x81FBU, 0x01FEU, 0x01F4U, 0x81F1U, 0x81D3U, 0x01D6U, 0x01DCU, 0x81D9U, 0x01C8U, 0x81CDU, 0x81C7U, 0x01C2U,
        0x0140U, 0x8145U, 0x814FU, 0x014AU, 0x815BU, 0x015EU, 0x0154U, 0x8151U, 0x8173U, 0x0176U, 0x017CU, 0x8179U, 0x0168U, 0x816DU, 0x8167U, 0x0162U,
        0x8123U, 0x0126U, 0x012CU, 0x8129U, 0x0138U, 0x813DU, 0x8137U, 0x0132U, 0x0110U, 0x8115U, 0x811FU, 0x011AU, 0x810BU, 0x010EU, 0x0104U, 0x8101U,
        0x8303U, 0x0306U, 0x030CU, 0x8309U, 0x0318U, 0x831DU, 0x8317U, 0x0312U, 0x0330U, 0x8335U, 0x833FU, 0x033AU, 0x832BU, 0x032EU, 0x0324U, 0x8321U,
        0x0360U, 0x8365U, 0x836FU, 0x036AU, 0x837BU, 0x037EU, 0x0374U, 0x8371U, 0x8353U, 0x0356U, 0x035CU, 0x8359U, 0x0348U, 0x834DU, 0x8347U, 0x0342U,
        0x03C0U, 0x83C5U, 0x83CFU, 0x03CAU, 0x83DBU, 0x03DEU, 0x03D4U, 0x83D1U, 0x83F3U, 0x03F6U, 0x03FCU, 0x83F9U, 0x03E8U, 0x83EDU, 0x83E7U, 0x03E2U,
        0x83A3U, 0x03A6U, 0x03ACU, 0x83A9U, 0x03B8U, 0x83BDU, 0x83B7U, 0x03B2U, 0x0390U, 0x8395U, 0x839FU, 0x039AU, 0x838BU, 0x038EU, 0x0384U, 0x8381U,
        0x0280U, 0x8285U, 0x828FU, 0x028AU, 0x829BU, 0x029EU, 0x0294U, 0x8291U, 0x82B3U, 0x02B6U, 0x02BCU, 0x82B9U, 0x02A8U, 0x82ADU, 0x82A7U, 0x02A2U,
        0x82E3U, 0x02E6U, 0x02ECU, 0x82E9U, 0x02F8U, 0x82FDU, 0x82F7U, 0x02F2U, 0x02D0U, 0x82D5U, 0x82DFU, 0x02DAU, 0x82CBU, 0x02CEU, 0x02C4U, 0x82C1U,
        0x8243U, 0x0246U, 0x024CU, 0x8249U, 0x0258U, 0x825DU, 0x8257U, 0x0252U, 0x0270U, 0x8275U, 0x827FU, 0x027AU, 0x826BU, 0x026EU, 0x0264U, 0x8261U,
        0x0220U, 0x8225U, 0x822FU, 0x022AU, 0x823BU, 0x023EU, 0x0234U, 0x8231U, 0x8213U, 0x0216U, 0x021CU, 0x8219U, 0x0208U, 0x820DU, 0x8207U, 0x0202U
    };

    polynomial = 0x8005;
    Crc16Base_tableCalculator(polynomial, crc_table_calc);
    TEST_ASSERT_EQUAL_HEX16_ARRAY(crc_table_usb, crc_table_calc, 256);

}

TEST(Crc16, Crc16_a) {
    TEST_ASSERT_EQUAL_HEX16(0x5600U, Crc16_a(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x33D3U, Crc16_a(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x9D7CU, Crc16_a(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x3CB4U, Crc16_a(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x6F1DU, Crc16_a(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x1D00U, Crc16_a(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xA599U, Crc16_a(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_a(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_a(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_a(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x6F1DU, crc_result);
}

TEST(Crc16, Crc16_arc) {
    TEST_ASSERT_EQUAL_HEX16(0x0000U, Crc16_arc(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC2E1U, Crc16_arc(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x0BE3U, Crc16_arc(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x6CCFU, Crc16_arc(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xAE98U, Crc16_arc(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xE24EU, Crc16_arc(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x9401U, Crc16_arc(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_arc(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_arc(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_arc(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xAE98U, crc_result);
}

TEST(Crc16, Crc16_augCcit) {
    TEST_ASSERT_EQUAL_HEX16(0x0E10U, Crc16_augCcit(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x0EE4U, Crc16_augCcit(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xAAF3U, Crc16_augCcit(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x3229U, Crc16_augCcit(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x3942U, Crc16_augCcit(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xDAD5U, Crc16_augCcit(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x97DFU, Crc16_augCcit(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_augCcit(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_augCcit(&message5[2], 5U, &crc_result);
    crc_result = Crc16_augCcit(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x3942U, crc_result);
}

TEST(Crc16, Crc16_buypass) {
    TEST_ASSERT_EQUAL_HEX16(0x0000U, Crc16_buypass(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x89E1U, Crc16_buypass(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC5F6U, Crc16_buypass(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x726FU, Crc16_buypass(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x4FD0U, Crc16_buypass(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF093U, Crc16_buypass(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x8029U, Crc16_buypass(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_buypass(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_buypass(&message5[2], 5U, &crc_result);
    crc_result = Crc16_buypass(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x4FD0U, crc_result);
}

TEST(Crc16, Crc16_ccitFalse) {
    TEST_ASSERT_EQUAL_HEX16(0x84C0U, Crc16_ccitFalse(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xD374U, Crc16_ccitFalse(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x2023U, Crc16_ccitFalse(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xB8F9U, Crc16_ccitFalse(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF53FU, Crc16_ccitFalse(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x0745U, Crc16_ccitFalse(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x1D0FU, Crc16_ccitFalse(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_ccitFalse(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_ccitFalse(&message5[2], 5U, &crc_result);
    crc_result = Crc16_ccitFalse(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xF53FU, crc_result);
}

TEST(Crc16, Crc16_ccitZero) {
    TEST_ASSERT_EQUAL_HEX16(0x0000U, Crc16_ccitZero(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x1FE8U, Crc16_ccitZero(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xA4E3U, Crc16_ccitZero(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x3C39U, Crc16_ccitZero(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xED4DU, Crc16_ccitZero(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xCBD9U, Crc16_ccitZero(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x99CFU, Crc16_ccitZero(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_ccitZero(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_ccitZero(&message5[2], 5U, &crc_result);
    crc_result = Crc16_ccitZero(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xED4DU, crc_result);
}

TEST(Crc16, Crc16_cdma2000) {
    TEST_ASSERT_EQUAL_HEX16(0xA101U, Crc16_cdma2000(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x98F9U, Crc16_cdma2000(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x9658U, Crc16_cdma2000(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x7124U, Crc16_cdma2000(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x2DCBU, Crc16_cdma2000(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x023FU, Crc16_cdma2000(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x8A85U, Crc16_cdma2000(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_cdma2000(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_cdma2000(&message5[2], 5U, &crc_result);
    crc_result = Crc16_cdma2000(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x2DCBU, crc_result);
}

TEST(Crc16, Crc16_dds110) {
    TEST_ASSERT_EQUAL_HEX16(0x00D8U, Crc16_dds110(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xADE1U, Crc16_dds110(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC52EU, Crc16_dds110(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x72B7U, Crc16_dds110(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x2FF7U, Crc16_dds110(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xD493U, Crc16_dds110(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x80F1U, Crc16_dds110(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_dds110(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_dds110(&message5[2], 5U, &crc_result);
    crc_result = Crc16_dds110(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x2FF7U, crc_result);
}

TEST(Crc16, Crc16_dectR) {
    TEST_ASSERT_EQUAL_HEX16(0x0001U, Crc16_dectR(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC746U, Crc16_dectR(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x860AU, Crc16_dectR(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x3C4FU, Crc16_dectR(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xEE45U, Crc16_dectR(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x36FDU, Crc16_dectR(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x983CU, Crc16_dectR(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_dectR(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_dectR(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_dectR(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xEE45U, crc_result);
}

TEST(Crc16, Crc16_dectX) {
    TEST_ASSERT_EQUAL_HEX16(0x0000U, Crc16_dectX(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC747U, Crc16_dectX(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x860BU, Crc16_dectX(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x3C4EU, Crc16_dectX(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xEE44U, Crc16_dectX(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x36FCU, Crc16_dectX(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x983DU, Crc16_dectX(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_dectX(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_dectX(&message5[2], 5U, &crc_result);
    crc_result = Crc16_dectX(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xEE44U, crc_result);
}

TEST(Crc16, Crc16_dnp) {
    TEST_ASSERT_EQUAL_HEX16(0xFFFFU, Crc16_dnp(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x7425U, Crc16_dnp(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x9935U, Crc16_dnp(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xFD1FU, Crc16_dnp(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x9BE3U, Crc16_dnp(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC6FFU, Crc16_dnp(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x7A8FU, Crc16_dnp(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_dnp(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_dnp(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_dnp(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x9BE3U, crc_result);
}

TEST(Crc16, Crc16_en13757) {
    TEST_ASSERT_EQUAL_HEX16(0xFFFFU, Crc16_en13757(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xD754U, Crc16_en13757(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xAD16U, Crc16_en13757(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF72AU, Crc16_en13757(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x7A1FU, Crc16_en13757(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xB31FU, Crc16_en13757(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF15EU, Crc16_en13757(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_en13757(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_en13757(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_en13757(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x7A1FU, crc_result);
}

TEST(Crc16, Crc16_genibus) {
    TEST_ASSERT_EQUAL_HEX16(0x7B3FU, Crc16_genibus(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x2C8BU, Crc16_genibus(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xDFDCU, Crc16_genibus(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x4706U, Crc16_genibus(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x0AC0U, Crc16_genibus(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF8BAU, Crc16_genibus(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xE2F0U, Crc16_genibus(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_genibus(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_genibus(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_genibus(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x0AC0U, crc_result);
}

TEST(Crc16, Crc16_kermit) {
    TEST_ASSERT_EQUAL_HEX16(0x0000U, Crc16_kermit(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x96C7U, Crc16_kermit(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xCB7CU, Crc16_kermit(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x6AB4U, Crc16_kermit(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF191U, Crc16_kermit(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xB814U, Crc16_kermit(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF399U, Crc16_kermit(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_kermit(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_kermit(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_kermit(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xF191U, crc_result);
}

TEST(Crc16, Crc16_maxim) {
    TEST_ASSERT_EQUAL_HEX16(0xFFFFU, Crc16_maxim(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x3D1EU, Crc16_maxim(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF41CU, Crc16_maxim(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x9330U, Crc16_maxim(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x5167U, Crc16_maxim(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x1DB1U, Crc16_maxim(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x6BFEU, Crc16_maxim(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_maxim(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_maxim(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_maxim(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x5167U, crc_result);
}

TEST(Crc16, Crc16_mcrf4xx) {
    TEST_ASSERT_EQUAL_HEX16(0x0321U, Crc16_mcrf4xx(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xAFF4U, Crc16_mcrf4xx(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC85DU, Crc16_mcrf4xx(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x6995U, Crc16_mcrf4xx(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xBF89U, Crc16_mcrf4xx(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x8127U, Crc16_mcrf4xx(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF0B8U, Crc16_mcrf4xx(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_mcrf4xx(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_mcrf4xx(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_mcrf4xx(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xBF89U, crc_result);
}

TEST(Crc16, Crc16_modbus) {
    TEST_ASSERT_EQUAL_HEX16(0x2400U, Crc16_modbus(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x0290U, Crc16_modbus(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x2FE3U, Crc16_modbus(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x48CFU, Crc16_modbus(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x5E92U, Crc16_modbus(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x223FU, Crc16_modbus(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xB001U, Crc16_modbus(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_modbus(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_modbus(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_modbus(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x5E92U, crc_result);
}

TEST(Crc16, Crc16_riello) {
    TEST_ASSERT_EQUAL_HEX16(0x2766U, Crc16_riello(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC281U, Crc16_riello(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xEC1AU, Crc16_riello(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x4DD2U, Crc16_riello(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xB3C8U, Crc16_riello(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xEC52U, Crc16_riello(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xD4FFU, Crc16_riello(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_riello(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_riello(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_riello(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xB3C8U, crc_result);
}

TEST(Crc16, Crc16_t10Dif) {
    TEST_ASSERT_EQUAL_HEX16(0x0000U, Crc16_t10Dif(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x6276U, Crc16_t10Dif(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x9231U, Crc16_t10Dif(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x0FF2U, Crc16_t10Dif(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xA725U, Crc16_t10Dif(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x1A01U, Crc16_t10Dif(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x77B5U, Crc16_t10Dif(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_t10Dif(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_t10Dif(&message5[2], 5U, &crc_result);
    crc_result = Crc16_t10Dif(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xA725U, crc_result);
}

TEST(Crc16, Crc16_teledisk) {
    TEST_ASSERT_EQUAL_HEX16(0x0000U, Crc16_teledisk(message1, sizeof(message1), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x3079U, Crc16_teledisk(message2, sizeof(message2), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x612FU, Crc16_teledisk(message3, sizeof(message3), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF1AEU, Crc16_teledisk(message4, sizeof(message4), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xC07BU, Crc16_teledisk(message5, sizeof(message5), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x50D4U, Crc16_teledisk(message6, sizeof(message6), NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x30B8U, Crc16_teledisk(message7, sizeof(message7), NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_teledisk(&message5[0], 2U, NULL_PTR);
    crc_result = Crc16_teledisk(&message5[2], 5U, &crc_result);
    crc_result = Crc16_teledisk(&message5[7], 2U, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xC07BU, crc_result);
}

TEST(Crc16, Crc16_tms37157) {
    TEST_ASSERT_EQUAL_HEX16(0xF8DFU, Crc16_tms37157(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xBEC8U, Crc16_tms37157(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x33A3U, Crc16_tms37157(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x926BU, Crc16_tms37157(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xF6A9U, Crc16_tms37157(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x901BU, Crc16_tms37157(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x0B46U, Crc16_tms37157(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_tms37157(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_tms37157(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_tms37157(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xF6A9U, crc_result);
}

TEST(Crc16, Crc16_usb) {
    TEST_ASSERT_EQUAL_HEX16(0xDBFFU, Crc16_usb(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xFD6FU, Crc16_usb(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xD01CU, Crc16_usb(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xB730U, Crc16_usb(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xA16DU, Crc16_usb(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0xDDC0U, Crc16_usb(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x4FFEU, Crc16_usb(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_usb(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_usb(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_usb(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0xA16DU, crc_result);
}

TEST(Crc16, Crc16_x25) {
    TEST_ASSERT_EQUAL_HEX16(0xFCDEU, Crc16_x25(message1, sizeof(message1), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x500BU, Crc16_x25(message2, sizeof(message2), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x37A2U, Crc16_x25(message3, sizeof(message3), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x966AU, Crc16_x25(message4, sizeof(message4), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x4076U, Crc16_x25(message5, sizeof(message5), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x7ED8U, Crc16_x25(message6, sizeof(message6), true, NULL_PTR));
    TEST_ASSERT_EQUAL_HEX16(0x0F47U, Crc16_x25(message7, sizeof(message7), true, NULL_PTR));

    // Test with message in chunks
    uint16_t crc_result = Crc16_x25(&message5[0], 2U, false, NULL_PTR);
    crc_result = Crc16_x25(&message5[2], 5U, false, &crc_result);
    crc_result = Crc16_x25(&message5[7], 2U, true, &crc_result);
    TEST_ASSERT_EQUAL_HEX16(0x4076U, crc_result);
}
