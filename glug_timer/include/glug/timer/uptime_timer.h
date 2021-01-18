#ifndef GLUG_UPTIME_TIMER_H
#define GLUG_UPTIME_TIMER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/allocator_t.h>
#include <glug/timer/timer_state.h>

GLUG_EXTERN_START

struct glug_uptime_timer;
struct glug_time;

GLUG_LIB_API void                   glug_uptime_timer_alloc(const struct glug_allocator *, struct glug_uptime_timer **);
GLUG_LIB_API void                   glug_uptime_timer_free (struct glug_uptime_timer **);

// controls
GLUG_LIB_API void                   glug_uptime_timer_start(struct glug_uptime_timer *);
GLUG_LIB_API void                   glug_uptime_timer_pause(struct glug_uptime_timer *);
GLUG_LIB_API void                   glug_uptime_timer_reset(struct glug_uptime_timer *);

// read
GLUG_LIB_API void                   glug_uptime_timer_delta   (struct glug_uptime_timer *, struct glug_time *);
GLUG_LIB_API void                   glug_uptime_timer_run_time(struct glug_uptime_timer *, struct glug_time *);

// state
GLUG_LIB_API enum glug_timer_state  glug_uptime_timer_state     (const struct glug_uptime_timer *);
GLUG_LIB_API void                   glug_uptime_timer_resolution(struct glug_time *);

GLUG_EXTERN_END

#endif // GLUG_UPTIME_TIMER_H
