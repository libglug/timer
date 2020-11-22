#ifndef GLUG_TIMER_H
#define GLUG_TIMER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/allocator_t.h>
#include <glug/timer/timer_t.h>
#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

GLUG_EXTERN_START

GLUG_LIB_API void                   glug_timer_alloc(struct glug_timer **, struct glug_allocator *);
GLUG_LIB_API void                   glug_timer_free(struct glug_timer **);

// controls
GLUG_LIB_API void                   glug_timer_start(struct glug_timer *);
GLUG_LIB_API void                   glug_timer_pause(struct glug_timer *);
GLUG_LIB_API void                   glug_timer_reset(struct glug_timer *);

// read
GLUG_LIB_API void                   glug_timer_delta(struct glug_timer *, struct glug_time *);
GLUG_LIB_API void                   glug_timer_run_time(const struct glug_timer *, struct glug_time *);

// state
GLUG_LIB_API void                   glug_timer_resolution(struct glug_time *);
GLUG_LIB_API enum glug_timer_state  glug_timer_state(const struct glug_timer *);

GLUG_EXTERN_END

#endif // GLUG_TIMER_H
