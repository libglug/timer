#include "timer.hpp"
#include <stdlib.h>

namespace glug
{

timer::timer()
{
    struct glug_allocator alloc = { malloc, free };
    glug_timer_alloc(&glug_timer_impl, &alloc);
}

timer::~timer()
{
    glug_timer_free(&glug_timer_impl);
}

void timer::start()
{
    glug_timer_start(glug_timer_impl);
}

void timer::pause()
{
    glug_timer_pause(glug_timer_impl);
}

void timer::reset()
{
    glug_timer_reset(glug_timer_impl);
}

void timer::delta(time &delta)
{
    glug_timer_delta(glug_timer_impl, &delta);
}

void timer::duration(time &run_time) const
{
    return glug_timer_run_time(glug_timer_impl, &run_time);
}

enum glug_timer_state timer::state() const
{
    return glug_timer_state(glug_timer_impl);
}

void timer::resolution(time &res)
{
    return glug_timer_resolution(&res);
}

} // namespace glug
