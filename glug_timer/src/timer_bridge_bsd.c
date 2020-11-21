#include "timer_platform.h"
#include <glug/os.h>

#include "clock/clock.h"

#define NSEC_PER_SEC 1000 * 1000 * 1000

uint64_t read_clock_ticks(void)
{
    nstime_t clock;
    get_time(MONOTONIC, &clock);

    return (uint64_t)clock.nsec + (uint64_t)clock.sec * NSEC_PER_SEC;
}

void ticks_per_sec(frac_t *tps)
{
    tps->numer = 1;
    tps->denom = 1;
}

uint64_t clock_res(void)
{
    nstime_t res;
    get_res(MONOTONIC, &res);

    return (uint64_t)res.nsec + (uint64_t)res.sec * NSEC_PER_SEC;
}

