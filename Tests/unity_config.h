#ifndef TESTS_UNITY_UNITY_CONFIG_H_
#define TESTS_UNITY_UNITY_CONFIG_H_

#define UNITY_INCLUDE_EXEC_TIME

#if defined(_WIN32)
#include <time.h>
#define UNITY_TIME_TYPE clock_t
#define UNITY_GET_TIME(t) t = (clock_t)((clock() * 1000) / CLOCKS_PER_SEC)
#define UNITY_EXEC_TIME_START() UNITY_GET_TIME(Unity.CurrentTestStartTime)
#define UNITY_EXEC_TIME_STOP() UNITY_GET_TIME(Unity.CurrentTestStopTime)
#define UNITY_PRINT_EXEC_TIME() { \
        UNITY_UINT execTimeMs = (Unity.CurrentTestStopTime - Unity.CurrentTestStartTime); \
        UnityPrint(" ("); \
        UnityPrintNumberUnsigned(execTimeMs); \
        UnityPrint(" ms)"); \
    }
#elif defined(__unix__) || defined(__APPLE__)
#include <time.h>
#define UNITY_TIME_TYPE struct timespec
#define UNITY_GET_TIME(t) clock_gettime(CLOCK_MONOTONIC, &t)
#define UNITY_EXEC_TIME_START() UNITY_GET_TIME(Unity.CurrentTestStartTime)
#define UNITY_EXEC_TIME_STOP() UNITY_GET_TIME(Unity.CurrentTestStopTime)
#define UNITY_PRINT_EXEC_TIME() { \
        UNITY_UINT execTimeNs = ((Unity.CurrentTestStopTime.tv_sec - Unity.CurrentTestStartTime.tv_sec) * 1000L); \
        execTimeNs += (Unity.CurrentTestStopTime.tv_nsec - Unity.CurrentTestStartTime.tv_nsec); \
        UnityPrint(" ("); \
        UnityPrintNumberUnsigned(execTimeNs); \
        UnityPrint(" ns)"); \
    }
#endif

#endif /* TESTS_UNITY_UNITY_CONFIG_H_ */
