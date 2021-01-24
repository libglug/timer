#ifndef GLUG_CONTINUOUS_TIMER_HPP
#define GLUG_CONTINUOUS_TIMER_HPP

#include <glug/timer/continuous_timer.h>
#include <glug/timer/time_t.h>
#include <glug/timer/timer_state.h>

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

} // namespace glug

#include "continuous_timer.inl"

#endif // GLUG_CONTINUOUS_TIMER_HPP
