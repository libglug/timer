#include "timer_bridge.h"
#include <glug/timer/time_t.h>
#include <frac_t.h>
#include "defs.h"

#include "mach/mach.h"

static void tick_scale_to_res(const frac_t *, struct glug_time *);

void read_continuous_ticks(uint64_t * ticks)
{
    continuous_ticks(ticks);
}

void continuous_tick_scale(frac_t *sec_per_tick)
{
    tick_scale(sec_per_tick);
}

void continuous_clock_res(struct glug_time *res)
{
    frac_t timebase;
    tick_scale(&timebase);

    tick_scale_to_res(&timebase, res);
}

void read_uptime_ticks(uint64_t *ticks)
{
    absolute_ticks(ticks);
}

void uptime_tick_scale(struct frac *sec_per_tick)
{
    tick_scale(sec_per_tick);
}

void uptime_clock_res(struct glug_time *res)
{
    frac_t timebase;
    tick_scale(&timebase);

    tick_scale_to_res(&timebase, res);
}

static void tick_scale_to_res(const frac_t *tick_scale, struct glug_time *res)
{
    uint64_t timer_res = tick_scale->numer / tick_scale->denom;

    res->sec  = (uint32_t)(timer_res / NSEC_PER_SEC);
    res->nsec = (uint32_t)(timer_res % NSEC_PER_SEC);
}
