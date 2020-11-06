#include "timer.hpp"
#include <stdlib.h>

namespace glug
{

timer::timer()
{
    struct glug_allocator alloc =
    {
        .malloc = malloc,
        .free = free
    };
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

glug_time_t timer::split_reset()
{
    return glug_timer_split_reset(glug_timer_impl);
}

glug_time_t timer::split() const
{
    return glug_timer_split(glug_timer_impl);
}

glug_time_t timer::duration() const
{
    return glug_timer_run_time(glug_timer_impl);
}

enum glug_timer_state timer::state() const
{
    return glug_timer_state(glug_timer_impl);
}

glug_time_t timer::resolution()
{
    return glug_timer_resolution();
}

} // namespace glug
