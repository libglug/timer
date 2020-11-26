#include "qpc.h"

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void query_frequency(uint64_t *frequency)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);

    *frequency = freq.QuadPart;
}

void query_counter(uint64_t *counter)
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);

    *counter = count.QuadPart;
}
