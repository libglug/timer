#include <glug/timer/continuous_timer.h>
#include <glug/timer/time_t.h>
#include "timer.h"
#include "timer_bridge.h"

static void continuous_timer_alloc(const struct glug_allocator *alloc, struct glug_continuous_timer **timer)
{
    *timer = alloc->malloc(sizeof(**timer));
    (*timer)->base.free = alloc->free;
    (*timer)->base.state = glug_ts_stopped;
    continuous_tick_scale(&(*timer)->base.tick_scale);
}

static void continuous_timer_free(struct glug_continuous_timer **timer)
{
    (*timer)->base.free(*timer);
    *timer = NULL;
}

static void continuous_timer_start(struct glug_continuous_timer *timer)
{
    timer_start(&timer->base, read_continuous_ticks);
}

static void continuous_timer_pause(struct glug_continuous_timer *timer)
{
    timer_pause(&timer->base, read_continuous_ticks);
}

static void continuous_timer_reset(struct glug_continuous_timer *timer)
{
    timer_reset(&timer->base, read_continuous_ticks);
}

static void continuous_timer_delta(struct glug_continuous_timer *timer, struct glug_time *res)
{
    timer_delta(&timer->base, read_continuous_ticks, res);
}

static void continuous_timer_run_time(struct glug_continuous_timer *timer, struct glug_time *res)
{
    timer_run_time(&timer->base, read_continuous_ticks, res);
}

static void continuous_timer_resolution(struct glug_time *res)
{
    continuous_clock_res(res);
}

static enum glug_timer_state continuous_timer_state(const struct glug_continuous_timer *timer)
{
    return timer_state(&timer->base);
}

void glug_icontinuous_timer_init(struct glug_icontinuous_timer *itimer)
{
    itimer->alloc      = continuous_timer_alloc;
    itimer->free       = continuous_timer_free;
    itimer->start      = continuous_timer_start;
    itimer->pause      = continuous_timer_pause;
    itimer->reset      = continuous_timer_reset;
    itimer->delta      = continuous_timer_delta;
    itimer->run_time   = continuous_timer_run_time;
    itimer->resolution = continuous_timer_resolution;
    itimer->state      = continuous_timer_state;
}
