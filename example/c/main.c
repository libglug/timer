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

    struct glug_timer *t;
    glug_timer_alloc(&alloc, &t);

    struct glug_time time;
    glug_timer_resolution(&time);

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
            glug_timer_start(t);
            break;
        case 'p':
            glug_timer_pause(t);
            break;
        case 'r':
            glug_timer_reset(t);
            break;
        case 't':
            glug_timer_run_time(t, &time);
            printf("total run time: %.3fms\n", msec_from_glug_time(&time));
            break;
        case 'd':
            glug_timer_delta(t, &time);
            printf("delta: %.3fms\n", msec_from_glug_time(&time));
            break;
        }
    }

    return 0;
}
