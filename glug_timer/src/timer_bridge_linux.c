#include "timer_platform.h"
#include <glug/os.h>
#include <frac.h>
#include "defs.h"

#include "clock/clock.h"

void read_clock_ticks(uint64_t *ticks)
{
    nstime_t clock;
    get_time(MONOTONIC, &clock);

    *ticks = (uint64_t)clock.nsec + (uint64_t)clock.sec * NSEC_PER_SEC;
}

void secs_per_tick(frac_t *sec_per_tick)
{
    sec_per_tick->numer = 1;
    sec_per_tick->denom = 1;
}

void clock_res(struct glug_time *res)
{
    nstime_t timer_res;
    get_res(MONOTONIC, &timer_res);

    res->sec  = timer_res.sec;
    res->nsec = timer_res.nsec;
}
