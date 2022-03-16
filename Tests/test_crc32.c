#include "crc32.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Crc32);

uint8_t message1[] = { 0x00, 0x00, 0x00, 0x00 };
uint8_t message2[] = { 0xF2, 0x01, 0x83 };
uint8_t message3[] = { 0x0F, 0xAA, 0x00, 0x55 };
uint8_t message4[] = { 0x00, 0xFF, 0x55, 0x11 };
uint8_t message5[] = { 0x33, 0x22, 0x55, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0XFF };
uint8_t message6[] = { 0x92, 0x6B, 0x55 };
uint8_t message7[] = { 0xFF, 0xFF, 0xFF, 0xFF };

uint32_t init_value = 0xFFFFFFFF;
uint32_t xor_value = 0xFFFFFFFF;

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
    TEST_ASSERT_EQUAL_HEX32(0x2144DF1C, CalculateCRC32(message1, sizeof(message1), init_value, xor_value, true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0x24AB9D77, CalculateCRC32(message2, sizeof(message2), init_value, xor_value, true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xB6C9B287, CalculateCRC32(message3, sizeof(message3), init_value, xor_value, true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0x32A06212, CalculateCRC32(message4, sizeof(message4), init_value, xor_value, true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xB0AE863D, CalculateCRC32(message5, sizeof(message5), init_value, xor_value, true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0x9CDEA29B, CalculateCRC32(message6, sizeof(message6), init_value, xor_value, true, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, CalculateCRC32(message7, sizeof(message7), init_value, xor_value, true, true, true));
}

TEST(Crc32, CalculateCRC32_Reflect_input) {
    TEST_ASSERT_EQUAL_HEX32(0x38FB2284, CalculateCRC32(message1, sizeof(message1), init_value, xor_value, false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xEEB9D524, CalculateCRC32(message2, sizeof(message2), init_value, xor_value, false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xE14D936D, CalculateCRC32(message3, sizeof(message3), init_value, xor_value, false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0x4846054C, CalculateCRC32(message4, sizeof(message4), init_value, xor_value, false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xBC61750D, CalculateCRC32(message5, sizeof(message5), init_value, xor_value, false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xD9457B39, CalculateCRC32(message6, sizeof(message6), init_value, xor_value, false, true, true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, CalculateCRC32(message7, sizeof(message7), init_value, xor_value, false, true, true));
}

TEST(Crc32, CalculateCRC32_Reflect_output) {
    TEST_ASSERT_EQUAL_HEX32(0x2144DF1C, CalculateCRC32(message1, sizeof(message1), init_value, xor_value, true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0x53677982, CalculateCRC32(message2, sizeof(message2), init_value, xor_value, true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0xFB566F16, CalculateCRC32(message3, sizeof(message3), init_value, xor_value, true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0x2857B480, CalculateCRC32(message4, sizeof(message4), init_value, xor_value, true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0xBD39C06B, CalculateCRC32(message5, sizeof(message5), init_value, xor_value, true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0x616B4732, CalculateCRC32(message6, sizeof(message6), init_value, xor_value, true, false, true));
    TEST_ASSERT_EQUAL_HEX32(0xFFFFFFFF, CalculateCRC32(message7, sizeof(message7), init_value, xor_value, true, false, true));
}

TEST(Crc32, CalculateCRC32_Without_finish_xor) {
    TEST_ASSERT_EQUAL_HEX32(0xDEBB20E3, CalculateCRC32(message1, sizeof(message1), init_value, xor_value, true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0xDB546288, CalculateCRC32(message2, sizeof(message2), init_value, xor_value, true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0x49364D78, CalculateCRC32(message3, sizeof(message3), init_value, xor_value, true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0xCD5F9DED, CalculateCRC32(message4, sizeof(message4), init_value, xor_value, true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0x4F5179C2, CalculateCRC32(message5, sizeof(message5), init_value, xor_value, true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0x63215D64, CalculateCRC32(message6, sizeof(message6), init_value, xor_value, true, true, false));
    TEST_ASSERT_EQUAL_HEX32(0x00000000, CalculateCRC32(message7, sizeof(message7), init_value, xor_value, true, true, false));
}
