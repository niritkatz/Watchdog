#define _POSIX_C_SOURCE 1
#include <stdio.h>
#include <wd.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    size_t i = 0;
    int is_res_twice = 0;

    if (NULL == getenv("WD_PID"))
    {
        WDStart((const char **) argv);
        printf("test main called arg(expected a): %s\n", argv[1]);
    }
    else
    {
        if (argv[1][0] == 'b')
        {
            printf("test main called arg(expected b): %s\n", argv[1]);
            is_res_twice = 1;
        }
        else
        {
            printf("test main called arg(expected a): %s\n", argv[1]);
            argv[1][0] = 'b';
            WDStart((const char **) argv);
        }
    }

    while(i < 100)
    {
        if (20 == i)
        {
            if (NULL == getenv("WD_PID"))
            {
                printf("client kill self\n");
                kill(getpid(), SIGKILL);
            }
        }
        
        if (40 == i)
        {
            if (NULL != getenv("WD_PID"))
            {
                printf("client kill wd(40)\n");
                kill(atoi(getenv("WD_PID")), SIGKILL);
            }
        }

        if (60 == i)
        {
            if (!is_res_twice)
            {
                printf("client kill self second time\n");
                kill(getpid(), SIGKILL);
            }
        }

        if (80 == i)
        {
            printf("client WDStop\n");
            WDStop();
        }
        sleep(1);
        i++;
    }
    printf("done and success\n");

    (void) argc;
    return 0;
}
