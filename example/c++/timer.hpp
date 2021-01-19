#ifndef GLUG_TIMER_HPP
#define GLUG_TIMER_HPP

#include <glug/timer/continuous_timer.h>
#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

#include <glug/timer/uptime_timer.h>

namespace glug
{

using time = glug_time;

class continuous_timer
{
public:
    continuous_timer(glug_allocator &);
    virtual ~continuous_timer();

    void start();
    void pause();
    void reset();

    void delta(time &);
    void duration(time &) const;

    enum glug_timer_state state() const;
    static void resolution(time &res);

private:
    glug_continuous_timer *timer_impl;
};

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

#endif // GLUG_TIMER_HPP
