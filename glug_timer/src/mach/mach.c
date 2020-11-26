#include "mach.h"

#include <mach/mach_time.h>

void continuous_ticks(uint64_t *ticks)
{
    *ticks = mach_continuous_time();
}

void absolute_ticks(uint64_t *ticks)
{
    *ticks = mach_absolute_time();
}

void tick_scale(frac_t *tick_scale)
{
    mach_timebase_info_data_t scale;
    mach_timebase_info(&scale);

    tick_scale->numer = scale.numer;
    tick_scale->denom = scale.denom;
}
