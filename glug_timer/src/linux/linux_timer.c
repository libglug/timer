#include "../timer_platform.h"

#define NSEC_PER_SEC (uint64_t)1000 * 1000 * 1000

#include <stdint.h>
#include <time.h>

uint64_t read_clock()
{
    struct timespec clock;
    clock_gettime(CLOCK_MONOTONIC_RAW, &clock);
    return (uint64_t)clock.tv_nsec + (uint64_t)clock.tv_sec * NSEC_PER_SEC;
}

uint64_t clock_to_nsec(uint64_t clock)
{
    return clock;
}

uint64_t clock_res()
{
    struct timespec res;
    clock_getres(CLOCK_MONOTONIC_RAW, &res);
    return (uint64_t)res.tv_nsec + (uint64_t)res.tv_sec * NSEC_PER_SEC;
}
