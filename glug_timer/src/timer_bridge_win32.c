#include "timer_platform.h"
#include <glug/os.h>
#include <frac.h>
#include "defs.h"

#include "qpc/qpc.h"

void read_continuous_ticks(uint64_t *ticks)
{
    query_counter(ticks);
}

void continuous_tick_scale(frac_t *sec_per_tick)
{
    uint64_t freq;
    query_frequency(&freq);
    sec_per_tick->numer = NSEC_PER_SEC;
    sec_per_tick->denom = freq;
}

void continuous_clock_res(struct glug_time *res)
{
    uint64_t freq;
    query_frequency(&freq);
    uint64_t timer_res = NSEC_PER_SEC / freq;

    res->sec  = timer_res / NSEC_PER_SEC;
    res->nsec = timer_res % NSEC_PER_SEC;
}
