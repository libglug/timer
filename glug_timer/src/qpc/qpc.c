#include "qpc.h"

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

uint64_t query_frequency(void)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    return freq.QuadPart;
}

uint64_t query_counter(void)
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);

    return counter.QuadPart;
}
