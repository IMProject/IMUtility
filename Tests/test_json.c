#include "json.h"
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Json);

TEST_SETUP(Json) {
}

TEST_TEAR_DOWN(Json) {
}

TEST_GROUP_RUNNER(Json) {
    RUN_TEST_CASE(Json, Json_findByKey);
}

TEST(Json, Json_findByKey) {
    {
        char json_string[] =
            "{\"public_key\":\"u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=\",\"public_key_signature\":\"sQjximnEuRAsf+mAuTURcXASUS5vkl5xU0SNvvAcX+Mfc7es+xXw/Lgo0bfMNY+ShKe5VjbIg3DaSxJvLbhX+w==\"}";
        char value[200];
        size_t size;

        char key_1[] = "public_key";
        bool success = Json_findByKey(json_string, strlen(json_string), key_1, value, &size);
        TEST_ASSERT_EQUAL_STRING("u1zeY+TBbtYlDIzZsLH16RJ9aIBmxTINpLXSkTpaikQ=", value);
        TEST_ASSERT_EQUAL_INT(44, size);
        TEST_ASSERT_EQUAL_INT(true, success);

        char key_2[] = "public_key_signature";
        success = Json_findByKey(json_string, strlen(json_string), key_2, value, &size);
        TEST_ASSERT_EQUAL_STRING("sQjximnEuRAsf+mAuTURcXASUS5vkl5xU0SNvvAcX+Mfc7es+xXw/Lgo0bfMNY+ShKe5VjbIg3DaSxJvLbhX+w==", value);
        TEST_ASSERT_EQUAL_INT(88, size);
        TEST_ASSERT_EQUAL_INT(true, success);


        char key_3[] = "public";
        success = Json_findByKey(json_string, strlen(json_string), key_3, value, &size);
        TEST_ASSERT_EQUAL_INT(false, success);

        char key_4[] = "\"public_key\"";
        success = Json_findByKey(json_string, strlen(json_string), key_4, value, &size);
        TEST_ASSERT_EQUAL_INT(false, success);
    }
}
