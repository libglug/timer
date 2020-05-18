#include "timer_platform.h"
#include <glug/os.h>

#if GLUG_OS == GLUG_OS_WIN

#include "qpc/qpc.h"
#include "safe_clock_scale.h"

#define NSEC_PER_SEC 1000ULL * 1000 * 1000

uint64_t read_clock(void)
{
    LARGE_INTEGER clock;
    query_counter(&clock);
    return (uint64_t)clock.QuadPart;
}

uint64_t clock_to_nsec(uint64_t clock)
{
    LARGE_INTEGER freq;
    query_frequency(&freq);
    return safe_clock_scale(clock, NSEC_PER_SEC, freq.QuadPart);
}

uint64_t clock_res(void)
{
    LARGE_INTEGER freq;
    query_frequency(&freq);
    return NSEC_PER_SEC / freq.QuadPart;
}

#endif // GLUG_OS == GLUG_OS_WIN
