#ifndef GLUG_STRUCT_TIMER_H
#define GLUG_STRUCT_TIMER_H

#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

#include <stdint.h>

struct glug_timer
{
    uint64_t start_clock, pause_clock, split_clock;
    uint64_t pause_split, pause_total;
    enum glug_timer_state state;
};

#endif // GLUG_STRUCT_TIMER_H
