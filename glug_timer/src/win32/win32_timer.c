#include "../timer_platform.h"

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

#define NSEC_PER_SEC (uint64_t)1000 * 1000 * 1000

#include <stdint.h>
#include <Windows.h>

extern uint64_t GLUG_LIB_LOCAL safe_clock_scale(uint64_t clock, uint64_t numer, uint64_t denom);

static uint64_t clock_frequency()
{
    LARGE_INTEGER freq;
    freq.QuadPart = 1;
    if (!QueryPerformanceFrequency(&freq))
        return 1;
    return (uint64_t)freq.QuadPart;
}

uint64_t GLUG_LIB_LOCAL read_clock()
{
    LARGE_INTEGER clock;
    clock.QuadPart = 0;
    if (!QueryPerformanceCounter(&clock))
        return 0;
    return (uint64_t)clock.QuadPart;
}

uint64_t GLUG_LIB_LOCAL clock_to_nsec(uint64_t clock)
{
    return safe_clock_scale(clock, NSEC_PER_SEC, clock_frequency());
}

uint64_t GLUG_LIB_LOCAL clock_res()
{
    return NSEC_PER_SEC / clock_frequency();
}
