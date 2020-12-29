#ifndef MOCK_WINDOWS_H
#define MOCK_WINDOWS_H

#include <stdint.h>

typedef union
{
    struct
    {
        uint32_t LowPart;
        uint32_t HighPart;
    } u;
    uint64_t QuadPart;
} LARGE_INTEGER;

typedef int BOOL;

void set_QueryPerformanceFrequency(const uint64_t *);
BOOL QueryPerformanceFrequency(LARGE_INTEGER *);

void set_QueryPerformanceCounter(const uint64_t *);
BOOL QueryPerformanceCounter(LARGE_INTEGER *);

typedef uint64_t* PULONGLONG;
void set_UnbiasedInterruptTime(const uint64_t *);
BOOL QueryUnbiasedInterruptTime(PULONGLONG);

#endif // MOCK_WINDOWS_H
