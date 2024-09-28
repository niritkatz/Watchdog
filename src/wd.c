#define _GNU_SOURCE
#define _POSIX_SOURCE
#include <pthread.h> /*pthread_create*/
#include <stdatomic.h> /*atomic_int*/
#include <unistd.h> /*get pid*/
#include <stdio.h> /*printf*/
#include <stdlib.h> /*setenv*/
#include <string.h> /*strcmp*/
#include <semaphore.h> /*sem_t*/
#include <fcntl.h> /*sem_open*/
#include <signal.h> /*sigaction*/
#include <sys/wait.h> /*wait*/

#include <scheduler.h> /*sched_t*/
#include "wd.h" /*WD API*/

#define LIMIT (5)
#define WD_ENV ("WD_PID")
#define WD_PROC ("/wd_proc")
#define WD_CLIENT ("/wd_client")

atomic_int fails_counter = 0;
atomic_int is_finish = 0;

typedef struct wdproc
{
    const char **cmd;
    pid_t partner_pid;
    scheduler_t *sched;
    int is_wd;
    sem_t *sem_wd;
    sem_t *sem_client;
    pthread_t communication_thread;
}wdproc_t;

wdproc_t wd_struct = {0};
char* const wd_cmd[20] = {"./wd_proc"};
char* const client_cmd[20] = {"./wd_client"};

static void *WDSched(void *args);
static void InitHandlers();
static wd_status_t Revive();
static wd_status_t CreateSemaphores();
static void WDDestroy(void);

/*********************TASKS***************************/
static int Alivecheck(void *pid);
static int FailsCheck();
static int RollBack(void *pid);

/*********************HANDLERS************************/
static void Sigusr1Handler();
static void Sigusr2Handler();


wd_status_t WDStart(const char **cmd)
{
    pid_t child_pid = 0;
    wd_status_t status = WD_SUCCESS;
    const char *wd_pid = NULL;

    wd_struct.cmd = cmd;
    status = CreateSemaphores();
    wd_pid = getenv(WD_ENV);

    if (!(strcmp(cmd[0], wd_cmd[0])))
    {
        wd_struct.is_wd = 1;
        wd_struct.partner_pid = getppid();
        WDSched(NULL);
    }

    else    
    {
        if (NULL == wd_pid)
        {
            child_pid = fork();
            if (child_pid == -1)
            {
                return(1);
            }

            if (child_pid == 0)
            {
                execvp("./wd_proc", wd_cmd); 
                printf("Something Went Wrong\n");
                _exit(0);
            }
            wd_struct.partner_pid = child_pid; 
        }

        else
        {   
            wd_struct.partner_pid = atoi(wd_pid); 
        }
        
        wd_struct.is_wd = 0;
        status = pthread_create(&wd_struct.communication_thread, NULL, WDSched, NULL);
        if (status != WD_SUCCESS)
        {
            return (WD_FAILURE);
        } 
    }
    
    return (status);
}

void WDStop(void)
{
    kill(wd_struct.partner_pid, SIGUSR2);
    sem_wait(wd_struct.sem_wd);
    SchedStop(wd_struct.sched); 
    
    pthread_join(wd_struct.communication_thread, NULL);
}


/****************************STATIC FUNC********************************/

static void *WDSched(void *args)
{
    ilrd_uid_t uid = {0};
    pid_t pid = wd_struct.partner_pid;
    
    InitHandlers();

    wd_struct.sched =  SchedCreate();
    if (NULL == wd_struct.sched)
    {
        return ((void*)WD_FAILURE);
    }

    uid = SchedAddTask(wd_struct.sched, 2, Alivecheck, &pid, NULL, NULL);
    if (UIDIsEqual(bad_uid, uid))
    {
        
        return ((void*)WD_FAILURE);
    }

    uid = SchedAddTask(wd_struct.sched, 2, FailsCheck, NULL, NULL, NULL);
    if (UIDIsEqual(bad_uid, uid))
    {
        return ((void*)WD_FAILURE);
    }

    uid = SchedAddTask(wd_struct.sched, 4, RollBack, &pid, NULL, NULL);
    if (UIDIsEqual(bad_uid, uid))
    {
        return ((void*)WD_FAILURE);
    }

    sem_post(wd_struct.is_wd ? wd_struct.sem_wd : wd_struct.sem_client);
    sem_wait(wd_struct.is_wd ? wd_struct.sem_client : wd_struct.sem_wd);

    SchedRun(wd_struct.sched);
    
    WDDestroy();

    return (wd_struct.sched);
}

static void InitHandlers()
{ 
    struct sigaction action1 = {NULL};
    struct sigaction action2 = {NULL};

    action1.sa_handler = Sigusr1Handler;
    action2.sa_handler = Sigusr2Handler;

    sigaction(SIGUSR1, &action1, NULL);
    sigaction(SIGUSR2, &action2, NULL);
}

static wd_status_t CreateSemaphores()
{
    wd_struct.sem_client = sem_open("/sem_client",  O_CREAT, 0666, 0);
    if (SEM_FAILED == wd_struct.sem_client)
    {
        printf ("Sem Client Open Failed\n");
        return (WD_FAILURE);
    }

    wd_struct.sem_wd = sem_open("/sem_wd",  O_CREAT, 0666, 0);
    if (SEM_FAILED == wd_struct.sem_wd)
    {
        printf ("Sem_write Open Failed\n");
        return (WD_FAILURE);
    }

    return (WD_SUCCESS);
}

static wd_status_t Revive()
{
    wd_status_t status = WD_SUCCESS;
    pid_t child_pid = {0};
    char pid_val[10];

    printf("**Revive**, %d\n", getpid());
    child_pid = fork();
    if (-1 == child_pid)
    {
        return WD_FAILURE;
    }

    if (0 == child_pid)
    {
        if (wd_struct.is_wd)
        {
            sprintf(pid_val, "%d", getpid());
            setenv(WD_ENV, pid_val, 1); 
            execvp("./wd_client", client_cmd);
            _exit(1);
        }

        execvp("./wd_proc", wd_cmd);
        _exit(1);
    }

    wd_struct.partner_pid = child_pid;

    return (status);
}

static void WDDestroy(void)
{
    SchedDestroy(wd_struct.sched);

    sem_unlink("/sem_client");
    sem_close(wd_struct.sem_client);

    sem_unlink("/sem_wd");
    sem_close(wd_struct.sem_wd);
}

static int Alivecheck(void *pid)
{
    printf("alive %d\n" , *(pid_t *)pid);
    kill(*(pid_t *)pid, SIGUSR1);
    
    ++fails_counter;
    return(REPEAT);
}

static int FailsCheck()
{
    printf("count %d\n", fails_counter);
    if (fails_counter > LIMIT)
    {
        printf("Restart\n");
        Revive();
        atomic_store(&fails_counter, 0);

        sem_post(wd_struct.is_wd ? wd_struct.sem_wd : wd_struct.sem_client);
        sem_wait(!wd_struct.is_wd ? wd_struct.sem_wd : wd_struct.sem_client);
    }

    return(REPEAT);
}

static int RollBack(void *pid)
{
    if (is_finish)
    {
        printf("Rollback %d\n" , *(pid_t *)pid);
        sem_post(wd_struct.sem_wd);
        SchedStop(wd_struct.sched); 
    }
    
    return(REPEAT);
}

static void Sigusr1Handler()
{
    atomic_store(&fails_counter, 0);
}

static void Sigusr2Handler()
{
    atomic_store(&is_finish, 1);
}


