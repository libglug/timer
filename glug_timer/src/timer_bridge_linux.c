#include "timer_platform.h"
#include <glug/os.h>
#include <frac.h>
#include "defs.h"

#include "clock/clock.h"

void read_continuous_ticks(uint64_t *ticks)
{
    clocktime_t clock;
    get_time(CONTINUOUS, &clock);

    *ticks = (uint64_t)clock.nsec + (uint64_t)clock.sec * NSEC_PER_SEC;
}

void continuous_tick_scale(frac_t *sec_per_tick)
{
    sec_per_tick->numer = 1;
    sec_per_tick->denom = 1;
}

void continuous_clock_res(struct glug_time *res)
{
    clocktime_t timer_res;
    get_res(CONTINUOUS, &timer_res);

    res->sec  = timer_res.sec;
    res->nsec = timer_res.nsec;
}
