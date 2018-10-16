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

struct glug_timer GLUG_LIB_API *glug_create_timer()
{
    struct glug_timer *timer = malloc(sizeof(struct glug_timer));
    timer->state = glug_ts_stopped;
    return timer;
}

void GLUG_LIB_API glug_dispose_timer(struct glug_timer *timer)
{
    free(timer);
}

void GLUG_LIB_API glug_start_timer(struct glug_timer *timer)
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

void GLUG_LIB_API glug_pause_timer(struct glug_timer *timer)
{
    if (timer->state == glug_ts_running)
    {
        timer->pause_clock = read_clock();
        timer->state = glug_ts_paused;
    }
}

void GLUG_LIB_API glug_reset_timer(struct glug_timer *timer)
{
    clear_timer(timer);

    if (timer->state == glug_ts_paused)
        timer->state = glug_ts_stopped;
}

glug_time_t GLUG_LIB_API glug_split(struct glug_timer *timer)
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

    return split / clock_frequency();
}

glug_time_t GLUG_LIB_API glug_split_cont(const struct glug_timer *timer)
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

    return split / clock_frequency();
}

glug_time_t GLUG_LIB_API glug_running_time(const struct glug_timer *timer)
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

    return run_time / clock_frequency();
}

glug_time_t GLUG_LIB_API glug_resolution(const struct glug_timer *timer)
{
    (void) timer;
    return clock_res();
}

enum glug_timer_state GLUG_LIB_API glug_timer_state(const struct glug_timer *timer)
{
    return timer->state;
}
