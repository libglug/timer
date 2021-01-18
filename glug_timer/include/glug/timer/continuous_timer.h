#ifndef GLUG_CONTINUOUS_TIMER_H
#define GLUG_CONTINUOUS_TIMER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/allocator_t.h>
#include <glug/timer/timer_state.h>

GLUG_EXTERN_START

struct glug_continuous_timer;
struct glug_time;

GLUG_LIB_API void                    glug_cont_timer_alloc(const struct glug_allocator *, struct glug_continuous_timer **);
GLUG_LIB_API void                    glug_cont_timer_free (struct glug_continuous_timer **);

// controls
GLUG_LIB_API void                    glug_cont_timer_start(struct glug_continuous_timer *);
GLUG_LIB_API void                    glug_cont_timer_pause(struct glug_continuous_timer *);
GLUG_LIB_API void                    glug_cont_timer_reset(struct glug_continuous_timer *);

// read
GLUG_LIB_API void                    glug_cont_timer_delta   (struct glug_continuous_timer *, struct glug_time *);
GLUG_LIB_API void                    glug_cont_timer_run_time(struct glug_continuous_timer *, struct glug_time *);

// state
GLUG_LIB_API enum glug_timer_state   glug_cont_timer_state     (const struct glug_continuous_timer *);
GLUG_LIB_API void                    glug_cont_timer_resolution(struct glug_time *);

GLUG_EXTERN_END

#endif // GLUG_CONTINUOUS_TIMER_H
