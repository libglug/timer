#include "uptime_timer.hpp"

namespace glug
{

uptime_timer::uptime_timer(glug_allocator &allocator)
{
    glug_uptime_timer_alloc(&allocator, &timer_impl);
}

uptime_timer::~uptime_timer()
{
    glug_uptime_timer_free(&timer_impl);
}

void uptime_timer::start()
{
    glug_uptime_timer_start(timer_impl);
}

void uptime_timer::pause()
{
    glug_uptime_timer_pause(timer_impl);
}

void uptime_timer::reset()
{
    glug_uptime_timer_reset(timer_impl);
}

void uptime_timer::delta(time &delta)
{
    glug_uptime_timer_delta(timer_impl, &delta);
}

void uptime_timer::duration(time &run_time) const
{
    glug_uptime_timer_run_time(timer_impl, &run_time);
}

enum glug_timer_state uptime_timer::state() const
{
    return glug_uptime_timer_state(timer_impl);
}

void uptime_timer::resolution(time &res)
{
    glug_uptime_timer_resolution(&res);
}

} // namespace glug
