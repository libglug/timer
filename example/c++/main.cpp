#include <iostream>
#include "timer.hpp"

void print_controls()
{
    std::cout << "--------------------------------" << std::endl <<
                 "s: start\np: pause" << std::endl <<
                 "r: reset" << std::endl <<
                 "t: print elapsed" << std::endl <<
                 "l: print split" << std::endl <<
                 "c: print split and continue" << std::endl <<
                 "enter selection: " << std::flush;
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
        case 'l':
            std::cout << "split: " << msec_from_glug_time(t.split_reset()) << "ms" << std::endl;
            break;
        case 'c':
            std::cout << "split: " << msec_from_glug_time(t.split())<< "ms" << std::endl;
            break;
        }

        print_controls();
        std::cin >> ctrl;
    }

    return 0;
}
