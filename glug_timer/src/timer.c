#include "timer.h"

#include <glug/timer/time_t.h>
#include "tick.h"

static void clear_timer(struct glug_timer *, void (*)(uint64_t *));

void timer_start(struct glug_timer *timer, void (*read_ticks)(uint64_t *))
{
    switch(timer->state)
    {
        case glug_ts_stopped:
            clear_timer(timer, read_ticks);
            break;
        case glug_ts_paused:
        {
            uint64_t pause_dur;
            read_ticks(&pause_dur);
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

void timer_pause(struct glug_timer *timer, void (*read_ticks)(uint64_t *))
{
    if (timer->state == glug_ts_running)
    {
        read_ticks(&timer->pause_clock);
        timer->state = glug_ts_paused;
    }
}

void timer_reset(struct glug_timer *timer, void (*read_ticks)(uint64_t *))
{
    if (timer->state == glug_ts_running)
        clear_timer(timer, read_ticks);
    else if (timer->state == glug_ts_paused)
        timer->state = glug_ts_stopped;
}

void timer_delta(struct glug_timer *timer, void (*read_ticks)(uint64_t *), struct glug_time *res)
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
            read_ticks(&ticks);
            delta = ticks - timer->delta_clock - timer->pause_delta;
            timer->delta_clock = ticks;
            timer->pause_delta = 0;
            break;
        }
    }

    scale_to_time(&delta, &timer->tick_scale, res);
}

void timer_run_time(struct glug_timer *timer, void (*read_ticks)(uint64_t *), struct glug_time *res)
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
            read_ticks(&ticks);
            run_time = ticks - timer->start_clock - timer->pause_total;
            break;
        }
    }

    scale_to_time(&run_time, &timer->tick_scale, res);
}

enum glug_timer_state timer_state(const struct glug_timer *timer)
{
    return timer->state;
}

static void clear_timer(struct glug_timer *timer, void (*read_ticks)(uint64_t *))
{
    read_ticks(&timer->start_clock);
    timer->pause_clock = timer->start_clock;
    timer->delta_clock = timer->start_clock;
    timer->pause_delta = timer->pause_total = 0;
}
