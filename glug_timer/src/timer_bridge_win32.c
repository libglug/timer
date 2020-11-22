#include "timer_platform.h"
#include <glug/os.h>
#include <frac.h>
#include "defs.h"

#include "qpc/qpc.h"

uint64_t read_clock_ticks(void)
{
    return query_counter();
}

void secs_per_tick(frac_t *sec_per_tick)
{
    uint64_t freq = query_frequency();
    sec_per_tick->numer = NSEC_PER_SEC;
    sec_per_tick->denom = freq;
}

void clock_res(struct glug_time *res)
{
    uint64_t freq = query_frequency();
    uint64_t timer_res = NSEC_PER_SEC / freq;

    res->sec  = timer_res / NSEC_PER_SEC;
    res->nsec = timer_res % NSEC_PER_SEC;
}
