#include "json.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Json);

TEST_SETUP(Json) {
}

TEST_TEAR_DOWN(Json) {
}

TEST_GROUP_RUNNER(Json) {
    RUN_TEST_CASE(Json, Json_startString);
    RUN_TEST_CASE(Json, Json_addData);
    RUN_TEST_CASE(Json, Json_endString);
    RUN_TEST_CASE(Json, Json_findByKey);
}

TEST(Json, Json_startString) {
    char buffer[10] = {0U};
    TEST_ASSERT_TRUE(Json_startString(buffer, 2U));
    TEST_ASSERT_EQUAL_UINT8(buffer[0], '{');
    TEST_ASSERT_EQUAL_UINT8(buffer[1], '\0');
    TEST_ASSERT_FALSE(Json_startString(buffer, 1U));
}

TEST(Json, Json_addData) {
    char buffer[100] = {0U};
    const char key[] = "public_key";
    const char value[] = "u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=";
    TEST_ASSERT_TRUE(Json_addData(buffer, sizeof(buffer), key, value));
    TEST_ASSERT_EQUAL_STRING(buffer, "\"public_key\":\"u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=\"");

    //Buffer size not big enough
    TEST_ASSERT_FALSE(Json_addData(buffer, 10U, key, value));
}

TEST(Json, Json_endString) {
    char buffer_1[10] = "{ABCD";
    TEST_ASSERT_TRUE(Json_endString(buffer_1, sizeof(buffer_1)));
    TEST_ASSERT_EQUAL_UINT8(buffer_1[5], '}');
    TEST_ASSERT_EQUAL_UINT8(buffer_1[6], '\0');

    char buffer_2[10] = "{ABCD";
    TEST_ASSERT_FALSE(Json_endString(buffer_2, 6U)); // Not enough space for '\0'
}

TEST(Json, Json_findByKey) {
    {
        char json_string[] =
            "{\"public_key\":\"u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=\",\"public_key_signature\":\"sQjximnEuRAsf+mAuTURcXASUS5vkl5xU0SNvvAcX+Mfc7es+xXw/Lgo0bfMNY+ShKe5VjbIg3DaSxJvLbhX+w==\"}";
        char value[200];
        size_t size = 200;

        char key_1[] = "public_key";
        TEST_ASSERT_TRUE(Json_findByKey(json_string, strlen(json_string), key_1, value, size));
        TEST_ASSERT_EQUAL_STRING("u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=", value);

        char key_2[] = "public_key_signature";
        TEST_ASSERT_TRUE(Json_findByKey(json_string, strlen(json_string), key_2, value, size));
        TEST_ASSERT_EQUAL_STRING("sQjximnEuRAsf+mAuTURcXASUS5vkl5xU0SNvvAcX+Mfc7es+xXw/Lgo0bfMNY+ShKe5VjbIg3DaSxJvLbhX+w==",
                                 value);

        char key_3[] = "public";
        TEST_ASSERT_FALSE(Json_findByKey(json_string, strlen(json_string), key_3, value, size));

        char key_4[] = "\"public_key\"";
        TEST_ASSERT_FALSE(Json_findByKey(json_string, strlen(json_string), key_4, value, size));

        size = 45; // 44 + '/0' needed for full string
        TEST_ASSERT_TRUE(Json_findByKey(json_string, strlen(json_string), key_1, value, size));
        TEST_ASSERT_EQUAL_STRING("u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=", value);

        size = 44; // can't fit full string
        TEST_ASSERT_FALSE(Json_findByKey(json_string, strlen(json_string), key_1, value, size));
        TEST_ASSERT_EQUAL_STRING("u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=", value);

        char key_same_size_as_buffer[strlen(json_string) + 1];
        memset(key_same_size_as_buffer, 'A', sizeof(key_same_size_as_buffer));
        key_same_size_as_buffer[strlen(json_string)] = '\0';
        TEST_ASSERT_FALSE(Json_findByKey(json_string, strlen(json_string), key_same_size_as_buffer, value, size));

        size = 200;
        char key_non_existing[] = "non_existing_key";
        TEST_ASSERT_FALSE(Json_findByKey(json_string, strlen(json_string), key_non_existing, value, size));

        //missing quotation marks for value
        char broken_json_string_1[] = "{\"public_key\": blabla }";
        TEST_ASSERT_FALSE(Json_findByKey(broken_json_string_1, strlen(broken_json_string_1), key_1, value, size));

        //missing quotation mark at the end for value
        char broken_json_string_2[] = "{\"public_key\": \"blabla }";
        TEST_ASSERT_FALSE(Json_findByKey(broken_json_string_2, strlen(broken_json_string_2), key_1, value, size));

        char json_string_with_space[] = "{  \"public_key\"   :     \"u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=\"   }";
        TEST_ASSERT_TRUE(Json_findByKey(json_string_with_space, strlen(json_string_with_space), key_1, value, size));
        TEST_ASSERT_EQUAL_STRING("u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=", value);
    }
}
