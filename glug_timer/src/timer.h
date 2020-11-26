#ifndef GLUG_STRUCT_TIMER_H
#define GLUG_STRUCT_TIMER_H

#include <glug/allocator_t.h>
#include <glug/timer/timer_state.h>
#include "frac.h"

#include <stdint.h>

struct glug_timer
{
    glug_free_t free;
    uint64_t start_clock, pause_clock, delta_clock;
    uint64_t pause_delta, pause_total;
    struct frac tick_scale;
    enum glug_timer_state state;
};

#endif // GLUG_STRUCT_TIMER_H
