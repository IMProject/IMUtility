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
        bool success = Json_findByKey(json_string, strlen(json_string), key_1, value, size);
        TEST_ASSERT_EQUAL_STRING("u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=", value);
        TEST_ASSERT_EQUAL_INT(true, success);

        char key_2[] = "public_key_signature";
        success = Json_findByKey(json_string, strlen(json_string), key_2, value, size);
        TEST_ASSERT_EQUAL_STRING("sQjximnEuRAsf+mAuTURcXASUS5vkl5xU0SNvvAcX+Mfc7es+xXw/Lgo0bfMNY+ShKe5VjbIg3DaSxJvLbhX+w==", value);
        TEST_ASSERT_EQUAL_INT(true, success);


        char key_3[] = "public";
        success = Json_findByKey(json_string, strlen(json_string), key_3, value, size);
        TEST_ASSERT_EQUAL_INT(false, success);

        char key_4[] = "\"public_key\"";
        success = Json_findByKey(json_string, strlen(json_string), key_4, value, size);
        TEST_ASSERT_EQUAL_INT(false, success);

        size = 45; // 44 + '/0' needed for full string
        success = Json_findByKey(json_string, strlen(json_string), key_1, value, size);
        TEST_ASSERT_EQUAL_STRING("u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=", value);
        TEST_ASSERT_EQUAL_INT(true, success);

        size = 44; // can't fit full string
        success = Json_findByKey(json_string, strlen(json_string), key_1, value, size);
        TEST_ASSERT_EQUAL_STRING("u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=", value);
        TEST_ASSERT_EQUAL_INT(false, success);
    }
}
