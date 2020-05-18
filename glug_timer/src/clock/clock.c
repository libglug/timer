#include "clock.h"

#include <time.h>

void get_time(clockid_t clock, struct timespec *time)
{
    clock_gettime(clock, time);
}

void get_res(clockid_t clock, struct timespec *res)
{
    clock_getres(clock, res);
}
