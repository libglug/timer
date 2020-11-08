#include <glug/timer/timer.h>
#include <glug/timer/time_t.h>
#include "timer.h"
#include "timer_platform.h"
#include "safe_clock_scale.h"

static uint64_t clock_to_nsec(uint64_t clock);
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
            glug_time_t pause_dur = read_clock_ticks() - timer->pause_clock;
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

glug_time_t glug_timer_delta(struct glug_timer *timer)
{
    glug_time_t delta;
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

    return clock_to_nsec(delta);
}

glug_time_t glug_timer_run_time(const struct glug_timer *timer)
{
    glug_time_t run_time;
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

    return clock_to_nsec(run_time);
}

glug_time_t glug_timer_resolution(void)
{
    return clock_res();
}

enum glug_timer_state glug_timer_state(const struct glug_timer *timer)
{
    return timer->state;
}

static uint64_t clock_to_nsec(uint64_t clock)
{
    frac_t tps = {0};
    ticks_per_sec(&tps);
    return safe_clock_scale(clock, &tps);
}

static void clear_timer(struct glug_timer *timer)
{
    timer->start_clock = read_clock_ticks();
    timer->pause_clock = timer->start_clock;
    timer->delta_clock = timer->start_clock;
    timer->pause_delta = timer->pause_total = 0;
}
