/* *****************************
 Name:     Alon Nov
 Exercise: queue
 Date:     22.10.2024
 Reviewer: Liran Mazor
 
********************************/

#include <stdlib.h>  /* size_t, malloc, free */
#include <assert.h>  /* assert */

#include "sll.h"     /* sll_t, SLLCreate, SLLDestroy, SLLInsert, SLLRemove, 
						SLLCount, SLLAppend, SLLGetData, SLLBegin */
#include "queue.h"   /* API */

struct queue
{
	sll_t* list;	
};		

/***************************QCreate**************************************/
queue_t* QCreate(void)
{
	queue_t* queue = malloc(sizeof(queue_t));	
	if(NULL == queue)
	{
		return NULL;
	}
	
	queue->list = SLLCreate();
	if(NULL == queue->list)
	{
		free(queue);
		return NULL;
	}

	return queue;
}

/***************************QDestroy**************************************/
void QDestroy(queue_t* queue)
{
	SLLDestroy(queue->list);
	free(queue);
	queue = NULL;
}	
	
void* QPeek(const queue_t* queue)
{
	return SLLGetData(SLLBegin(queue->list));
}	
	
/***************************QEnqueue**************************************/	
int QEnqueue(queue_t* queue, void* data)
{
	return SLLInsert(queue->list, SLLEnd(queue->list), data) 
			!= SLLEnd(queue->list);		
}

/***************************QDequeue**************************************/	
void QDequeue(queue_t* queue)
{
	SLLRemove(SLLBegin(queue->list));
}

/*****************************QSize***************************************/
size_t QSize(const queue_t* queue)
{
	return SLLCount(queue->list);
}

/***************************QIsEmpty**************************************/	
int QIsEmpty(const queue_t* queue)
{
	return SLLIsIterEq(SLLBegin(queue->list),SLLEnd(queue->list));
}

/***************************QAppend***************************************/	
queue_t* QAppend(queue_t* dest, queue_t* src)
{
	SLLAppend(dest->list, src->list);
	
	return dest;
}					
	
