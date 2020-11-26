#include "timer_platform.h"
#include <glug/os.h>
#include <frac.h>
#include "defs.h"

#include "mach/mach.h"

void read_clock_ticks(uint64_t * ticks)
{
    continuous_ticks(ticks);
}

void secs_per_tick(frac_t *sec_per_tick)
{
    tick_scale(sec_per_tick);
}

void clock_res(struct glug_time *res)
{
    frac_t timebase;
    tick_scale(&timebase);
    uint64_t timer_res = timebase.numer / timebase.denom;

    res->sec  = timer_res / NSEC_PER_SEC;
    res->nsec = timer_res % NSEC_PER_SEC;
}
