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

double msec_from_glug_time(glug_time_t time)
{
    return time / 1000.0 / 1000.0;
}

int main(int, char **)
{
    glug::timer t;

    std::cout << "timer resolution: " << glug::timer::resolution() << std::endl;
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
            std::cout << "total run time: " << msec_from_glug_time(t.duration()) << "ms" << std::endl;
            break;
        case 'd':
            std::cout << "split: " << msec_from_glug_time(t.delta()) << "ms" << std::endl;
            break;
        }

        print_controls();
        std::cin >> ctrl;
    }

    return 0;
}
