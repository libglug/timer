#include "mach.h"

// continuous_ticks
static uint64_t continuous = 0;

void set_continuous_ticks(const uint64_t *ticks)
{
    continuous = *ticks;
}
void continuous_ticks(uint64_t *ticks)
{
    *ticks = continuous;
}

// absolute_ticks
static uint64_t absolute = 0;

void set_absolute_ticks(const uint64_t *ticks)
{
    absolute = *ticks;
}
void absolute_ticks(uint64_t *ticks)
{
    *ticks = absolute;
}

// tick_scale
static frac_t scale = { 0, 1 };

void set_tick_scale(const frac_t *ts)
{
    scale = *ts;
}

void tick_scale(frac_t *ts)
{
    *ts = scale;
}
