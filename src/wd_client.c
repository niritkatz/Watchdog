#include "wd.h"
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main(int argc, const char **argv)
{
    size_t i = 0;

    (void)argc;
    
    WDStart(argv);
    for (i=0; i<20; i++)
    {
        sleep(1);
    }
    WDStop();

    return (0);
}
