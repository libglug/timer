#include "timer.hpp"
#include <stdlib.h>

namespace glug
{

timer::timer()
{
    struct glug_allocator alloc = { malloc, free };
    glug_itimer_init(&glug_itimer);
    glug_itimer.alloc(&alloc, &glug_timer_impl);
}

timer::~timer()
{
    glug_itimer.free(&glug_timer_impl);
}

void timer::start()
{
    glug_itimer.start(glug_timer_impl);
}

void timer::pause()
{
    glug_itimer.pause(glug_timer_impl);
}

void timer::reset()
{
    glug_itimer.reset(glug_timer_impl);
}

void timer::delta(time &delta)
{
    glug_itimer.delta(glug_timer_impl, &delta);
}

void timer::duration(time &run_time) const
{
    glug_itimer.run_time(glug_timer_impl, &run_time);
}

enum glug_timer_state timer::state() const
{
    return glug_itimer.state(glug_timer_impl);
}

void timer::resolution(time &res)
{
    glug_itimer.resolution(&res);
}

} // namespace glug
