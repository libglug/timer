#include <glug/timer/timer.h>
#include <glug/timer/time.h>

#include <stdio.h>

void print_controls()
{
    printf("--------------------------------\n");
    printf("s: start\np: pause\nr: reset\n");
    printf("t: print elapsed\n");
    printf("l: print split\nc: print split and continue\n");
    printf("enter selection: ");
}

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    struct glug_timer *t = glug_timer_create();
    glug_time_t res = glug_timer_resolution();
    int ctrl = 0;

    printf("timer resolution: %lld\n", res);

    while(ctrl != 'q')
    {
        print_controls();
        ctrl = getchar();
        while(getchar() != '\n'); // flush input
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
            printf("total run time: %.3lfms\n", glug_msec_from_time(glug_timer_run_time(t)));
            break;
        case 'l':
            printf("split: %.3lfms\n", glug_msec_from_time(glug_timer_split(t)));
            break;
        case 'c':
            printf("split: %.3lfms\n", glug_msec_from_time(glug_timer_split_cont(t)));
            break;
        }
    }

    return 0;
}
