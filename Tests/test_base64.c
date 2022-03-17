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
    const char string[] = "IMProject is a very cool project!";
    char base64[200];
    Base64_encode(string, strlen(string), base64, sizeof(base64));
    TEST_ASSERT_EQUAL_STRING("SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh", base64);
}

TEST(Base64, Base64_decode) {

    char text_1[] = "IMProject is a very cool project!";
    char base64_1[] = "SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh";
    unsigned char string[200];
    size_t string_size = 200;
    Base64_decode(base64_1, strlen(base64_1), string, &string_size);
    TEST_ASSERT_EQUAL_MEMORY(text_1, string, strlen(text_1));

    char text_2[] = "B?E(H+MbQeThWmZq4t7w!z%C*F)J@NcR";
    char base64_2[] =  "Qj9FKEgrTWJRZVRoV21acTR0N3cheiVDKkYpSkBOY1I=";
    unsigned char string_2[200];
    size_t string_size_2 = 200;
    Base64_decode(base64_2, strlen(base64_2), string_2, &string_size_2);
    TEST_ASSERT_EQUAL_MEMORY(text_2, string_2, strlen(text_2));
}

