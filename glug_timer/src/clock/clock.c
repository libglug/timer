#include "clock.h"

#include <time.h>

void get_time(struct timespec *time)
{
    clock_gettime(CLOCK_MONOTONIC_RAW, time);
}

void get_res(struct timespec *res)
{
    clock_getres(CLOCK_MONOTONIC_RAW, res);
}
