#include "utils.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Utils);

uint8_t test_data_1[] = {
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
    RUN_TEST_CASE(Utils, Utils_SerializeBlobBE);
    RUN_TEST_CASE(Utils, Utils_DeserializeBlobBE);
    RUN_TEST_CASE(Utils, Utils_SerializeBlobLE);
    RUN_TEST_CASE(Utils, Utils_DeserializeBlobLE);
    RUN_TEST_CASE(Utils, Utils_BigEndianSerializeDeserialize);
    RUN_TEST_CASE(Utils, Utils_LittleEndianSerializeDeserialize);
}

TEST(Utils, Utils_SerializeBlobBE) {
    {
        const size_t size = 50;
        uint8_t result_data[size];
        Utils_SerializeBlobBE(result_data, test_data_1, size);

        for (uint32_t i = 0; i < size; ++i) {
            TEST_ASSERT_EQUAL_INT(result_data[i], test_data_1[i]);
        }
    }
}

TEST(Utils, Utils_DeserializeBlobBE) {
    {
        const size_t size = 50;
        uint8_t result_data[size];
        Utils_DeserializeBlobBE(test_data_1, result_data, size);

        for (uint32_t i = 0; i < size; ++i) {
            TEST_ASSERT_EQUAL_INT(result_data[i], test_data_1[i]);
        }
    }
}

TEST(Utils, Utils_SerializeBlobLE) {
    {
        const size_t size = 50;
        uint8_t result_data[size];
        Utils_SerializeBlobLE(result_data, test_data_1, size);

        for (uint32_t i = 0, j = (size - 1); i < size; ++i, --j) {
            TEST_ASSERT_EQUAL_INT(result_data[i], test_data_1[j]);
        }
    }
}

TEST(Utils, Utils_DeserializeBlobLE) {
    {
        const size_t size = 50;
        uint8_t result_data[size];
        Utils_DeserializeBlobLE(test_data_1, result_data, size);

        for (uint32_t i = 0, j = (size - 1); i < size; ++i, --j) {
            TEST_ASSERT_EQUAL_INT(result_data[i], test_data_1[j]);
        }
    }
}

TEST(Utils, Utils_BigEndianSerializeDeserialize) {
    {
        const size_t size = 50;
        uint8_t result_data_serialize[size];
        uint8_t result_data_deserialize[size];
        Utils_SerializeBlobBE(result_data_serialize, test_data_1, size);
        Utils_DeserializeBlobBE(result_data_serialize, result_data_deserialize, size);

        for (uint32_t i = 0; i < size; ++i) {
            TEST_ASSERT_EQUAL_INT(result_data_deserialize[i], test_data_1[i]);
        }
    }
}

TEST(Utils, Utils_LittleEndianSerializeDeserialize) {
    {
        const size_t size = 50;
        uint8_t result_data_serialize[size];
        uint8_t result_data_deserialize[size];
        Utils_SerializeBlobLE(result_data_serialize, test_data_1, size);
        Utils_DeserializeBlobLE(result_data_serialize, result_data_deserialize, size);

        for (uint32_t i = 0; i < size; ++i) {
            TEST_ASSERT_EQUAL_INT(result_data_deserialize[i], test_data_1[i]);
        }
    }
}
