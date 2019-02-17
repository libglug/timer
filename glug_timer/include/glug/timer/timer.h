#ifndef GLUG_TIMER_H
#define GLUG_TIMER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

GLUG_EXTERN_START

GLUG_LIB_API struct glug_timer *    glug_create_timer(void);
GLUG_LIB_API void                   glug_dispose_timer(struct glug_timer *);

// controls
GLUG_LIB_API void                   glug_start_timer(struct glug_timer *);
GLUG_LIB_API void                   glug_pause_timer(struct glug_timer *);
GLUG_LIB_API void                   glug_reset_timer(struct glug_timer *);

// deltas
GLUG_LIB_API glug_time_t            glug_split(struct glug_timer *);
GLUG_LIB_API glug_time_t            glug_split_cont(const struct glug_timer *);

// totals
GLUG_LIB_API glug_time_t            glug_running_time(const struct glug_timer *);

// state
GLUG_LIB_API glug_time_t            glug_resolution (const struct glug_timer *);
GLUG_LIB_API enum glug_timer_state  glug_timer_state(const struct glug_timer *);

GLUG_EXTERN_END

#endif // GLUG_TIMER_H
