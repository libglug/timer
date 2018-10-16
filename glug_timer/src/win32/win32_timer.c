#include "../timer_platform.h"

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#include <stdint.h>
#include <Windows.h>

uint64_t frequency()
{
    LARGE_INTEGER freq;
    freq.QuadPart = 1;
    if (!QueryPerformanceFrequency(&freq))
        return 1;
    return (uint64_t)freq.QuadPart;
}

uint64_t read_clock()
{
    LARGE_INTEGER clock;
    clock.QuadPart = 0;
    if (!QueryPerformanceCounter(&clock))
        return 0;
    return (uint64_t)clock.QuadPart;
}
