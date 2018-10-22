#include "../timer_platform.h"

#include <stdint.h>
#include <mach/mach_time.h>

extern uint64_t GLUG_LIB_LOCAL safe_clock_scale(uint64_t clock, uint64_t numer, uint64_t denom);

static mach_timebase_info_data_t clock_frequency()
{
    mach_timebase_info_data_t frequency;
    mach_timebase_info(&frequency);
    return frequency;
}

uint64_t GLUG_LIB_LOCAL read_clock()
{
    return mach_absolute_time();
}

uint64_t GLUG_LIB_LOCAL clock_to_nsec(uint64_t clock)
{
    mach_timebase_info_data_t frequency = clock_frequency();
    return safe_clock_scale(clock, frequency.numer, frequency.denom);
}

uint64_t GLUG_LIB_LOCAL clock_res()
{
    mach_timebase_info_data_t frequency = clock_frequency();
    return frequency.numer / frequency.denom;
}
