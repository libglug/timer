#ifndef GLUG_TIMER_HPP
#define GLUG_TIMER_HPP

#include <glug/timer/timer.h>
#include <glug/timer/timer_state.h>

namespace glug
{

class timer
{
public:
    timer();
    virtual ~timer();

    void start();
    void pause();
    void reset();

    glug_time_t split_reset();
    glug_time_t split() const;

    glug_time_t duration() const;
    enum glug_timer_state state() const;
    static glug_time_t resolution();

private:
    glug_timer *glug_timer;
};

} // namespace glug

#endif // GLUG_TIMER_HPP
