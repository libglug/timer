#include "timer_bridge.h"
#include <glug/timer/time_t.h>
#include <frac_t.h>

// read_continuous_ticks
static uint64_t cont_ticks = 0;
void set_continuous_ticks(const uint64_t *ticks)
{
    cont_ticks = *ticks;
}

void read_continuous_ticks(uint64_t *ticks)
{
    *ticks = cont_ticks;
}

// continuous_tick_scale
static struct frac cont_scale = { 1, 1 };
void set_continuous_scale(const struct frac *scale)
{
    cont_scale = *scale;
}

void continuous_tick_scale(struct frac *scale)
{
    *scale = cont_scale;
}

// continuous_clock_res
static struct glug_time continuous_res = { 0, 0 };
void set_continuous_res(const struct glug_time *time)
{
    continuous_res = *time;
}

void continuous_clock_res(struct glug_time *time)
{
    *time = continuous_res;
}

// read_uptime_ticks
static uint64_t up_ticks = 0;
void set_uptime_ticks(const uint64_t *ticks)
{
    up_ticks = *ticks;
}

void read_uptime_ticks(uint64_t *ticks)
{
    *ticks = up_ticks;
}

// uptime_tick_scale
static struct frac up_scale = { 1, 1 };
void set_uptime_scale(const struct frac *scale)
{
    up_scale = *scale;
}

void uptime_tick_scale(struct frac *scale)
{
    *scale = up_scale;
}

// uptime_clock_res
static struct glug_time up_res = { 0, 0 };
void set_uptime_res(const struct glug_time *time)
{
    up_res = *time;
}

void uptime_clock_res(struct glug_time *time)
{
    *time = up_res;
}
