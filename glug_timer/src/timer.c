#include <glug/timer/timer.h>
#include <glug/timer/time_t.h>
#include "timer.h"
#include "timer_platform.h"
#include "tick.h"
#include "frac.h"

static void clear_timer(struct glug_timer *);

void glug_timer_alloc(const struct glug_allocator *alloc, struct glug_timer **timer)
{
    *timer = alloc->malloc(sizeof(**timer));
    (*timer)->free = alloc->free;
    (*timer)->state = glug_ts_stopped;
    secs_per_tick(&(*timer)->tick_scale);
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
            uint64_t pause_dur;
            read_clock_ticks(&pause_dur);
            pause_dur -= timer->pause_clock;
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
        read_clock_ticks(&timer->pause_clock);
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
            uint64_t ticks;
            read_clock_ticks(&ticks);
            delta = ticks - timer->delta_clock - timer->pause_delta;
            timer->delta_clock = ticks;
            timer->pause_delta = 0;
            break;
        }
    }

    scale_to_time(&delta, &timer->tick_scale, time);
}

void glug_timer_run_time(struct glug_timer *timer, struct glug_time *elapsed)
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
        {
            uint64_t ticks;
            read_clock_ticks(&ticks);
            run_time = ticks - timer->start_clock - timer->pause_total;
            break;
        }
    }

    scale_to_time(&run_time, &timer->tick_scale, elapsed);
}

void glug_timer_resolution(struct glug_time *res)
{
    clock_res(res);
}

enum glug_timer_state glug_timer_state(const struct glug_timer *timer)
{
    return timer->state;
}

static void clear_timer(struct glug_timer *timer)
{
    read_clock_ticks(&timer->start_clock);
    timer->pause_clock = timer->start_clock;
    timer->delta_clock = timer->start_clock;
    timer->pause_delta = timer->pause_total = 0;
}

void glug_itimer_init(struct glug_itimer *itimer)
{
    itimer->alloc      = glug_timer_alloc;
    itimer->free       = glug_timer_free;
    itimer->start      = glug_timer_start;
    itimer->pause      = glug_timer_pause;
    itimer->reset      = glug_timer_reset;
    itimer->delta      = glug_timer_delta;
    itimer->run_time   = glug_timer_run_time;
    itimer->resolution = glug_timer_resolution;
    itimer->state      = glug_timer_state;
}
