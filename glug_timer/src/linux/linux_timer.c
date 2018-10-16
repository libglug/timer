#include "../timer_platform.h"

#include <stdint.h>
#include <time.h>

uint64_t clock_res()
{
    struct timespec res;
    clock_getres(CLOCK_MONOTONIC_RAW, &res);
    return (uint64_t)res.tv_nsec + (uint64_t)res.tv_sec * 1000 * 1000 * 1000;
}

uint64_t clock_frequency()
{
    return 1;
}

uint64_t read_clock()
{
    struct timespec clock;
    clock_gettime(CLOCK_MONOTONIC_RAW, &clock);
    return clock.tv_nsec + clock.tv_sec * 1000 * 1000 * 1000;
}
