#include "timer.hpp"

namespace glug
{

timer::timer()
{
    glug_timer = glug_timer_create();
}

timer::~timer()
{
    glug_timer_dispose(glug_timer);
}

void timer::start()
{
    glug_timer_start(glug_timer);
}

void timer::pause()
{
    glug_timer_pause(glug_timer);
}

void timer::reset()
{
    glug_timer_reset(glug_timer);
}

glug_time_t timer::split()
{
    return glug_timer_split(glug_timer);
}

glug_time_t timer::split_cont() const
{
    return glug_timer_split_cont(glug_timer);
}

glug_time_t timer::duration() const
{
    return glug_timer_run_time(glug_timer);
}

enum glug_timer_state timer::state() const
{
    return glug_timer_state(glug_timer);
}

glug_time_t timer::resolution()
{
    return glug_timer_resolution();
}

} // namespace glug
