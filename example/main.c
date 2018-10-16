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

    struct glug_timer *t = glug_create_timer();
    glug_time_t res = glug_resolution(t);
    int ctrl = 0;

    printf("timer resolution: %lld\n", res);

    print_controls();
    while((ctrl = getchar()) != 'q')
    {
        while(getchar() != '\n'); // flush input
        switch (ctrl)
        {
        case 's':
            glug_start_timer(t);
            break;
        case 'p':
            glug_pause_timer(t);
            break;
        case 'r':
            glug_reset_timer(t);
            break;
        case 't':
            printf("total run time %.2lfms\n", glug_msec_from_time(glug_running_time(t)));
            break;
        case 'l':
            printf("split: %.2lfms\n", glug_msec_from_time(glug_split(t)));
            break;
        case 'c':
            printf("split: %.2lfms\n", glug_msec_from_time(glug_split_cont(t)));
            break;
        }
        print_controls();
    }

    return 0;
}
