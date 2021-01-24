#ifndef GLUG_UPTIME_TIMER_HPP
#define GLUG_UPTIME_TIMER_HPP

#include <glug/timer/uptime_timer.h>
#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

namespace glug
{

using time = glug_time;

class uptime_timer
{
public:
    uptime_timer(glug_allocator &);
    virtual ~uptime_timer();

    void start();
    void pause();
    void reset();

    void delta(time &);
    void duration(time &) const;

    enum glug_timer_state state() const;
    static void resolution(time &res);

private:
    glug_uptime_timer *timer_impl;
};

} // namespace glug

#include "uptime_timer.inl"

#endif // GLUG_UPTIME_TIMER_HPP
