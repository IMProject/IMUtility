#include "vernam_cipher.h"

#include <string.h>

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(VernamCipher);

TEST_SETUP(VernamCipher) {
}

TEST_TEAR_DOWN(VernamCipher) {
}

TEST_GROUP_RUNNER(VernamCipher) {
    RUN_TEST_CASE(VernamCipher, VernamCipher_encryptDecrypt);
}

TEST(VernamCipher, VernamCipher_encryptDecrypt) {
    const char expected_result[] = "ReSuLt1a";
    const char key1[] = "OSIJEK11";
    const char key2[] = "OSijek!/";
    char message[] = "ReSuLt1a";
    TEST_ASSERT_TRUE(VernamCipher_encrypt(message, key1, (int32_t)strlen(key1)));
    TEST_ASSERT_TRUE(VernamCipher_decrypt(message, key1, (int32_t)strlen(key1)));
    TEST_ASSERT_EQUAL_STRING(expected_result, message);

    TEST_ASSERT_TRUE(VernamCipher_encrypt(message, key2, (int32_t)strlen(key2)));
    TEST_ASSERT_TRUE(VernamCipher_decrypt(message, key2, (int32_t)strlen(key2)));
    TEST_ASSERT_EQUAL_STRING(expected_result, message);

    TEST_ASSERT_FALSE(VernamCipher_encrypt(message, key1, 3));
    TEST_ASSERT_FALSE(VernamCipher_decrypt(message, key1, 100));
}
