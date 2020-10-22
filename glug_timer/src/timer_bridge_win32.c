#include "timer_platform.h"
#include <glug/os.h>

#include "qpc/qpc.h"

#define NSEC_PER_SEC 1000ULL * 1000 * 1000

uint64_t read_clock_ticks(void)
{
    return query_counter();
}

void ticks_per_sec(frac_t *tps)
{
    uint64_t freq = query_frequency();
    tps->numer = NSEC_PER_SEC;
    tps->denom = freq;
}

uint64_t clock_res(void)
{
    uint64_t freq = query_frequency();
    return NSEC_PER_SEC / freq;
}
