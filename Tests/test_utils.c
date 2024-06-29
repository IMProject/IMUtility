#include "utils.h"

#include "unity.h"
#include "unity_fixture.h"

#include <string.h>

TEST_GROUP(Utils);

static const byte_t test_data_1[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49
};

TEST_SETUP(Utils) {
}

TEST_TEAR_DOWN(Utils) {
}

TEST_GROUP_RUNNER(Utils) {
    RUN_TEST_CASE(Utils, Utils_stringToUint32);
    RUN_TEST_CASE(Utils, Utils_swapElements);
    RUN_TEST_CASE(Utils, Utils_quickUint32Pow10);

    RUN_TEST_CASE(Utils, Utils_serialize8);
    RUN_TEST_CASE(Utils, Utils_deserialize8);

    RUN_TEST_CASE(Utils, Utils_serializeBlobBE);
    RUN_TEST_CASE(Utils, Utils_serialize32BE);
    RUN_TEST_CASE(Utils, Utils_serialize24BE);
    RUN_TEST_CASE(Utils, Utils_serialize16BE);

    RUN_TEST_CASE(Utils, Utils_deserializeBlobBE);
    RUN_TEST_CASE(Utils, Utils_deserialize32BE);
    RUN_TEST_CASE(Utils, Utils_deserialize24BE);
    RUN_TEST_CASE(Utils, Utils_deserialize16BE);

    RUN_TEST_CASE(Utils, Utils_serializeBlobLE);
    RUN_TEST_CASE(Utils, Utils_serialize32LE);
    RUN_TEST_CASE(Utils, Utils_serialize24LE);
    RUN_TEST_CASE(Utils, Utils_serialize16LE);

    RUN_TEST_CASE(Utils, Utils_deserializeBlobLE);
    RUN_TEST_CASE(Utils, Utils_deserialize32LE);
    RUN_TEST_CASE(Utils, Utils_deserialize24LE);
    RUN_TEST_CASE(Utils, Utils_deserialize16LE);

    RUN_TEST_CASE(Utils, Utils_bigEndianSerializeDeserialize);
    RUN_TEST_CASE(Utils, Utils_littleEndianSerializeDeserialize);

    RUN_TEST_CASE(Utils, Utils_characters);
}

