#include <glug/timer/timer.h>
#include <glug/timer/time_t.h>
#include "timer.h"
#include "timer_platform.h"
#include "tick.h"
#include "frac.h"

static void ticks_to_nsec(uint64_t clock, struct glug_time *);
static void clear_timer(struct glug_timer *timer);

void glug_timer_alloc(struct glug_timer **timer, struct glug_allocator *alloc)
{
    *timer = alloc->malloc(sizeof(**timer));
    (*timer)->free = alloc->free;
    (*timer)->state = glug_ts_stopped;
}

void glug_timer_free(struct glug_timer **timer)
{
    (*timer)->free(*timer);
    *timer = NULL;
}

void glug_timer_start(struct glug_timer *timer)
{
    switch(timer->state)
    {
        case glug_ts_stopped:
            clear_timer(timer);
            break;
        case glug_ts_paused:
        {
            uint64_t pause_dur = read_clock_ticks() - timer->pause_clock;
            timer->pause_delta += pause_dur;
            timer->pause_total += pause_dur;
            break;
        }
        case glug_ts_running:
            break;
    }

    timer->state = glug_ts_running;
}

void glug_timer_pause(struct glug_timer *timer)
{
    if (timer->state == glug_ts_running)
    {
        timer->pause_clock = read_clock_ticks();
        timer->state = glug_ts_paused;
    }
}

void glug_timer_reset(struct glug_timer *timer)
{
    clear_timer(timer);

    if (timer->state == glug_ts_paused)
        timer->state = glug_ts_stopped;
}

void glug_timer_delta(struct glug_timer *timer, struct glug_time *time)
{
    uint64_t delta;
    switch(timer->state)
    {
        case glug_ts_stopped:
            delta = 0;
            break;
        case glug_ts_paused:
            delta = timer->pause_clock - timer->delta_clock;
            timer->delta_clock = timer->pause_clock;
            break;
        case glug_ts_running:
        {
            uint64_t clock = read_clock_ticks();
            delta = clock - timer->delta_clock - timer->pause_delta;
            timer->delta_clock = clock;
            timer->pause_delta = 0;
            break;
        }
    }

    return ticks_to_nsec(delta, time);
}

void glug_timer_run_time(const struct glug_timer *timer, struct glug_time *elapsed)
{
    uint64_t run_time;
    switch(timer->state)
    {
        case glug_ts_stopped:
            run_time = 0;
            break;
        case glug_ts_paused:
            run_time = timer->pause_clock - timer->start_clock - timer->pause_total;
            break;
        case glug_ts_running:
            run_time = read_clock_ticks() - timer->start_clock - timer->pause_total;
            break;
    }

    return ticks_to_nsec(run_time, elapsed);
}

void glug_timer_resolution(struct glug_time *res)
{
    clock_res(res);
}

enum glug_timer_state glug_timer_state(const struct glug_timer *timer)
{
    return timer->state;
}

static void ticks_to_nsec(uint64_t ticks, struct glug_time *time)
{
    frac_t sec_per_tick = {0};
    secs_per_tick(&sec_per_tick);

    scale_to_time(ticks, &sec_per_tick, time);
}

static void clear_timer(struct glug_timer *timer)
{
    timer->start_clock = read_clock_ticks();
    timer->pause_clock = timer->start_clock;
    timer->delta_clock = timer->start_clock;
    timer->pause_delta = timer->pause_total = 0;
}
