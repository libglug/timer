#ifndef GLUG_CONTINUOUS_TIMER_H
#define GLUG_CONTINUOUS_TIMER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/allocator_t.h>
#include <glug/timer/timer_state.h>

GLUG_EXTERN_START

struct glug_continuous_timer;
struct glug_time;

struct glug_icontinuous_timer
{
    void                    (* alloc)(const struct glug_allocator *, struct glug_continuous_timer **);
    void                    (* free) (struct glug_continuous_timer **);

    // controls
    void                    (* start)(struct glug_continuous_timer *);
    void                    (* pause)(struct glug_continuous_timer *);
    void                    (* reset)(struct glug_continuous_timer *);

    // read
    void                    (* delta)   (struct glug_continuous_timer *, struct glug_time *);
    void                    (* run_time)(struct glug_continuous_timer *, struct glug_time *);

    // state
    void                    (* resolution)(struct glug_time *);
    enum glug_timer_state   (* state)     (const struct glug_continuous_timer *);
};

#ifdef GLUG_USE_TYPEDEFS
    typedef struct glug_icontinuous_timer glug_icontinuous_timer_t;
#endif

GLUG_LIB_API void glug_icontinuous_timer_init(struct glug_icontinuous_timer *);

GLUG_EXTERN_END

#endif // GLUG_CONTINUOUS_TIMER_H
