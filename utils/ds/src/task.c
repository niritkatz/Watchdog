/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Scheduler
 * Reviewer: Bella
 * Last Update: 03/03/2024
 *****************************************/
 
 #include <stddef.h> /*size_t*/
 #include <time.h> /*time_t*/
 #include <stdlib.h> /*malloc*/
 #include <assert.h> /*assert*/
 #include "task.h" /*task_t*/
 
 struct task
 {
 	ilrd_uid_t uid;
	task_action_func_t action;
	task_clean_func_t cleanup;
	void *action_params;
	void *cleanup_params;
	size_t interval;
	time_t exec_time;
 };
 
 task_t *TaskCreate(size_t interval, task_action_func_t action, void* action_params, 
 					task_clean_func_t cleanup , void *cleanup_params)
 {
 	task_t *task = NULL;
 	
 	ilrd_uid_t new_uid = UIDGenerate();
 	if (UIDIsEqual(new_uid, bad_uid))
 	{
 		return (NULL);
 	}
 	
 	task = (task_t *)malloc(sizeof(task_t));
 	if (NULL == task)
 	{
 		return (NULL);
 	}
 	
 	task->uid = new_uid;
 	task->action = action;
 	task->cleanup = cleanup;
 	task->action_params = action_params;
 	task->cleanup_params = cleanup_params;
 	task->interval = interval;
 	task->exec_time = time(NULL) + interval;
 	
 	return (task);
 }
 
 void TaskDestroy(task_t *task)
 {
 	assert(task);
 	
 	if (NULL != task->cleanup)
 	{
 		task->cleanup(task->cleanup_params);
 	}
 	
 	free (task);
 }
 
 ilrd_uid_t TaskGetUID(const task_t *task)
 {
 	assert(task);
 	
 	return (task->uid);
 }
 
 int TaskRun(task_t *task)
 {
 	int status = task->action(task->action_params);
 	
 	assert(task);
 	
 	if (status < 0)
 	{
 		task->cleanup(task->cleanup_params);
 	}
 	
 	return (status);
 }
 
 int TaskIsSame(const task_t *task1, const task_t *task2)
 {
 	assert(task1);
 	assert(task2);
 	
 	return (UIDIsEqual(task1->uid, task2->uid));
 }
 
 time_t TaskGetTimeToRun(const task_t *task)
 {
 	return (task->exec_time);
 }
 
 void TaskUpdateTimeToRun(task_t *task)
 {
 	task->exec_time =  time(NULL) + task->interval;
 }

