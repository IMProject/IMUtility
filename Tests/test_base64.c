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
        const char string[] = "IMProject is a very cool project!";
        char base64[200];
        int success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_STRING("SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh", base64);
        TEST_ASSERT_EQUAL_INT(0, success);
    }
    {
        // Result length is too small
        const char string[] = "IMProject is a very cool project!";
        char base64[10];
        int success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_INT(1, success);
    }
    {
        const char string[] = "Hehe";
        char base64[200];
        int success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_STRING("SGVoZQ==", base64);
        TEST_ASSERT_EQUAL_INT(0, success);
    }
    {
        // Result length is too small
        const char string[] = "Hehe";
        char base64[4];
        int success = Base64_encode(string, strlen(string), base64, sizeof(base64));
        TEST_ASSERT_EQUAL_INT(1, success);
    }
}

TEST(Base64, Base64_decode) {
    {
        char text[] = "IMProject is a very cool project!";
        char base64[] = "SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh";
        unsigned char string[200];
        int success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_MEMORY(text, string, strlen(text));
        TEST_ASSERT_EQUAL_INT(0, success);
    }
    {
        // Output size is too big
        char base64[] = "SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh";
        unsigned char string[10];
        int success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_INT(1, success);
    }
    {
        char text[] = "B?E(H+MbQeThWmZq4t7w!z%C*F)J@NcR";
        char base64[] = "Qj9FKEgrTWJRZVRoV21acTR0N3cheiVDKkYpSkBOY1I=";
        unsigned char string[200];
        int success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_MEMORY(text, string, strlen(text));
        TEST_ASSERT_EQUAL_INT(0, success);
    }
    {
        // Output size is too big
        char base64[] = "Qj9FKEgrTWJRZVRoV21acTR0N3cheiVDKkYpSkBOY1I=";
        unsigned char string[31];
        int success = Base64_decode(base64, strlen(base64), string, sizeof(string));
        TEST_ASSERT_EQUAL_INT(1, success);
    }
}
