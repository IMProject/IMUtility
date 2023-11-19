#include "bit_manipulation.h"

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(BitManipulation);

TEST_SETUP(BitManipulation) {
}

TEST_TEAR_DOWN(BitManipulation) {
}

TEST_GROUP_RUNNER(BitManipulation) {
    RUN_TEST_CASE(BitManipulation, BitManipulation_reflect);
    RUN_TEST_CASE(BitManipulation, BitManipulation_bitSet);
    RUN_TEST_CASE(BitManipulation, BitManipulation_setBit);
    RUN_TEST_CASE(BitManipulation, BitManipulation_clearBit);
    RUN_TEST_CASE(BitManipulation, BitManipulation_toggleBit);
}

TEST(BitManipulation, BitManipulation_reflect) {
    const uint32_t data = 0b10110011U;
    uint8_t n_bits = 4U;

    TEST_ASSERT_EQUAL_UINT32(0b1100U, BitManipulation_reflect(data, n_bits));

    n_bits = 2U;
    TEST_ASSERT_EQUAL_UINT32(0b11U, BitManipulation_reflect(data, n_bits));

    n_bits = 3U;
    TEST_ASSERT_EQUAL_UINT32(0b110U, BitManipulation_reflect(data, n_bits));
}

TEST(BitManipulation, BitManipulation_bitSet) {
    const uint32_t data = 0b10110011U;
    bool bit_set;
    TEST_ASSERT_FALSE(BitManipulation_bitSet(data, 32U, &bit_set));
    TEST_ASSERT_FALSE(BitManipulation_bitSet(data, 100U, &bit_set));
    TEST_ASSERT_TRUE(BitManipulation_bitSet(data, 0U, &bit_set));
    TEST_ASSERT_TRUE(bit_set);
    TEST_ASSERT_TRUE(BitManipulation_bitSet(data, 3U, &bit_set));
    TEST_ASSERT_FALSE(bit_set);
    TEST_ASSERT_TRUE(BitManipulation_bitSet(data, 4U, &bit_set));
    TEST_ASSERT_TRUE(bit_set);
}

TEST(BitManipulation, BitManipulation_setBit) {
    const uint32_t data = 0b10110011U;
    uint32_t out_data;
    TEST_ASSERT_FALSE(BitManipulation_setBit(data, 32U, &out_data));
    TEST_ASSERT_FALSE(BitManipulation_setBit(data, 90U, &out_data));
    TEST_ASSERT_TRUE(BitManipulation_setBit(data, 0U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10110011U, out_data);
    TEST_ASSERT_TRUE(BitManipulation_setBit(data, 2U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10110111U, out_data);
    TEST_ASSERT_TRUE(BitManipulation_setBit(data, 3U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10111011U, out_data);
}

TEST(BitManipulation, BitManipulation_clearBit) {
    const uint32_t data = 0b10110011U;
    uint32_t out_data;
    TEST_ASSERT_FALSE(BitManipulation_clearBit(data, 32U, &out_data));
    TEST_ASSERT_FALSE(BitManipulation_clearBit(data, 80U, &out_data));
    TEST_ASSERT_TRUE(BitManipulation_clearBit(data, 0U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10110010U, out_data);
    TEST_ASSERT_TRUE(BitManipulation_clearBit(data, 2U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10110011U, out_data);
    TEST_ASSERT_TRUE(BitManipulation_clearBit(data, 4U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10100011U, out_data);
}

TEST(BitManipulation, BitManipulation_toggleBit) {
    const uint32_t data = 0b10110011U;
    uint32_t out_data;
    TEST_ASSERT_FALSE(BitManipulation_toggleBit(data, 32U, &out_data));
    TEST_ASSERT_FALSE(BitManipulation_toggleBit(data, 128U, &out_data));
    TEST_ASSERT_TRUE(BitManipulation_toggleBit(data, 0U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10110010U, out_data);
    TEST_ASSERT_TRUE(BitManipulation_toggleBit(data, 2U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10110111U, out_data);
    TEST_ASSERT_TRUE(BitManipulation_toggleBit(data, 4U, &out_data));
    TEST_ASSERT_EQUAL_UINT32(0b10100011U, out_data);
}
