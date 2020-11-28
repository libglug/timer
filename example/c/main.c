#include <glug/timer/timer.h>

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

void print_controls(void)
{
    printf("--------------------------------\n"
           "s: start\n"
           "p: pause\n"
           "r: reset\n"
           "d: print delta\n"
           "t: print elapsed\n"
           "q: quit\n"
           "enter selection: ");
}

double msec_from_glug_time(struct glug_time *time)
{
    return time->sec * 1000 + time->nsec/ 1000.0 / 1000.0;
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    struct glug_allocator alloc =
    {
        malloc,
        free
    };

    struct glug_itimer itimer;
    glug_itimer_init(&itimer);

    struct glug_timer *t;
    itimer.alloc(&alloc, &t);

    struct glug_time time;
    itimer.resolution(&time);

    printf("timer resolution: %uns\n", time.nsec);

    int ctrl = 0;
    while(ctrl != 'q')
    {
        print_controls();
        ctrl = getchar();
        while (getchar() != '\n'); // flush input
        switch (ctrl)
        {
        case 's':
            itimer.start(t);
            break;
        case 'p':
            itimer.pause(t);
            break;
        case 'r':
            itimer.reset(t);
            break;
        case 't':
            itimer.run_time(t, &time);
            printf("total run time: %.3fms\n", msec_from_glug_time(&time));
            break;
        case 'd':
            itimer.delta(t, &time);
            printf("delta: %.3fms\n", msec_from_glug_time(&time));
            break;
        }
    }

    return 0;
}
