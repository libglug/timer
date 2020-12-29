#ifndef GLUG_STRUCT_TIMER_H
#define GLUG_STRUCT_TIMER_H

#include <glug/allocator_t.h>
#include <glug/timer/timer_state.h>
#include "frac_t.h"

#include <stdint.h>

struct glug_time;

struct glug_timer
{
    glug_free_t free;
    uint64_t start_clock, pause_clock, delta_clock;
    uint64_t pause_delta, pause_total;
    struct frac tick_scale;
    enum glug_timer_state state;
};

struct glug_continuous_timer
{
    struct glug_timer base;
};

struct glug_uptime_timer
{
    struct glug_timer base;
};

GLUG_LIB_LOCAL void timer_start(struct glug_timer *, void (*)(uint64_t *));
GLUG_LIB_LOCAL void timer_pause(struct glug_timer *, void (*)(uint64_t *));
GLUG_LIB_LOCAL void timer_reset(struct glug_timer *, void (*)(uint64_t *));

GLUG_LIB_LOCAL void timer_delta(struct glug_timer *, void (*)(uint64_t *), struct glug_time *);
GLUG_LIB_LOCAL void timer_run_time(struct glug_timer *, void (*)(uint64_t *), struct glug_time *);

GLUG_LIB_LOCAL enum glug_timer_state timer_state(const struct glug_timer *);

#endif // GLUG_STRUCT_TIMER_H
