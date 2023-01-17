#include "unity.h"
#include "unity_fixture.h"

static void
RunAllTests(void) {
    RUN_TEST_GROUP(Base64);
    RUN_TEST_GROUP(BubbleSort);
    RUN_TEST_GROUP(Crc32);
    RUN_TEST_GROUP(HeapSort);
    RUN_TEST_GROUP(Json);
    RUN_TEST_GROUP(PriorityQueue);
    RUN_TEST_GROUP(Queue);
    RUN_TEST_GROUP(Scheduler);
    RUN_TEST_GROUP(Utils);
}

int
main(int argc, const char* argv[]) {
    return UnityMain(argc, argv, RunAllTests);
}
