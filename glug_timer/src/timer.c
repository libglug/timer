#include <glug/timer/timer.h>
#include <glug/timer/time_t.h>
#include "timer.h"
#include "timer_platform.h"

#include <stdlib.h>

static void clear_timer(struct glug_timer *timer)
{
    timer->start_clock = read_clock();
    timer->pause_clock = timer->start_clock;
    timer->split_clock = timer->start_clock;
    timer->pause_split = timer->pause_total = 0;
}

struct glug_timer *glug_timer_create(void)
{
    struct glug_timer *timer = malloc(sizeof(struct glug_timer));
    timer->state = glug_ts_stopped;
    return timer;
}

void glug_timer_dispose(struct glug_timer *timer)
{
    free(timer);
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
        glug_time_t pause_dur = read_clock() - timer->pause_clock;
        timer->pause_split += pause_dur;
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
        timer->pause_clock = read_clock();
        timer->state = glug_ts_paused;
    }
}

void glug_timer_reset(struct glug_timer *timer)
{
    clear_timer(timer);

    if (timer->state == glug_ts_paused)
        timer->state = glug_ts_stopped;
}

glug_time_t glug_timer_split(struct glug_timer *timer)
{
    glug_time_t split;
    switch(timer->state)
    {
    case glug_ts_stopped:
        split = 0;
        break;
    case glug_ts_paused:
        split = timer->pause_clock - timer->split_clock;
        timer->split_clock = timer->pause_clock;
        break;
    case glug_ts_running:
    {
        uint64_t clock = read_clock();
        split = clock - timer->split_clock - timer->pause_split;
        timer->split_clock = clock;
        timer->pause_split = 0;
        break;
    }
    }

    return clock_to_nsec(split);
}

glug_time_t glug_timer_split_cont(const struct glug_timer *timer)
{
    glug_time_t split;
    switch(timer->state)
    {
    case glug_ts_stopped:
        split = 0;
        break;
    case glug_ts_paused:
        split = timer->pause_clock - timer->split_clock;
        break;
    case glug_ts_running:
        split = read_clock() - timer->split_clock - timer->pause_split;
        break;
    }

    return clock_to_nsec(split);
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
        run_time = read_clock() - timer->start_clock - timer->pause_total;
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
