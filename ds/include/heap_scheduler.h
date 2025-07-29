/* *****************************
 Name:     Alon Nov
 Exercise: heap scheduler
 Date:	   12.12.2024   
 Reviewer: Mor Weisberg

********************************/

#ifndef _HEAP_SCHEDULER_H_ 
#define _HEAP_SCHEDULER_H_

#include <stddef.h> /* size_t */

#include "uid.h"
#include "task.h"

typedef struct scheduler scheduler_t;
	
	
/*@Desc - creates a task scheduler
* @Params - N/A
* @Return - pointer to the created scheduler
* @Return - NULL, if creation fails
* @Warnings - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
scheduler_t* SchedulerCreate();


/*@Desc - destroys all tasks in a given scheduler and the scheduler itself
* @Params - scheduler to destroy
* @Return - N/A
* @Warning - if schdlr param is not a pointer to a valid scheduler, 
			 can cause UB
* @time complexity - O(n)  
* @Space complexity - O(1) */
void SchedulerDestroy(scheduler_t* schdlr);


/*@Desc - adds a task to a given scheduler
* @Params - schdlr: scheduler to add task to 
* @Params - operation: operation the added task will do
* @Params - cleanup: cleanup function (created by the user) 
			the created task will have.
			cleans all temporary files/data created by the operation function 
* @Params - when: added task's start time
* @Params - opt_params: given operation function parameters
* @Params - cleanup_params: given cleanup function parameters
* @Return - uuid of the added task
* @Return - bad uuid
* @Warning - if schdlr param is not a pointer to a valid scheduler,
			 can cause UB
* @Warning - clean func can be NULL (will do nothing)
* @time complexity - O(n)   
* @Space complexity - O(1) */
unid_t SchedulerAddTask(scheduler_t* schdlr, operation_func_t operation, 
						cleanup_func_t cleanup, time_t when, void* opt_params,
						void* cleanup_params);
                             
                             
/*@Desc - removes the task that corresponds to the given unid from a given 
		  scheduler
* @Params - schdlr: scheduler to remove from
* @Params - task_id: unid of the task to remove
* @Return - N/A
* @Warning - N/A
* @time complexity - O(n)  
* @Space complexity - O(1) */
void SchedulerRemoveTask(scheduler_t* schdlr, unid_t task_id);


/*@Desc - starts the given scheduler with all current tasks
* @Params - schdlr: scheduler to start
* @Return - number of completed tasks
* @Warning - N/A
* @time complexity - O(n)  
* @Space complexity - O(1) */
size_t SchedulerRun(scheduler_t* schdlr);


/*@Desc - stops the current run of a given scheduler
* @Params - schdlr: scheduler to pause
* @Return - N/A
* @Warning - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
void SchedulerStop(scheduler_t* schdlr);


/*@desc - gets the number of tasks in a given scheduler
* @param - schdlr: scheduler to get number of tasks in
* @return - number of tasks in the given scheduler
* @Warning - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
size_t SchedulerSize(const scheduler_t* schdlr);


/*@Desc - removes all tasks from a given scheduler 
* @Params - schdlr: scheduler to remove tasks from 
* @Return - the given scheduler after all tasks were removed (empty)
* @Warning - if schdlr param is not a pointer to a valid scheduler,
			 can cause UB
* @Warning - N/A
* @time complexity - O(n)   
* @Space complexity - O(1) */
void SchedulerClear(scheduler_t* schdlr);


/*@Desc - tests if a given scheduler is empty (contains no tasks)
* @Params - schdlr: scheduler to test for emptiness
* @Return - 1 (TRUE) if empty
* @Return - 0 (FALSE) if not empty
* @time complexity - O(1) 
* @Space complexity - O(1) */
int SchedulerIsEmpty(const scheduler_t* schdlr);


#endif
