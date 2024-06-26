#include "base64.h"

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Base64);

TEST_SETUP(Base64) {
}

TEST_TEAR_DOWN(Base64) {
}

TEST_GROUP_RUNNER(Base64) {
    RUN_TEST_CASE(Base64, Base64_encode);
    RUN_TEST_CASE(Base64, Base64_decode);
}

TEST(Base64, Base64_encode) {
    {
        // Success
        const char string[] = "IMProject is a very cool project!";
        char base64[200];
        int32_t success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_STRING("SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh", base64);
        TEST_ASSERT_EQUAL_INT32(0, success);
    }
    {
        // Result length is too small
        const char string[] = "IMProject is a very cool project!";
        char base64[10];
        int32_t success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_INT32(1, success);
    }
    {
        // Success
        const char string[] = "Hehe";
        char base64[200];
        int32_t success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_STRING("SGVoZQ==", base64);
        TEST_ASSERT_EQUAL_INT32(0, success);
    }
    {
        // Success
        const char string[] = "jc";
        char base64[200];
        int32_t success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_STRING("amM=", base64);
        TEST_ASSERT_EQUAL_INT32(0, success);
    }
    {
        // Result length is too small
        const char string[] = "Hehe";
        char base64[4];
        int32_t success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_INT32(1, success);
    }
    {
        // data_length = 18446744073709551610, overflow
        const char string[] = "Hehe";
        char base64[4];
        int32_t success = Base64_encode(string, 18446744073709551610U, base64, sizeof(base64));
        TEST_ASSERT_EQUAL_INT32(1, success);
    }
}

TEST(Base64, Base64_decode) {
    {
        // Success
        char text[] = "IMProject is a very cool project!";
        const char base64[] = "SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh";
        uint8_t string[200];
        int32_t success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_MEMORY(text, string, strlen(text));
        TEST_ASSERT_EQUAL_INT32(0, success);
    }
    {
        // Output size is too big
        const char base64[] = "SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh";
        uint8_t string[10];
        int32_t success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_INT32(1, success);
    }
    {
        // Success
        char text[] = "B?E(H+MbQeThWmZq4t7w!z%C*F)J@NcR";
        const char base64[] = "Qj9FKEgrTWJRZVRoV21acTR0N3cheiVDKkYpSkBOY1I=";
        uint8_t string[200];
        int32_t success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_MEMORY(text, string, strlen(text));
        TEST_ASSERT_EQUAL_INT32(0, success);
    }
    {
        // Success
        char text[] = "Hehe";
        const char base64[] = "SGVoZQ==";
        uint8_t string[200];
        int32_t success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_MEMORY(text, string, strlen(text));
        TEST_ASSERT_EQUAL_INT32(0, success);
    }
    {
        // Success
        char text[] = "Hehe";
        const char base64[] = "SGVoZQ1==";
        uint8_t string[200];
        int32_t success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_MEMORY(text, string, strlen(text));
        TEST_ASSERT_EQUAL_INT32(0, success);
    }
    {
        // Output size is too big
        const char base64[] = "Qj9FKEgrTWJRZVRoV21acTR0N3cheiVDKkYpSkBOY1I=";
        uint8_t string[31];
        int32_t success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_INT32(1, success);
    }
    {
        // Fail, length = 0
        const char base64[] = "SGVoZQ==";
        uint8_t string[200];
        int32_t success = Base64_decode(base64, 0U, string, sizeof(string));
        TEST_ASSERT_EQUAL_INT32(1, success);
    }
}
