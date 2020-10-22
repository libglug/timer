#include "timer_platform.h"
#include <glug/os.h>

#include "mach/mach.h"
#include "safe_clock_scale.h"

uint64_t read_clock(void)
{
    return continuous_ticks();
}

uint64_t clock_to_nsec(uint64_t clock)
{
    frac_t timebase;
    tick_scale(&timebase);

    return safe_clock_scale(clock, timebase.numer, timebase.denom);
}

uint64_t clock_res(void)
{
    frac_t timebase;
    tick_scale(&timebase);

    return timebase.numer / timebase.denom;
}
