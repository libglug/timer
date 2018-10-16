#ifndef GLUG_TIMER_H
#define GLUG_TIMER_H

#include <glug/import.h>

#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

struct glug_timer     GLUG_LIB_API *glug_create_timer();
void                  GLUG_LIB_API  glug_dispose_timer(struct glug_timer *);

// controls
void                  GLUG_LIB_API  glug_start_timer(struct glug_timer *);
void                  GLUG_LIB_API  glug_pause_timer(struct glug_timer *);
void                  GLUG_LIB_API  glug_reset_timer(struct glug_timer *);

// deltas
glug_time_t           GLUG_LIB_API  glug_split(struct glug_timer *);
glug_time_t           GLUG_LIB_API  glug_split_cont(const struct glug_timer *);

// totals
glug_time_t           GLUG_LIB_API  glug_running_time(const struct glug_timer *);

// state
glug_time_t           GLUG_LIB_API  glug_resolution (const struct glug_timer *);
enum glug_timer_state GLUG_LIB_API  glug_timer_state(const struct glug_timer *);

#endif // GLUG_TIMER_H