TEST(Utils, Utils_stringToUint32) {
    uint32_t ui32_number = 0U;

    TEST_ASSERT_TRUE(Utils_stringToUint32("39", 2U, &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 39U);

    TEST_ASSERT_TRUE(Utils_stringToUint32("0", 1U, &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 0U);

    TEST_ASSERT_TRUE(Utils_stringToUint32("2165217", 7U, &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 2165217U);

    const char number_string[] = "1234567890";
    TEST_ASSERT_TRUE(Utils_stringToUint32(number_string, strlen(number_string), &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 1234567890U);

    const char max_uint32_number_string[] = "4294967295";
    TEST_ASSERT_TRUE(Utils_stringToUint32(max_uint32_number_string, strlen(max_uint32_number_string), &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 4294967295U);

    const char overflow_1_uint32_number_string[] = "4294967296";
    TEST_ASSERT_FALSE(Utils_stringToUint32(overflow_1_uint32_number_string, strlen(overflow_1_uint32_number_string),
                                           &ui32_number));

    const char overflow_2_uint32_number_string[] = "5294967295";
    TEST_ASSERT_FALSE(Utils_stringToUint32(overflow_2_uint32_number_string, strlen(overflow_2_uint32_number_string),
                                           &ui32_number));

    const char not_a_number_string[] = "A";
    TEST_ASSERT_FALSE(Utils_stringToUint32(not_a_number_string, strlen(not_a_number_string), &ui32_number));

    const char not_a_number_2_string[] = "1A1";
    TEST_ASSERT_FALSE(Utils_stringToUint32(not_a_number_2_string, strlen(not_a_number_2_string), &ui32_number));

    const char not_a_number_3_string[] = "123456789A";
    TEST_ASSERT_FALSE(Utils_stringToUint32(not_a_number_3_string, strlen(not_a_number_3_string), &ui32_number));

    const char not_a_number_4_string[] = "429496729A";
    TEST_ASSERT_FALSE(Utils_stringToUint32(not_a_number_4_string, strlen(not_a_number_4_string), &ui32_number));

    const char number_string_edge_case_1[] = "/";
    TEST_ASSERT_FALSE(Utils_stringToUint32(number_string_edge_case_1, strlen(number_string_edge_case_1), &ui32_number));

    const char number_string_edge_case_2[] = ":";
    TEST_ASSERT_FALSE(Utils_stringToUint32(number_string_edge_case_2, strlen(number_string_edge_case_2), &ui32_number));

    uint8_t force_overflow_check_size = 10U;
    const char number_string_edge_case_3[10U] = "12345A";
    TEST_ASSERT_FALSE(Utils_stringToUint32(number_string_edge_case_3, force_overflow_check_size, &ui32_number));

    const char number_string_edge_case_4[] = "123456789/";
    TEST_ASSERT_FALSE(Utils_stringToUint32(number_string_edge_case_4, strlen(number_string_edge_case_4), &ui32_number));

    const char number_string_edge_case_5[] = "123456789:";
    TEST_ASSERT_FALSE(Utils_stringToUint32(number_string_edge_case_5, strlen(number_string_edge_case_5), &ui32_number));
}

TEST(Utils, Utils_swapElements) {
    {
        int8_t a = 3;
        int8_t b = 4;
        Utils_swapElements((byte_t*)&a, (byte_t*)&b, sizeof(int8_t));
        TEST_ASSERT_EQUAL_INT(a, 4);
        TEST_ASSERT_EQUAL_INT(b, 3);
    }
    {
        float64_t a = 3.1;
        float64_t b = 4.2;
        Utils_swapElements((byte_t*)&a, (byte_t*)&b, sizeof(float64_t));
        TEST_ASSERT_EQUAL_DOUBLE(a, 4.2);
        TEST_ASSERT_EQUAL_DOUBLE(b, 3.1);
    }
    {
        float64_t a[2] = {3.2, 8.4};
        float64_t b[2] = {4.2, 9.4};
        Utils_swapElements((byte_t*)&a, (byte_t*)&b, sizeof(a));
        TEST_ASSERT_EQUAL_DOUBLE(a[0], 4.2);
        TEST_ASSERT_EQUAL_DOUBLE(a[1], 9.4);
        TEST_ASSERT_EQUAL_DOUBLE(b[0], 3.2);
        TEST_ASSERT_EQUAL_DOUBLE(b[1], 8.4);
    }
}

TEST(Utils, Utils_quickUint32Pow10) {
    uint32_t result = 0U;
    uint32_t expected = 1U;

    for (uint8_t i = 0U; i < 10U; ++i) {
        TEST_ASSERT_TRUE(Utils_quickUint32Pow10(i, &result));
        TEST_ASSERT_EQUAL_UINT32(result, expected);
        expected *= 10U;
    }

    TEST_ASSERT_FALSE(Utils_quickUint32Pow10(10U, &result));
}


TEST(Utils, Utils_serialize8) {
    byte_t buffer[10];
    uint8_t value1 = 0x11U;
    uint8_t value2 = 0x22U;
    uint8_t value3 = 0x33U;
    uint8_t value4 = 0x44U;
    Utils_serialize8(&buffer[0], value1);
    Utils_serialize8(&buffer[1], value2);
    Utils_serialize8(&buffer[2], value3);
    Utils_serialize8(&buffer[3], value4);

    TEST_ASSERT_EQUAL_HEX8(buffer[0], 0x11U);
    TEST_ASSERT_EQUAL_HEX8(buffer[1], 0x22U);
    TEST_ASSERT_EQUAL_HEX8(buffer[2], 0x33U);
    TEST_ASSERT_EQUAL_HEX8(buffer[3], 0x44U);
}

TEST(Utils, Utils_deserialize8) {
    uint8_t deserialize_value = 0U;

    deserialize_value = Utils_deserialize8(&test_data_1[0]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x00U);

    deserialize_value = Utils_deserialize8(&test_data_1[1]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x01U);

    deserialize_value = Utils_deserialize8(&test_data_1[2]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x02U);

    deserialize_value = Utils_deserialize8(&test_data_1[3]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x03U);
}

TEST(Utils, Utils_serialize16BE) {
    byte_t buffer[10];
    uint16_t value1 = 0x1122U;
    uint16_t value2 = 0x3344U;
    Utils_serialize16BE(&buffer[0], value1);
    Utils_serialize16BE(&buffer[2], value2);

    TEST_ASSERT_EQUAL_HEX8(buffer[0], 0x11U);
    TEST_ASSERT_EQUAL_HEX8(buffer[1], 0x22U);
    TEST_ASSERT_EQUAL_HEX8(buffer[2], 0x33U);
    TEST_ASSERT_EQUAL_HEX8(buffer[3], 0x44U);
}


TEST(Utils, Utils_serialize24BE) {
    byte_t buffer[10];
    uint32_t value1 = (0x00FFFFFFU & 0x112233U);
    uint32_t value2 = (0x00FFFFFFU & 0x445566U);
    Utils_serialize24BE(&buffer[0], value1);
    Utils_serialize24BE(&buffer[3], value2);

    TEST_ASSERT_EQUAL_HEX8(buffer[0], 0x11U);
    TEST_ASSERT_EQUAL_HEX8(buffer[1], 0x22U);
    TEST_ASSERT_EQUAL_HEX8(buffer[2], 0x33U);
    TEST_ASSERT_EQUAL_HEX8(buffer[3], 0x44U);
    TEST_ASSERT_EQUAL_HEX8(buffer[4], 0x55U);
    TEST_ASSERT_EQUAL_HEX8(buffer[5], 0x66U);
}

TEST(Utils, Utils_serialize32BE) {
    byte_t buffer[10];
    uint32_t value1 = 0x11223344U;
    uint32_t value2 = 0x55667788U;
    Utils_serialize32BE(&buffer[0], value1);
    Utils_serialize32BE(&buffer[4], value2);

    TEST_ASSERT_EQUAL_HEX8(buffer[0], 0x11U);
    TEST_ASSERT_EQUAL_HEX8(buffer[1], 0x22U);
    TEST_ASSERT_EQUAL_HEX8(buffer[2], 0x33U);
    TEST_ASSERT_EQUAL_HEX8(buffer[3], 0x44U);
    TEST_ASSERT_EQUAL_HEX8(buffer[4], 0x55U);
    TEST_ASSERT_EQUAL_HEX8(buffer[5], 0x66U);
    TEST_ASSERT_EQUAL_HEX8(buffer[6], 0x77U);
    TEST_ASSERT_EQUAL_HEX8(buffer[7], 0x88U);
}

TEST(Utils, Utils_serializeBlobBE) {
    const size_t size = 50;
    byte_t result_data[size];
    Utils_serializeBlobBE(result_data, test_data_1, size);

    for (uint32_t i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL_HEX8(result_data[i], test_data_1[i]);
    }
}

TEST(Utils, Utils_deserialize16BE) {
    uint16_t deserialize_value = 0U;

    deserialize_value = Utils_deserialize16BE(&test_data_1[0]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x0001U);

    deserialize_value = Utils_deserialize16BE(&test_data_1[2]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x0203U);
}

TEST(Utils, Utils_deserialize24BE) {
    uint32_t deserialize_value = 0U;

    deserialize_value = Utils_deserialize24BE(&test_data_1[0]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x000102U);

    deserialize_value =  Utils_deserialize24BE(&test_data_1[3]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x030405U);
}

TEST(Utils, Utils_deserialize32BE) {
    uint32_t deserialize_value = 0U;

    deserialize_value = Utils_deserialize32BE(&test_data_1[0]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x00010203U);

    deserialize_value = Utils_deserialize32BE(&test_data_1[4]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x04050607U);
}

TEST(Utils, Utils_deserializeBlobBE) {
    const size_t size = 50;
    byte_t result_data[size];
    Utils_deserializeBlobBE(test_data_1, result_data, size);

    for (uint32_t i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL_HEX8(result_data[i], test_data_1[i]);
    }
}

TEST(Utils, Utils_serialize16LE) {
    byte_t buffer[10];
    uint16_t value1 = 0x1122U;
    uint16_t value2 = 0x3344U;
    Utils_serialize16LE(&buffer[0], value1);
    Utils_serialize16LE(&buffer[2], value2);

    TEST_ASSERT_EQUAL_HEX8(buffer[1], 0x11U);
    TEST_ASSERT_EQUAL_HEX8(buffer[0], 0x22U);
    TEST_ASSERT_EQUAL_HEX8(buffer[3], 0x33U);
    TEST_ASSERT_EQUAL_HEX8(buffer[2], 0x44U);
}

TEST(Utils, Utils_serialize24LE) {
    byte_t buffer[10];
    uint32_t value1 = (0x00FFFFFFU & 0x112233U);
    uint32_t value2 = (0x00FFFFFFU & 0x445566U);
    Utils_serialize24LE(&buffer[0], value1);
    Utils_serialize24LE(&buffer[3], value2);

    TEST_ASSERT_EQUAL_HEX8(buffer[2], 0x11U);
    TEST_ASSERT_EQUAL_HEX8(buffer[1], 0x22U);
    TEST_ASSERT_EQUAL_HEX8(buffer[0], 0x33U);
    TEST_ASSERT_EQUAL_HEX8(buffer[5], 0x44U);
    TEST_ASSERT_EQUAL_HEX8(buffer[4], 0x55U);
    TEST_ASSERT_EQUAL_HEX8(buffer[3], 0x66U);
}

TEST(Utils, Utils_serialize32LE) {
    byte_t buffer[10];
    uint32_t value1 = 0x11223344U;
    uint32_t value2 = 0x55667788U;
    Utils_serialize32LE(&buffer[0], value1);
    Utils_serialize32LE(&buffer[4], value2);

    TEST_ASSERT_EQUAL_HEX8(buffer[3], 0x11U);
    TEST_ASSERT_EQUAL_HEX8(buffer[2], 0x22U);
    TEST_ASSERT_EQUAL_HEX8(buffer[1], 0x33U);
    TEST_ASSERT_EQUAL_HEX8(buffer[0], 0x44U);
    TEST_ASSERT_EQUAL_HEX8(buffer[7], 0x55U);
    TEST_ASSERT_EQUAL_HEX8(buffer[6], 0x66U);
    TEST_ASSERT_EQUAL_HEX8(buffer[5], 0x77U);
    TEST_ASSERT_EQUAL_HEX8(buffer[4], 0x88U);
}

TEST(Utils, Utils_serializeBlobLE) {
    const size_t size = 50;
    byte_t result_data[size];
    Utils_serializeBlobLE(result_data, test_data_1, size);

    for (uint32_t i = 0, j = (size - 1); i < size; ++i, --j) {
        TEST_ASSERT_EQUAL_HEX8(result_data[i], test_data_1[j]);
    }
}

TEST(Utils, Utils_deserialize16LE) {
    uint16_t deserialize_value = 0U;

    deserialize_value = Utils_deserialize16LE(&test_data_1[0]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x0100U);

    deserialize_value = Utils_deserialize16LE(&test_data_1[2]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x0302U);
}

TEST(Utils, Utils_deserialize24LE) {
    uint32_t deserialize_value = 0U;

    deserialize_value = Utils_deserialize24LE(&test_data_1[0]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x020100U);

    deserialize_value =  Utils_deserialize24LE(&test_data_1[3]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x050403U);
}

TEST(Utils, Utils_deserialize32LE) {
    uint32_t deserialize_value = 0U;

    deserialize_value = Utils_deserialize32LE(&test_data_1[0]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x03020100U);

    deserialize_value = Utils_deserialize32LE(&test_data_1[4]);
    TEST_ASSERT_EQUAL_HEX32(deserialize_value, 0x07060504U);
}

TEST(Utils, Utils_deserializeBlobLE) {
    const size_t size = 50;
    byte_t result_data[size];
    Utils_deserializeBlobLE(test_data_1, result_data, size);

    for (uint32_t i = 0, j = (size - 1); i < size; ++i, --j) {
        TEST_ASSERT_EQUAL_HEX8(result_data[i], test_data_1[j]);
    }
}

TEST(Utils, Utils_bigEndianSerializeDeserialize) {
    const size_t size = 50;
    byte_t result_data_serialize[size];
    byte_t result_data_deserialize[size];
    Utils_serializeBlobBE(result_data_serialize, test_data_1, size);
    Utils_deserializeBlobBE(result_data_serialize, result_data_deserialize, size);

    for (uint32_t i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL_HEX8(result_data_deserialize[i], test_data_1[i]);
    }
}

TEST(Utils, Utils_littleEndianSerializeDeserialize) {
    const size_t size = 50;
    byte_t result_data_serialize[size];
    byte_t result_data_deserialize[size];
    Utils_serializeBlobLE(result_data_serialize, test_data_1, size);
    Utils_deserializeBlobLE(result_data_serialize, result_data_deserialize, size);

    for (uint32_t i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL_HEX8(result_data_deserialize[i], test_data_1[i]);
    }
}

TEST(Utils, Utils_characters) {
    TEST_ASSERT_TRUE(Utils_isLowerChar('a'));
    TEST_ASSERT_FALSE(Utils_isLowerChar('B'));
    TEST_ASSERT_FALSE(Utils_isLowerChar(' '));

    TEST_ASSERT_TRUE(Utils_isUpperChar('D'));
    TEST_ASSERT_FALSE(Utils_isUpperChar('c'));
    TEST_ASSERT_FALSE(Utils_isUpperChar(','));

    TEST_ASSERT_TRUE(Utils_isAlpha('z'));
    TEST_ASSERT_TRUE(Utils_isAlpha('e'));
    TEST_ASSERT_FALSE(Utils_isAlpha('*'));
    TEST_ASSERT_FALSE(Utils_isAlpha('?'));
}
