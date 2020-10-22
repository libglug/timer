#include "clock.h"

#include <time.h>
#include <glug/os.h>

#if GLUG_OS == GLUG_OS_LIN
static const clockid_t clock_ids[2] = { CLOCK_MONOTONIC_RAW, CLOCK_BOOTTIME };
#elif GLUG_OS == GLUG_OS_BSD
static const clockid_t clock_ids[2] = { CLOCK_MONOTONIC, CLOCK_UPTIME }
#endif

void get_time(clock_type_t clock_type, nstime_t *time)
{
    clockid_t clock = clock_ids[clock_type];
    struct timespec timespec;

    clock_gettime(clock, &timespec);
    time->sec  = timespec.tv_sec;
    time->nsec = timespec.tv_nsec;
}

void get_res(clock_type_t clock_type, nstime_t *res)
{
    clockid_t clock = clock_ids[clock_type];
    struct timespec resspec;

    clock_getres(clock, &resspec);
    res->sec  = resspec.tv_sec;
    res->nsec = resspec.tv_nsec;
}
