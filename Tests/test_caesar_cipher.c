#include "ciphering/caesar_cipher.h"

#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(CaesarCipher);

TEST_SETUP(CaesarCipher) {
}

TEST_TEAR_DOWN(CaesarCipher) {
}

TEST_GROUP_RUNNER(CaesarCipher) {
    RUN_TEST_CASE(CaesarCipher, CaesarCipher_encryptDecrypt);
}

TEST(CaesarCipher, CaesarCipher_encryptDecrypt) {
    const char expected_result[] = "|Caesar Cipher Test|";
    char message[] = "|Caesar Cipher Test|";
    CaesarCipher_encrypt(message, 6U);
    CaesarCipher_decrypt(message, 6U);
    TEST_ASSERT_EQUAL_STRING(expected_result, message);
}
