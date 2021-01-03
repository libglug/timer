#ifndef GLUG_UPTIME_TIMER_H
#define GLUG_UPTIME_TIMER_H

#include <glug/import.h>
#include <glug/extern.h>

#include <glug/allocator_t.h>
#include <glug/timer/timer_state.h>

GLUG_EXTERN_START

struct glug_uptime_timer;
struct glug_time;

struct glug_iuptime_timer
{
    void                    (* alloc)(const struct glug_allocator *, struct glug_uptime_timer **);
    void                    (* free) (struct glug_uptime_timer **);

    // controls
    void                    (* start)(struct glug_uptime_timer *);
    void                    (* pause)(struct glug_uptime_timer *);
    void                    (* reset)(struct glug_uptime_timer *);

    // read
    void                    (* delta)   (struct glug_uptime_timer *, struct glug_time *);
    void                    (* run_time)(struct glug_uptime_timer *, struct glug_time *);

    // state
    void                    (* resolution)(struct glug_time *);
    enum glug_timer_state   (* state)     (const struct glug_uptime_timer *);
};

#ifdef GLUG_USE_TYPEDEFS
    typedef struct glug_iuptime_timer     glug_iuptime_timer_t;
#endif

GLUG_LIB_API void glug_iuptime_timer_init(struct glug_iuptime_timer *);

GLUG_EXTERN_END

#endif // GLUG_UPTIME_TIMER_H
