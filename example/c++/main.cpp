#include <iostream>
#include "timer.hpp"

void print_controls()
{
    std::cout << "--------------------------------" << std::endl <<
                 "s: start\np: pause\nr: reset" << std::endl <<
                 "t: print elapsed" << std::endl <<
                 "l: print split\nc: print split and continue" << std::endl <<
                 "enter selection: " << std::flush;
}

int main(int, char **)
{
    glug::timer t;

    std::cout << "timer resolution: " << glug::timer::resolution() << std::endl;
    print_controls();

    char ctrl = '\0';
    while(ctrl != 'q')
    {
        std::cin >> ctrl;

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
            std::cout << "total run time: " << glug_msec_from_time(t.duration()) << "ms" << std::endl;
            break;
        case 'l':
            std::cout << "split: " << glug_msec_from_time(t.split()) << "ms" << std::endl;
            break;
        case 'c':
            std::cout << "split: " << glug_msec_from_time(t.split_cont()) << "ms" << std::endl;
            break;
        }
        print_controls();
    }

    return 0;
}
