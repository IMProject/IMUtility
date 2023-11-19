#include "map.h"

#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Map);

TEST_SETUP(Map) {
}

TEST_TEAR_DOWN(Map) {
}

TEST_GROUP_RUNNER(Map) {
    RUN_TEST_CASE(Map, Map_uint32_key_char_value);
    RUN_TEST_CASE(Map, Map_int32_key_fp32_value);
    RUN_TEST_CASE(Map, Map_negative_cases);
}

TEST(Map, Map_uint32_key_char_value) {
    uint32_t keys[100];
    char values[100][50];
    Map_t map;
    TEST_ASSERT_TRUE(Map_init(&map, (byte_t*)keys, (byte_t*)values, sizeof(keys[0]), sizeof(values[0]),
                              sizeof(keys) / sizeof(keys[0])));

    uint32_t key = 2U;
    char value1[] = "Value1";
    TEST_ASSERT_TRUE(Map_insert(&map, (byte_t*)&key, (byte_t*)&value1));
    key = 3U;
    char value2[] = "Value2";
    TEST_ASSERT_TRUE(Map_insert(&map, (byte_t*)&key, (byte_t*)&value2));

    char foundValue[50];
    key = 2U;
    TEST_ASSERT_TRUE(Map_getValue(&map, (byte_t*)&key, (byte_t*)&foundValue));
    TEST_ASSERT_TRUE(0 == strcmp(&foundValue[0], "Value1"));
}

TEST(Map, Map_int32_key_fp32_value) {
    int32_t keys[2];
    float32_t values[2];
    Map_t map;
    TEST_ASSERT_TRUE(Map_init(&map, (byte_t*)keys, (byte_t*)values, sizeof(keys[0]), sizeof(values[0]),
                              sizeof(keys) / sizeof(keys[0])));

    int32_t key = 1;
    float32_t value = 10.5F;
    TEST_ASSERT_TRUE(Map_insert(&map, (byte_t*)&key, (byte_t*)&value));
    key = 2;
    value = 15.4F;
    TEST_ASSERT_TRUE(Map_insert(&map, (byte_t*)&key, (byte_t*)&value));

    float32_t foundValue;
    TEST_ASSERT_TRUE(Map_getValue(&map, (byte_t*)&key, (byte_t*)&foundValue));
    TEST_ASSERT_EQUAL_FLOAT(foundValue, 15.4F);

    value = 300.1F;
    TEST_ASSERT_TRUE(Map_insert(&map, (byte_t*)&key, (byte_t*)&value));
    TEST_ASSERT_TRUE(Map_getValue(&map, (byte_t*)&key, (byte_t*)&foundValue));
    TEST_ASSERT_EQUAL_FLOAT(foundValue, 300.1F);

    key = 10;
    TEST_ASSERT_FALSE(Map_getValue(&map, (byte_t*)&key, (byte_t*)&foundValue));

    TEST_ASSERT_FALSE(Map_insert(&map, (byte_t*)&key, (byte_t*)&value));
}

TEST(Map, Map_negative_cases) {
    int32_t keys[5];
    float32_t values[5];
    Map_t map;

    TEST_ASSERT_FALSE(Map_init(&map, (byte_t*)keys, (byte_t*)values, 0, sizeof(values[0]),
                               sizeof(keys) / sizeof(keys[0])));
    TEST_ASSERT_FALSE(Map_init(&map, (byte_t*)keys, (byte_t*)values, sizeof(keys[0]), 0,
                               sizeof(keys) / sizeof(keys[0])));
    TEST_ASSERT_FALSE(Map_init(&map, (byte_t*)keys, (byte_t*)values, sizeof(keys[0]), sizeof(values[0]),
                               0));
    TEST_ASSERT_FALSE(Map_init(&map, NULL_PTR, (byte_t*)values, sizeof(keys[0]), sizeof(values[0]),
                               sizeof(keys) / sizeof(keys[0])));
    TEST_ASSERT_FALSE(Map_init(&map, (byte_t*)keys, NULL_PTR, sizeof(keys[0]), sizeof(values[0]),
                               sizeof(keys) / sizeof(keys[0])));

    int32_t key = 1;
    float32_t value = 10.5F;
    TEST_ASSERT_FALSE(Map_insert(NULL_PTR, (byte_t*)&key, (byte_t*)&value));

    TEST_ASSERT_FALSE(Map_getValue(NULL_PTR, (byte_t*)&key, (byte_t*)&value));
}
