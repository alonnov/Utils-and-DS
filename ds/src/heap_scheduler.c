/* *****************************
 Name:     Alon Nov
 Exercise: heap
 Date:	   12.12.2024   
 Reviewer: Mor Weisberg

********************************/

#include <stdlib.h>  /* size_t, malloc, free */
#include <string.h>  /* memset */
#include <unistd.h>	 /* sleep */
#include <assert.h>  /* assert */

#include "task.h"		/* TaskClean, TaskCreate, TaskGetUnID, TaskGetTime, 
						   TaskRun */
#include "uid.h"
#include "heap_PQ.h" 	/* PQ_t, PQCreate, PQDequeue, 
						   PQDestroy, PQEnqueue, */
#include "heap_scheduler.h"	/* API */

struct scheduler
{
    pq_t* pq_tasks;
    int is_running;
    unid_t current_running_task;
};

/*****************************CompFunc****************************************/
static int CompFunc(const void* data1, const void* data2)
{
	return TaskGetTime((task_t*)data1) - TaskGetTime((task_t*)data2);
}


/*****************************MatchID****************************************/
static int MatchID(const void* data, const void* param)
{
	return UnIDIsEqual(TaskGetUnID((task_t*)data), *(unid_t*)param);
}
	
		
/**************************SchedulerCreate************************************/
scheduler_t* SchedulerCreate()
{
	scheduler_t* sched = (scheduler_t*)malloc(sizeof(scheduler_t));	
	if(NULL == sched)
	{
		return NULL;
	}
	
	sched->pq_tasks = PQCreate(CompFunc);
	if(!sched->pq_tasks)
	{
		free(sched);
		return NULL;
	}
		
	sched->is_running = 0;
	sched->current_running_task = bad_unid;
		
	return sched;					
}	


/**************************SchedulerDestroy***********************************/	
void SchedulerDestroy(scheduler_t* sched)
{	
	SchedulerClear(sched);
	PQDestroy(sched->pq_tasks);
	memset(sched, 0, sizeof(scheduler_t));
	free(sched);
}		
		

/***************************SchedulerAddTask**********************************/	
unid_t SchedulerAddTask(scheduler_t* sched, operation_func_t operation, 
						cleanup_func_t cleanup, time_t when, void* opt_params,
						void* cleanup_params)
{
	task_t* task = NULL;
	
	assert(sched);
	assert(operation);

	task = TaskCreate(operation, cleanup, when, opt_params, cleanup_params);
	if(NULL == task)
	{
		return bad_unid;
	}
	
	if(0 != PQEnqueue(sched->pq_tasks, task))
	{
		TaskClean(task);
		return bad_unid;
	}
	
	return TaskGetUnID(task);
}	


/************************SchedulerRemoveTask*********************************/
void SchedulerRemoveTask(scheduler_t* sched, unid_t task_id)
{
	task_t* task = NULL;
	
	assert(sched);
	
	if(UnIDIsEqual(task_id, sched->current_running_task))
	{
		sched->current_running_task = bad_unid;
		return;	
	}	
	
	task = (task_t*)PQRemoveBy(sched->pq_tasks, MatchID, &task_id);
	if(task)
	{
		TaskClean(task);
	}
}


/************************SchedulerRun****************************************/
size_t SchedulerRun(scheduler_t* sched)
{
	task_t* task = NULL;
	time_t interval = 0;
	time_t task_time = 0;
	size_t res = 0;
	
	assert(sched);
	printf("%ld before\n",SchedulerSize(sched));
	sched->is_running = 1;
	while(sched->is_running && !SchedulerIsEmpty(sched))
	{
	
		task = PQDequeue(sched->pq_tasks);
		sched->current_running_task = TaskGetUnID(task);
		
		task_time = TaskGetTime(task);
		while(time(NULL) < task_time)
		{
			sleep(task_time - time(NULL));
		}
											
		interval = TaskRun(task);
		
		if(interval && !UnIDIsEqual(bad_unid, sched->current_running_task))
		{ 	
			TaskSetTime(task, time(NULL) + interval);
			PQEnqueue(sched->pq_tasks, task);
		}
		else
		{
			TaskClean(task);	
		}				
		++res;
		printf("%ld \n",SchedulerSize(sched));											
	}
	sched->current_running_task = bad_unid;
	sched->is_running = 0;
	
	return res;
}


/************************SchedulerStop***************************************/
void SchedulerStop(scheduler_t* sched)
{
	assert(sched);
	
	sched->is_running = 0;
}


/************************SchedulerSize***************************************/
size_t SchedulerSize(const scheduler_t* sched)
{
	assert(sched);
	
	return PQSize(sched->pq_tasks);
}


/************************SchedulerClear**************************************/
void SchedulerClear(scheduler_t* sched)
{	
	assert(sched);
	
	while(!SchedulerIsEmpty(sched)) 
	{
		TaskClean((task_t*)PQDequeue(sched->pq_tasks));
	}
}


/***********************SchedulerIsEmpty*************************************/
int SchedulerIsEmpty(const scheduler_t* sched)
{
	assert(sched);
	
	return PQIsEmpty(sched->pq_tasks);
}

