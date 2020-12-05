#include "timer_platform.h"
#include <glug/timer/time_t.h>
#include <frac.h>
#include "defs.h"

#include "clock/clock.h"

static void read_ticks(clock_type_t, uint64_t *);
static void tick_scale(frac_t *);
static void clock_res(clock_type_t, struct glug_time *);

void read_continuous_ticks(uint64_t *ticks)
{
    read_ticks(CONTINUOUS, ticks);
}

void continuous_tick_scale(frac_t *sec_per_tick)
{
    tick_scale(sec_per_tick);
}

void continuous_clock_res(struct glug_time *res)
{
    clock_res(CONTINUOUS, res);
}

void read_uptime_ticks(uint64_t *ticks)
{
    read_ticks(UPTIME, ticks);
}

void uptime_tick_scale(struct frac *sec_per_tick)
{
    tick_scale(sec_per_tick);
}

void uptime_clock_res(struct glug_time *res)
{
    clock_res(UPTIME, res);
}

static void read_ticks(clock_type_t clock_type, uint64_t *ticks)
{
    clocktime_t clock;
    get_time(clock_type, &clock);

    *ticks = (uint64_t)clock.nsec + (uint64_t)clock.sec * NSEC_PER_SEC;
}

static void tick_scale(frac_t *sec_per_tick)
{
    sec_per_tick->numer = 1;
    sec_per_tick->denom = 1;
}

static void clock_res(clock_type_t clock_type, struct glug_time *res)
{
    clocktime_t timer_res;
    get_res(clock_type, &timer_res);

    res->sec  = timer_res.sec;
    res->nsec = timer_res.nsec;
}
