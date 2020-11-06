#ifndef GLUG_TIMER_H
#define GLUG_TIMER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/allocator_t.h>
#include <glug/timer/timer_t.h>
#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

GLUG_EXTERN_START

struct glug_itimer
{
    void                    (* alloc)(const struct glug_allocator *, struct glug_timer **);
    void                    (* free)(struct glug_timer **);

    // controls
    void                    (* start)(struct glug_timer *);
    void                    (* pause)(struct glug_timer *);
    void                    (* reset)(struct glug_timer *);

    // read
    void                    (* delta)(struct glug_timer *, struct glug_time *);
    void                    (* run_time)(struct glug_timer *, struct glug_time *);

    // state
    void                    (* resolution)(struct glug_time *);
    enum glug_timer_state   (* state)(const struct glug_timer *);
};

#ifdef GLUG_USE_TYPEDEFS
    typedef struct glug_itimer   glug_itimer_t;
#endif

GLUG_LIB_API void glug_itimer_init(struct glug_itimer *);

GLUG_EXTERN_END

#endif // GLUG_TIMER_H
