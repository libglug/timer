#include <glug/timer/continuous_timer.h>
#include <glug/timer/time_t.h>
#include <glug/timer/version.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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

    printf("Using timer v%d.%d.%d\n",
           GLUG_TIMER_VERSION_MAJOR,
           GLUG_TIMER_VERSION_MINOR,
           GLUG_TIMER_VERSION_PATCH);

    struct glug_allocator alloc =
    {
        malloc,
        free
    };

    struct glug_continuous_timer *t;
    glug_cont_timer_alloc(&alloc, &t);

    struct glug_time time;
    glug_cont_timer_resolution(&time);

    printf("timer resolution: %uns\n", time.nsec);

    int ctrl = 0;
    while(tolower(ctrl) != 'q')
    {
        print_controls();
        ctrl = getchar();
        while (getchar() != '\n'); // flush input
        switch (ctrl)
        {
        case 's':
            glug_cont_timer_start(t);
            break;
        case 'p':
            glug_cont_timer_pause(t);
            break;
        case 'r':
            glug_cont_timer_reset(t);
            break;
        case 't':
            glug_cont_timer_run_time(t, &time);
            printf("total run time: %.3fms\n", msec_from_glug_time(&time));
            break;
        case 'd':
            glug_cont_timer_delta(t, &time);
            printf("delta: %.3fms\n", msec_from_glug_time(&time));
            break;
        }
    }

    return 0;
}
