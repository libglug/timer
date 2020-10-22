#include "mach.h"

#include <mach/mach_time.h>

uint64_t continuous_ticks(void)
{
    return mach_continuous_time();
}

uint64_t absolute_ticks(void)
{
    return mach_absolute_time();
}

void tick_scale(frac_t *tick_scale)
{
    mach_timebase_info_data_t scale;
    mach_timebase_info(&scale);

    tick_scale->numer = scale.numer;
    tick_scale->denom = scale.denom;
}
