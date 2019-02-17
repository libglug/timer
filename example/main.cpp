#include <glug/timer/timer.h>
#include <glug/timer/time.h>

#include <iostream>

using namespace std;

void print_controls()
{
    cout << "--------------------------------" << endl;
    cout << "s: start\np: pause\nr: reset" << endl;
    cout << "t: print elapsed" << endl;
    cout << "l: print split\nc: print split and continue" << endl;
    cout << "enter selection: " << flush;
}

int main(int, char **)
{
    struct glug_timer *t = glug_timer_create();
    glug_time_t res = glug_timer_resolution(t);
    char ctrl = '\0';

    cout << "timer resolution: " << res << endl;

    while(ctrl != 'q')
    {
        print_controls();
        cin >> ctrl;
        switch (ctrl)
        {
        case 's':
            glug_timer_start(t);
            break;
        case 'p':
            glug_timer_pause(t);
            break;
        case 'r':
            glug_timer_reset(t);
            break;
        case 't':
            cout << "total run time: " << glug_msec_from_time(glug_timer_run_time(t)) << "ms" << endl;
            break;
        case 'l':
            cout << "split: " << glug_msec_from_time(glug_timer_split(t))  << "ms" << endl;
            break;
        case 'c':
            cout << "split: " << glug_msec_from_time(glug_timer_split_cont(t)) << "ms" << endl;
            break;
        }
    }

    return 0;
}
