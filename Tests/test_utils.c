#include "utils.h"

#include "unity.h"
#include "unity_fixture.h"

#include <string.h>

TEST_GROUP(Utils);

static const uint8_t test_data_1[] = {
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
    RUN_TEST_CASE(Utils, Utils_QuickUint32Pow10);
    RUN_TEST_CASE(Utils, Utils_StringToUint32);
    RUN_TEST_CASE(Utils, Utils_SwapElements);
    RUN_TEST_CASE(Utils, Utils_SerializeBlobBE);
    RUN_TEST_CASE(Utils, Utils_DeserializeBlobBE);
    RUN_TEST_CASE(Utils, Utils_SerializeBlobLE);
    RUN_TEST_CASE(Utils, Utils_DeserializeBlobLE);
    RUN_TEST_CASE(Utils, Utils_BigEndianSerializeDeserialize);
    RUN_TEST_CASE(Utils, Utils_LittleEndianSerializeDeserialize);
}

TEST(Utils, Utils_QuickUint32Pow10) {
    uint32_t result = 0U;
    uint32_t expected = 1U;

    for (uint8_t i = 0U; i < 10U; ++i) {
        TEST_ASSERT_TRUE(Utils_QuickUint32Pow10(i, &result));
        TEST_ASSERT_EQUAL_UINT32(result, expected);
        expected *= 10U;
    }

    TEST_ASSERT_FALSE(Utils_QuickUint32Pow10(10U, &result));
}

TEST(Utils, Utils_StringToUint32) {
    uint32_t ui32_number = 0U;

    TEST_ASSERT_TRUE(Utils_StringToUint32("39", 2U, &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 39U);

    TEST_ASSERT_TRUE(Utils_StringToUint32("0", 1U, &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 0U);

    TEST_ASSERT_TRUE(Utils_StringToUint32("2165217", 7U, &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 2165217U);

    char number_string[] = "1234567890";
    TEST_ASSERT_TRUE(Utils_StringToUint32(number_string, strlen(number_string), &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 1234567890U);

    char max_uint32_number_string[] = "4294967295";
    TEST_ASSERT_TRUE(Utils_StringToUint32(max_uint32_number_string, strlen(max_uint32_number_string), &ui32_number));
    TEST_ASSERT_EQUAL_UINT32(ui32_number, 4294967295U);

    char overflow_1_uint32_number_string[] = "4294967296";
    TEST_ASSERT_FALSE(Utils_StringToUint32(overflow_1_uint32_number_string, strlen(overflow_1_uint32_number_string), &ui32_number));

    char overflow_2_uint32_number_string[] = "5294967295";
    TEST_ASSERT_FALSE(Utils_StringToUint32(overflow_2_uint32_number_string, strlen(overflow_2_uint32_number_string), &ui32_number));

    char not_a_number_string[] = "A";
    TEST_ASSERT_FALSE(Utils_StringToUint32(not_a_number_string, strlen(not_a_number_string), &ui32_number));


    char not_a_number_2_string[] = "1A1";
    TEST_ASSERT_FALSE(Utils_StringToUint32(not_a_number_2_string, strlen(not_a_number_2_string), &ui32_number));

    char not_a_number_3_string[] = "123456789A";
    TEST_ASSERT_FALSE(Utils_StringToUint32(not_a_number_3_string, strlen(not_a_number_3_string), &ui32_number));

    char not_a_number_4_string[] = "429496729A";
    TEST_ASSERT_FALSE(Utils_StringToUint32(not_a_number_4_string, strlen(not_a_number_4_string), &ui32_number));
}

TEST(Utils, Utils_SwapElements) {
    {
        int a = 3;
        int b = 4;
        Utils_SwapElements((uint8_t*)&a, (uint8_t*)&b, sizeof(int));
        TEST_ASSERT_EQUAL_INT(a, 4);
        TEST_ASSERT_EQUAL_INT(b, 3);
    }
    {
        double a = 3.1;
        double b = 4.2;
        Utils_SwapElements((uint8_t*)&a, (uint8_t*)&b, sizeof(double));
        TEST_ASSERT_EQUAL_DOUBLE(a, 4.2);
        TEST_ASSERT_EQUAL_DOUBLE(b, 3.1);
    }
}

TEST(Utils, Utils_SerializeBlobBE) {
    const size_t size = 50;
    uint8_t result_data[size];
    Utils_SerializeBlobBE(result_data, test_data_1, size);

    for (uint32_t i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL_INT(result_data[i], test_data_1[i]);
    }
}

TEST(Utils, Utils_DeserializeBlobBE) {
    const size_t size = 50;
    uint8_t result_data[size];
    Utils_DeserializeBlobBE(test_data_1, result_data, size);

    for (uint32_t i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL_INT(result_data[i], test_data_1[i]);
    }
}

TEST(Utils, Utils_SerializeBlobLE) {
    const size_t size = 50;
    uint8_t result_data[size];
    Utils_SerializeBlobLE(result_data, test_data_1, size);

    for (uint32_t i = 0, j = (size - 1); i < size; ++i, --j) {
        TEST_ASSERT_EQUAL_INT(result_data[i], test_data_1[j]);
    }
}

TEST(Utils, Utils_DeserializeBlobLE) {
    const size_t size = 50;
    uint8_t result_data[size];
    Utils_DeserializeBlobLE(test_data_1, result_data, size);

    for (uint32_t i = 0, j = (size - 1); i < size; ++i, --j) {
        TEST_ASSERT_EQUAL_INT(result_data[i], test_data_1[j]);
    }
}

TEST(Utils, Utils_BigEndianSerializeDeserialize) {
    const size_t size = 50;
    uint8_t result_data_serialize[size];
    uint8_t result_data_deserialize[size];
    Utils_SerializeBlobBE(result_data_serialize, test_data_1, size);
    Utils_DeserializeBlobBE(result_data_serialize, result_data_deserialize, size);

    for (uint32_t i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL_INT(result_data_deserialize[i], test_data_1[i]);
    }
}

TEST(Utils, Utils_LittleEndianSerializeDeserialize) {
    const size_t size = 50;
    uint8_t result_data_serialize[size];
    uint8_t result_data_deserialize[size];
    Utils_SerializeBlobLE(result_data_serialize, test_data_1, size);
    Utils_DeserializeBlobLE(result_data_serialize, result_data_deserialize, size);

    for (uint32_t i = 0; i < size; ++i) {
        TEST_ASSERT_EQUAL_INT(result_data_deserialize[i], test_data_1[i]);
    }
}
