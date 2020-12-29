#include "time.h"

// clock_gettime
static struct timespec clock_times[2];
void set_clock_gettime(clockid_t clockid, const struct timespec *tp)
{
    clock_times[clockid] = *tp;
}

int clock_gettime(clockid_t clockid, struct timespec *tp)
{
    *tp = clock_times[clockid];
    return 1;
}

// clock_getres
static struct timespec clock_resolutions[2];
void set_clock_getres(clockid_t clockid, const struct timespec *res)
{
    clock_resolutions[clockid] = *res;
}

int clock_getres(clockid_t clockid, struct timespec *res)
{
    *res = clock_resolutions[clockid];
    return 1;
}
