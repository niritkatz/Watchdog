/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Scheduler
 * Reviewer: Bella
 * Last Update: 03/03/2024
 *****************************************/
 
#ifndef TASK_H
#define TASK_H

#include "uid.h" /* ilrd_uid_t */

typedef struct task task_t;

/*******************************************************************************
Callback function type for the action to be performed by a task.
Param: Parameter to be passed to the action function.
Return: Action status.
*******************************************************************************/
typedef int (*task_action_func_t)(void* param);

/*******************************************************************************
Callback function type for cleanup.
Param: Parameter to be passed to the cleanup function.
*******************************************************************************/
typedef void (*task_clean_func_t)(void* param);

/*******************************************************************************
Description: Creates a new task
Parameters:
	interval: Time interval for the task execution.
	action: Pointer to the function to be executed as the task action.
	action_params: Parameters to be passed to the action function.
	cleanup: Pointer to the cleanup function to be executed after the task 
		   completes.
	cleanup_params: Parameters to be passed to the cleanup function.
Return Value: A pointer to the newly created task.
Complexity: O(1)
*******************************************************************************/
task_t *TaskCreate(size_t interval, task_action_func_t action, void* action_params, 
					task_clean_func_t cleanup , void *cleanup_params); 
					
/*******************************************************************************
Description: Destroys a task 
Parameters:
	task: Pointer to the task object to be destroyed.
Complexity: O(n)
*******************************************************************************/
void TaskDestroy(task_t *task);

/*******************************************************************************
Description: Retrieves the unique ID of a task.
Parameters:
	task: Pointer to a task object
Return Value: The unique ID of the task.
Complexity: O(1)
*******************************************************************************/
ilrd_uid_t TaskGetUID(const task_t *task);

/*******************************************************************************
Description: Executes the action associated with the task.
Parameters:
	task: Pointer to a task object
Return Value: Task status indicating success or failure.
Complexity: O(1)
*******************************************************************************/
int TaskRun(task_t *task);

/*******************************************************************************
Description: Checks if two task objects are the same.
Parameters:
	task1: Pointer to the first task object.
	task2: Pointer to the second task object.
Return Value: 1 if the tasks are the same, 0 otherwise.
Complexity: O(n)
*******************************************************************************/
int TaskIsSame(const task_t *task1, const task_t *task2);

/*******************************************************************************
Description: Retrieves the time at which the task is scheduled to run.
Parameters:
	task: Pointer to a task object
Return Value: The time at which the task is scheduled to run.
Complexity: O(1)
*******************************************************************************/
time_t TaskGetTimeToRun(const task_t *task);

/*******************************************************************************
Description: Updates the time at which the task is scheduled to run.
Parameters:
	task: Pointer to a task object
Complexity: O(1)
*******************************************************************************/
void TaskUpdateTimeToRun(task_t *task);

#endif /*TASK_H*/


