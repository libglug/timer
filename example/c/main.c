#include <glug/timer/timer.h>

#include <stdio.h>
#include <stdlib.h>

void print_controls()
{
    printf("--------------------------------\n");
    printf("s: start\np: pause\nr: reset\n");
    printf("t: print elapsed\n");
    printf("l: print split\nc: print split and continue\n");
    printf("enter selection: ");
}

double msec_from_glug_time(glug_time_t time)
{
    return time / 1000.0 / 1000.0;
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    struct glug_timer *t;
    glug_time_t res = glug_timer_resolution();
    int ctrl = 0;
    struct glug_allocator alloc =
    {
        malloc,
        free
    };

    glug_timer_alloc(&t, &alloc);
    printf("timer resolution: %llu\n", res);

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
            printf("total run time: %.3fms\n", msec_from_glug_time(glug_timer_run_time(t)));
            break;
        case 'l':
            printf("split: %.3fms\n", msec_from_glug_time(glug_timer_split_reset(t)));
            break;
        case 'c':
            printf("split: %.3fms\n", msec_from_glug_time(glug_timer_split(t)));
            break;
        }
    }

    return 0;
}
