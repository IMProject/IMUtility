#include "crc32.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Crc32);

static uint8_t message1[] = { 0x00U, 0x00U, 0x00U, 0x00U };
static uint8_t message2[] = { 0xF2U, 0x01U, 0x83U };
static uint8_t message3[] = { 0x0FU, 0xAAU, 0x00U, 0x55U };
static uint8_t message4[] = { 0x00U, 0xFFU, 0x55U, 0x11U };
static uint8_t message5[] = { 0x33U, 0x22U, 0x55U, 0xAAU, 0xBBU, 0xCCU, 0xDDU, 0xEEU, 0xFFU };
static uint8_t message6[] = { 0x92U, 0x6BU, 0x55U };
static uint8_t message7[] = { 0xFFU, 0xFFU, 0xFFU, 0xFFU };

static uint32_t init_value = 0xFFFFFFFFU;
static uint32_t crc_xor_value = 0xFFFFFFFFU;

TEST_SETUP(Crc32) {
}

TEST_TEAR_DOWN(Crc32) {
}

TEST_GROUP_RUNNER(Crc32) {
    RUN_TEST_CASE(Crc32, CalculateCRC32_Reflect_output_and_input);
    RUN_TEST_CASE(Crc32, CalculateCRC32_Reflect_input);
    RUN_TEST_CASE(Crc32, CalculateCRC32_Reflect_output);
    RUN_TEST_CASE(Crc32, CalculateCRC32_Without_finish_xor);
}

TEST(Crc32, CalculateCRC32_Reflect_output_and_input) {
    TEST_ASSERT_EQUAL_HEX32(0x2144DF1CU, CalculateCRC32(message1, sizeof(message1), init_value, crc_xor_value, true, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0x24AB9D77U, CalculateCRC32(message2, sizeof(message2), init_value, crc_xor_value, true, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xB6C9B287U, CalculateCRC32(message3, sizeof(message3), init_value, crc_xor_value, true, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0x32A06212U, CalculateCRC32(message4, sizeof(message4), init_value, crc_xor_value, true, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xB0AE863DU, CalculateCRC32(message5, sizeof(message5), init_value, crc_xor_value, true, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0x9CDEA29BU, CalculateCRC32(message6, sizeof(message6), init_value, crc_xor_value, true, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, CalculateCRC32(message7, sizeof(message7), init_value, crc_xor_value, true, true,
                            true));
}

TEST(Crc32, CalculateCRC32_Reflect_input) {
    TEST_ASSERT_EQUAL_HEX32(0x38FB2284U, CalculateCRC32(message1, sizeof(message1), init_value, crc_xor_value, false, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xEEB9D524U, CalculateCRC32(message2, sizeof(message2), init_value, crc_xor_value, false, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xE14D936DU, CalculateCRC32(message3, sizeof(message3), init_value, crc_xor_value, false, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0x4846054CU, CalculateCRC32(message4, sizeof(message4), init_value, crc_xor_value, false, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xBC61750DU, CalculateCRC32(message5, sizeof(message5), init_value, crc_xor_value, false, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xD9457B39U, CalculateCRC32(message6, sizeof(message6), init_value, crc_xor_value, false, true,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, CalculateCRC32(message7, sizeof(message7), init_value, crc_xor_value, false, true,
                            true));
}

TEST(Crc32, CalculateCRC32_Reflect_output) {
    TEST_ASSERT_EQUAL_HEX32(0x2144DF1CU, CalculateCRC32(message1, sizeof(message1), init_value, crc_xor_value, true, false,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0x53677982U, CalculateCRC32(message2, sizeof(message2), init_value, crc_xor_value, true, false,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xFB566F16U, CalculateCRC32(message3, sizeof(message3), init_value, crc_xor_value, true, false,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0x2857B480U, CalculateCRC32(message4, sizeof(message4), init_value, crc_xor_value, true, false,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xBD39C06BU, CalculateCRC32(message5, sizeof(message5), init_value, crc_xor_value, true, false,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0x616B4732U, CalculateCRC32(message6, sizeof(message6), init_value, crc_xor_value, true, false,
                            true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFFU, CalculateCRC32(message7, sizeof(message7), init_value, crc_xor_value, true, false,
                            true));
}

TEST(Crc32, CalculateCRC32_Without_finish_xor) {
    TEST_ASSERT_EQUAL_HEX32(0xDEBB20E3U, CalculateCRC32(message1, sizeof(message1), init_value, crc_xor_value, true, true,
                            false));
    TEST_ASSERT_EQUAL_HEX32(0xDB546288U, CalculateCRC32(message2, sizeof(message2), init_value, crc_xor_value, true, true,
                            false));
    TEST_ASSERT_EQUAL_HEX32(0x49364D78U, CalculateCRC32(message3, sizeof(message3), init_value, crc_xor_value, true, true,
                            false));
    TEST_ASSERT_EQUAL_HEX32(0xCD5F9DEDU, CalculateCRC32(message4, sizeof(message4), init_value, crc_xor_value, true, true,
                            false));
    TEST_ASSERT_EQUAL_HEX32(0x4F5179C2U, CalculateCRC32(message5, sizeof(message5), init_value, crc_xor_value, true, true,
                            false));
    TEST_ASSERT_EQUAL_HEX32(0x63215D64U, CalculateCRC32(message6, sizeof(message6), init_value, crc_xor_value, true, true,
                            false));
    TEST_ASSERT_EQUAL_HEX32(0x00000000U, CalculateCRC32(message7, sizeof(message7), init_value, crc_xor_value, true, true,
                            false));
}
