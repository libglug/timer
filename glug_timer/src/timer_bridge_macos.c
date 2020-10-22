#include "timer_platform.h"
#include <glug/os.h>

#include "mach/mach.h"

uint64_t read_clock_ticks(void)
{
    return continuous_ticks();
}

void ticks_per_sec(frac_t *tps)
{
    tick_scale(tps);
}

uint64_t clock_res(void)
{
    frac_t timebase;
    tick_scale(&timebase);

    return timebase.numer / timebase.denom;
}
