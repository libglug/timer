#ifndef GLUG_TIMER_HPP
#define GLUG_TIMER_HPP

#include <glug/timer/timer.h>
#include <glug/timer/timer_state.h>

namespace glug
{

using time = struct glug_time;

class timer
{
public:
    timer();
    virtual ~timer();

    void start();
    void pause();
    void reset();

    void delta(time &);
    void duration(time &) const;

    enum glug_timer_state state() const;
    static void resolution(time &res);

private:
    glug_timer *glug_timer_impl;
};

} // namespace glug

#endif // GLUG_TIMER_HPP
