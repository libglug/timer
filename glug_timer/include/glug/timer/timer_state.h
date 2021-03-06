#ifndef GLUG_TIMER_STATE_H
#define GLUG_TIMER_STATE_H

enum glug_timer_state
{
    glug_ts_stopped,
    glug_ts_running,
    glug_ts_paused
};

#ifdef GLUG_USE_TYPEDEFS
    typedef enum glug_timer_state glug_timer_state_t;
#endif

#endif // GLUG_TIMER_STATE_H
