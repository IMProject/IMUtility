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
    char base64[] = "SU1Qcm9qZWN0IGlzIGEgdmVyeSBjb29sIHByb2plY3Qh\0";
    unsigned char string[200];
    size_t string_size = 200;
    Base64_decode(base64, strlen(base64), string, &string_size);
    TEST_ASSERT_EQUAL_STRING("IMProject is a very cool project!", string);
}

