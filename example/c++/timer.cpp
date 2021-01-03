#include "timer.hpp"
#include <stdlib.h>

namespace glug
{

continuous_timer::continuous_timer()
{
    struct glug_allocator alloc = { malloc, free };
    glug_icontinuous_timer_init(&icont_timer);
    icont_timer.alloc(&alloc, &timer_impl);
}

continuous_timer::~continuous_timer()
{
    icont_timer.free(&timer_impl);
}

void continuous_timer::start()
{
    icont_timer.start(timer_impl);
}

void continuous_timer::pause()
{
    icont_timer.pause(timer_impl);
}

void continuous_timer::reset()
{
    icont_timer.reset(timer_impl);
}

void continuous_timer::delta(time &delta)
{
    icont_timer.delta(timer_impl, &delta);
}

void continuous_timer::duration(time &run_time) const
{
    icont_timer.run_time(timer_impl, &run_time);
}

enum glug_timer_state continuous_timer::state() const
{
    return icont_timer.state(timer_impl);
}

void continuous_timer::resolution(time &res)
{
    icont_timer.resolution(&res);
}

uptime_timer::uptime_timer()
{
    struct glug_allocator alloc = { malloc, free };
    glug_iuptime_timer_init(&icont_timer);
    icont_timer.alloc(&alloc, &timer_impl);
}

uptime_timer::~uptime_timer()
{
    icont_timer.free(&timer_impl);
}

void uptime_timer::start()
{
    icont_timer.start(timer_impl);
}

void uptime_timer::pause()
{
    icont_timer.pause(timer_impl);
}

void uptime_timer::reset()
{
    icont_timer.reset(timer_impl);
}

void uptime_timer::delta(time &delta)
{
    icont_timer.delta(timer_impl, &delta);
}

void uptime_timer::duration(time &run_time) const
{
    icont_timer.run_time(timer_impl, &run_time);
}

enum glug_timer_state uptime_timer::state() const
{
    return icont_timer.state(timer_impl);
}

void uptime_timer::resolution(time &res)
{
    icont_timer.resolution(&res);
}

} // namespace glug
