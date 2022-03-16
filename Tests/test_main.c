#include "unity.h"
#include "unity_fixture.h"

static void
RunAllTests(void) {
    RUN_TEST_GROUP(Crc32);
    RUN_TEST_GROUP(Base64);
}

int
main(int argc, const char* argv[]) {
    return UnityMain(argc, argv, RunAllTests);
}
