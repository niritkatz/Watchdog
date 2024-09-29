/***************************************** 
 * Owner: Nirit Katz
 * Title: DS - Scheduler
 * Reviewer: Bella
 * Last Update: 03/03/2024
 *****************************************/

#include <stdlib.h> /*malloc*/
#include <assert.h> /*assert*/
#include <unistd.h> /*sleep*/
#include "pqueue.h" /*pq_t*/
#include "scheduler.h" /*scheduler_t*/
#include "task.h" /*task_t*/
/*#include "scheduler.hpp"*/

static int PriorityRule(const void *data, const void *dest_data);
static int FindToRemove(const void *data, void *param);

struct scheduler
{
    pq_t *priority_queue;
    task_t *active;
    int is_running;
};

scheduler_t *SchedCreate(void)
{
	scheduler_t *sched = (scheduler_t *)malloc(sizeof(scheduler_t));
	if (NULL == sched)
	{
		return (NULL);
	}
	
	sched->priority_queue = PQCreate(PriorityRule);
	if (NULL == sched->priority_queue)
	{
		SchedDestroy(sched);
		return (NULL);
	}
	
	sched->active = NULL;
	sched->is_running = 0;
	
	return (sched);
}

void SchedDestroy(scheduler_t *sched)
{
	assert (sched);
	
	SchedClear(sched);
	
	PQDestroy(sched->priority_queue);
	free(sched);
}

ilrd_uid_t SchedAddTask(scheduler_t *sched, size_t interval, action_func_t action, 
		void *action_params, cleanup_func_t cleanup, void *cleanup_params)
{
	task_t *task = TaskCreate(interval, action, action_params, 
 									 cleanup, cleanup_params);	
 	if (NULL == task)
 	{
 		return (bad_uid);
 	}
 	
 	
 	if (1 == PQEnqueue(sched->priority_queue, task))
 	{
 		return (bad_uid);
 	}
 	
	return (TaskGetUID(task));
}

int SchedRemoveTask(scheduler_t *sched, ilrd_uid_t task_id)
{
	task_t *task = PQErase(sched->priority_queue, FindToRemove, &task_id);
	if (NULL == task)
	{
		return (ERROR);	
	}
	
	TaskDestroy(task);
	
	return (SUCCESS);
}

int SchedRun(scheduler_t *sched)
{
	int status = SUCCESS;
	
	assert(sched);
	
	sched->is_running = 1;
	
	while (!SchedIsEmpty(sched) && ERROR != status && sched->is_running)
	{
		while (TaskGetTimeToRun(PQPeek(sched->priority_queue)) > time(NULL))
        {
            sleep(1);
        }

		sched->active = PQDequeue(sched->priority_queue);
		
		status = TaskRun(sched->active);
		
		if (REPEAT == status)
		{
			TaskUpdateTimeToRun(sched->active);
			
			if (PQEnqueue(sched->priority_queue, sched->active))
 			{
 				status = ERROR;
 			}		
		}
		
		else
		{
			if (ERROR == status)
			{
				SchedStop(sched);
			}
			
			TaskDestroy(sched->active);
		}
		
		sched->active = NULL;
	}
	
	sched->is_running = 0;
	
	return (status);
}

int SchedStop(scheduler_t *sched)
{
	assert (sched);
	
	sched->is_running = 0;
	
	return (STOP);
}

void SchedClear(scheduler_t *sched)
{
	assert (sched);
	
	while (!SchedIsEmpty(sched))
	{
		TaskDestroy(PQDequeue(sched->priority_queue));
	}

	if (sched->active)
	{
		TaskDestroy(sched->active);
	} 
}

size_t SchedSize(const scheduler_t *sched)
{
	assert(sched); 

	return (PQCount(sched->priority_queue) + sched->is_running);
}

int SchedIsEmpty(const scheduler_t *sched)
{
	assert(sched); 
	
	return (PQIsEmpty(sched->priority_queue) && !sched->active);
}

/***********************STATIC FUNCTION****************************************/

static int PriorityRule(const void *data, const void *dest_data)
{
	return (TaskGetTimeToRun((task_t*)data) - TaskGetTimeToRun((task_t*)dest_data));
}

static int FindToRemove(const void *data, void *param)
{
	return (UIDIsEqual(TaskGetUID(data), *(ilrd_uid_t *)param));
} 



