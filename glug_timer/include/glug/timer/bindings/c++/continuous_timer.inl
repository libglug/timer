#include "continuous_timer.hpp"

namespace glug
{

continuous_timer::continuous_timer(glug_allocator &allocator)
{
    glug_cont_timer_alloc(&allocator, &timer_impl);
}

continuous_timer::~continuous_timer()
{
    glug_cont_timer_free(&timer_impl);
}

void continuous_timer::start()
{
    glug_cont_timer_start(timer_impl);
}

void continuous_timer::pause()
{
    glug_cont_timer_pause(timer_impl);
}

void continuous_timer::reset()
{
    glug_cont_timer_reset(timer_impl);
}

void continuous_timer::delta(time &delta)
{
    glug_cont_timer_delta(timer_impl, &delta);
}

void continuous_timer::duration(time &run_time) const
{
    glug_cont_timer_run_time(timer_impl, &run_time);
}

enum glug_timer_state continuous_timer::state() const
{
    return glug_cont_timer_state(timer_impl);
}

void continuous_timer::resolution(time &res)
{
    glug_cont_timer_resolution(&res);
}

} // namespace glug
