#include "timer_platform.h"
#include <glug/os.h>

#include "qpc/qpc.h"
#include "safe_clock_scale.h"

#define NSEC_PER_SEC 1000ULL * 1000 * 1000

uint64_t read_clock(void)
{
    return query_counter();
}

uint64_t clock_to_nsec(uint64_t clock)
{
    uint64_t freq = query_frequency();
    return safe_clock_scale(clock, NSEC_PER_SEC, freq);
}

uint64_t clock_res(void)
{
    uint64_t freq = query_frequency();
    return NSEC_PER_SEC / freq;
}
