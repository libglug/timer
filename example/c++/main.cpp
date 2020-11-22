#include <iostream>
#include "timer.hpp"

void print_controls()
{
    std::cout << "--------------------------------" << std::endl
              << "s: start" << std:: endl
              << "p: pause" << std::endl
              << "r: reset" << std::endl
              << "d: print delta" << std::endl
              << "t: print elapsed" << std::endl
              << "q: quit" << std:: endl
              << "enter selection: " << std::flush;
}

double msec_from_glug_time(glug::time &time)
{
    return time.sec * 1000 + time.nsec / 1000.0 / 1000.0;
}

int main(int, char **)
{
    glug::timer t;

    glug::time time;
    glug::timer::resolution(time);
    std::cout << "timer resolution: " << msec_from_glug_time(time) << std::endl;
    print_controls();

    char ctrl = '\0';
    std::cin >> ctrl;

    while (ctrl != 'q')
    {
        switch (ctrl)
        {
        case 's':
            t.start();
            break;
        case 'p':
            t.pause();
            break;
        case 'r':
            t.reset();
            break;
        case 't':
            t.duration(time);
            std::cout << "total run time: " << msec_from_glug_time(time) << "ms" << std::endl;
            break;
        case 'd':
            t.delta(time);
            std::cout << "split: " << msec_from_glug_time(time) << "ms" << std::endl;
            break;
        }

        print_controls();
        std::cin >> ctrl;
    }

    return 0;
}
