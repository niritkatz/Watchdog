
#include <stdio.h> /*printf*/
#include "wd.h" /*WD API*/

int main(int argc, const char **argv)
{
    (void)argc;
    
    printf("WD Process ID: %s\n", argv[0]);

    WDStart(argv);
    
    return (0);
}