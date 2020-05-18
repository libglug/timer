#include "timer_platform.h"
#include <glug/os.h>

#if GLUG_OS == GLUG_OS_BSD

#include "clock/clock.h"

#define NSEC_PER_SEC 1000ULL * 1000 * 1000

uint64_t read_clock(void)
{
    struct timespec clock;
    get_time(CLOCK_MONOTONIC, &clock);
    return (uint64_t)clock.tv_nsec + (uint64_t)clock.tv_sec * NSEC_PER_SEC;
}

uint64_t clock_to_nsec(uint64_t clock)
{
    return clock;
}

uint64_t clock_res(void)
{
    struct timespec res;
    get_res(CLOCK_MONOTONIC, &res);
    return (uint64_t)res.tv_nsec + (uint64_t)res.tv_sec * NSEC_PER_SEC;
}

#endif // GLUG_OS == GLUG_OS_BSD
