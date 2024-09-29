/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Scheduler
 * Reviewer: Bella
 * Last Update: 03/03/2024
 *****************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "uid.h" /* ilrd_uid_t */

/*******************************************************************************
A scheduler is a mechanism for executing tasks at specified intervals. 
It manages tasks with associated actions, intervals, and cleanup functions.
*******************************************************************************/

/*******************************************************************************
Callback function type for the action to be performed by a task.
Param: Parameter to be passed to the action function.
Return: Action status.
*******************************************************************************/
typedef int (*action_func_t)(void* param);

/*******************************************************************************
Callback function type for cleanup.
Param: Parameter to be passed to the cleanup function.
*******************************************************************************/
typedef void (*cleanup_func_t)(void* param);
typedef struct scheduler scheduler_t;

typedef enum sched_status
{
    ERROR = -1,
    SUCCESS,
    STOP,
    REPEAT
}sched_status_t;

/*******************************************************************************
Description: Creates a new scheduler
Return Value: A pointer to the newly created scheduler.
Complexity: O(1)
*******************************************************************************/
scheduler_t *SchedCreate(void);

/*******************************************************************************
Description: Destroy a scheduler
Parameters:
     sched: Pointer to the scheduler object to be destroyed
Complexity: O(n)
*******************************************************************************/
void SchedDestroy(scheduler_t *sched);

/*******************************************************************************
Description: Adds a task to the scheduler.
Parameters:
     sched: pointer to the relevant scheduler
     interval: Time interval in which the task will be executed.
     action: Pointer to the function to be executed as the task.
     action_params: Parameters to be passed to the action function.
     cleanup: Pointer to the cleanup function to be executed after the task
     		 completes.
     cleanup_params: Parameters to be passed to the cleanup function.
Return Value: Unique ID representing the added task.
Complexity: O(n)
*******************************************************************************/
ilrd_uid_t SchedAddTask(scheduler_t *sched, size_t interval, action_func_t 
     action, void *action_params, cleanup_func_t cleanup, void *cleanup_params); 

/*******************************************************************************
Description: Removes a task from the scheduler.
Parameters:
     sched: pointer to the relevant scheduler
     task_id: Unique ID of the task to be removed.
Return Value: 0 for success, otherwise -1.
Complexity: O(n)
*******************************************************************************/
int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t task_id); 

/*******************************************************************************
Description: Runs the scheduler.
Parameters:
     sched: pointer to the relevant scheduler
Return Value: Scheduler status indicating success or failure.
Complexity: O(n)
*******************************************************************************/
int SchedRun(scheduler_t *sched);  

/*******************************************************************************
Description: Stops the scheduler.
Parameters:
     sched: pointer to the relevant scheduler
Return Value: Scheduler status indicating success or failure.
Complexity: O(1)
*******************************************************************************/
int SchedStop(scheduler_t *sched);  

/*******************************************************************************
Description: Clears all tasks from the scheduler.
Parameters:
     sched: pointer to the relevant scheduler
Complexity: O(n)
*******************************************************************************/
void SchedClear(scheduler_t *sched); 

/*******************************************************************************
Description: Retrieves the number of tasks in the scheduler.
Parameters:
     sched: pointer to the relevant scheduler
Return Value: The number of tasks in the scheduler.
Complexity: O(n)
*******************************************************************************/
size_t SchedSize(const scheduler_t *sched); 

/*******************************************************************************
Description: Checks if the scheduler is empty.
Parameters:
     sched: pointer to the relevant scheduler
Return Value: 1 if empty, 0 otherwise.
Complexity: O(1)
*******************************************************************************/
int SchedIsEmpty(const scheduler_t *sched);  

#endif /*SCHEDULER_H*/
