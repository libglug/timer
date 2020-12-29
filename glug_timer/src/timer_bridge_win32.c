#include "timer_bridge.h"
#include <glug/timer/time_t.h>
#include <frac_t.h>
#include "defs.h"

#include "qpc/qpc.h"
#include "qpc/quit.h"

static void freq_to_res(uint64_t *, struct glug_time *);

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

    freq_to_res(&freq, res);
}

void read_uptime_ticks(uint64_t *ticks)
{
    query_unbiased_time(ticks);
}

void uptime_tick_scale(struct frac *sec_per_tick)
{
    uint64_t freq;
    query_unbiased_frequency(&freq);
    sec_per_tick->numer = NSEC_PER_SEC;
    sec_per_tick->denom = freq;
}

void uptime_clock_res(struct glug_time *res)
{
    uint64_t freq;
    query_unbiased_frequency(&freq);

    freq_to_res(&freq, res);
}

static void freq_to_res(uint64_t *freq, struct glug_time *res)
{
    uint64_t timer_res = NSEC_PER_SEC / *freq;

    res->sec  = (uint32_t)(timer_res / NSEC_PER_SEC);
    res->nsec = (uint32_t)(timer_res % NSEC_PER_SEC);
}
