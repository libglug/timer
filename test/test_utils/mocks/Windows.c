#include "Windows.h"

// QueryPerformanceFrequency
static LARGE_INTEGER frequency = {0};

void set_QueryPerformanceFrequency(const uint64_t *freq)
{
    frequency.QuadPart = *freq;
}

int QueryPerformanceFrequency(LARGE_INTEGER *freq)
{
    freq->QuadPart = frequency.QuadPart;

    return 1;
}

// QueryPerformanceCounter
static LARGE_INTEGER counter = {0};

void set_QueryPerformanceCounter(const uint64_t *count)
{
    counter.QuadPart = *count;
}

int QueryPerformanceCounter(LARGE_INTEGER *count)
{
    count->QuadPart = counter.QuadPart;

    return 1;
}

// QueryUnbiasedInterruptTime
static uint64_t unbiased_time = 0;

void set_UnbiasedInterruptTime(const uint64_t *time)
{
    unbiased_time = *time;
}

int QueryUnbiasedInterruptTime(PULONGLONG time)
{
    *time = unbiased_time;

    return 1;
}
