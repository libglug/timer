#ifndef GLUG_TIMER_H
#define GLUG_TIMER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

GLUG_EXTERN_START

GLUG_LIB_API struct glug_timer *    glug_timer_create(void);
GLUG_LIB_API void                   glug_timer_dispose(struct glug_timer *);

// controls
GLUG_LIB_API void                   glug_timer_start(struct glug_timer *);
GLUG_LIB_API void                   glug_timer_pause(struct glug_timer *);
GLUG_LIB_API void                   glug_timer_reset(struct glug_timer *);

// deltas
GLUG_LIB_API glug_time_t            glug_timer_split_reset(struct glug_timer *);
GLUG_LIB_API glug_time_t            glug_timer_split(const struct glug_timer *);

// totals
GLUG_LIB_API glug_time_t            glug_timer_run_time(const struct glug_timer *);

// state
GLUG_LIB_API glug_time_t            glug_timer_resolution(void);
GLUG_LIB_API enum glug_timer_state  glug_timer_state(const struct glug_timer *);

GLUG_EXTERN_END

#endif // GLUG_TIMER_H
