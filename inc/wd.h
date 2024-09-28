#ifndef __ILRD_WD_1556__
#define __ILRD_WD_1556__

typedef enum wd_status
{
    WD_SUCCESS = 0,
    WD_FAILURE
} wd_status_t;

/*
Description:
    -Defends a critical section: if this section crushes, the program is revived
Params:
    -cmd: command line to reinitiate the process {"./a.out", "arguments"...}
Return:
    -status:
        -SUCCESS: section is protected
        -FAILURE: section isn't protected
Notes:
    -this utility uses SIGUSR1 SIGUSR2 signal
*/
wd_status_t WDStart(const char **cmd);

/*
Description:
    -Ends the critical section
Notes:
    -Function does not guarentee to free used resources immediately at function exit
*/
void WDStop(void);

#endif /* __ILRD_WD_1556__ */