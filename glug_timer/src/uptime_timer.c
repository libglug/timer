#include <glug/timer/uptime_timer.h>
#include <glug/timer/time_t.h>
#include "timer.h"
#include "timer_bridge.h"

static void uptime_timer_alloc(const struct glug_allocator *alloc, struct glug_uptime_timer **timer)
{
    *timer = alloc->malloc(sizeof(**timer));
    (*timer)->base.free = alloc->free;
    (*timer)->base.state = glug_ts_stopped;
    uptime_tick_scale(&(*timer)->base.tick_scale);
}

static void uptime_timer_free(struct glug_uptime_timer **timer)
{
    (*timer)->base.free(*timer);
    *timer = NULL;
}

static void uptime_timer_start(struct glug_uptime_timer *timer)
{
    timer_start(&timer->base, read_uptime_ticks);
}

static void uptime_timer_pause(struct glug_uptime_timer *timer)
{
    timer_pause(&timer->base, read_uptime_ticks);
}

static void uptime_timer_reset(struct glug_uptime_timer *timer)
{
    timer_reset(&timer->base, read_uptime_ticks);
}

static void uptime_timer_delta(struct glug_uptime_timer *timer, struct glug_time *res)
{
    timer_delta(&timer->base, read_uptime_ticks, res);
}

static void uptime_timer_run_time(struct glug_uptime_timer *timer, struct glug_time *res)
{
    timer_run_time(&timer->base, read_uptime_ticks, res);
}

static void uptime_timer_resolution(struct glug_time *res)
{
    uptime_clock_res(res);
}

static enum glug_timer_state uptime_timer_state(const struct glug_uptime_timer *timer)
{
    return timer_state(&timer->base);
}

void glug_iuptime_timer_init(struct glug_iuptime_timer *itimer)
{
    itimer->alloc      = uptime_timer_alloc;
    itimer->free       = uptime_timer_free;
    itimer->start      = uptime_timer_start;
    itimer->pause      = uptime_timer_pause;
    itimer->reset      = uptime_timer_reset;
    itimer->delta      = uptime_timer_delta;
    itimer->run_time   = uptime_timer_run_time;
    itimer->resolution = uptime_timer_resolution;
    itimer->state      = uptime_timer_state;
}
