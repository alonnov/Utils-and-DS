/* *****************************
 Name:     Alon Nov
 Exercise: priority queue 
 Date:	   10.11.2024   
 Reviewer: Israela Zimro

********************************/

#include <stdlib.h>  /* size_t, malloc, free */
#include <string.h>  /* memset */
#include <assert.h>  /* assert */

#include "slist.h"     /*SListCreate, SListDestroy, SListInsert, SListRemove, 
					   SListPopBack, SListPrev, SListBegin, SListEnd, 
					   SListIsIterEqual, SListGetData, SListFindIf, SListCount,
					   SListIsEmpty */
#include "pqueue.h"   /* API */


struct pqueue
{
    slist_t* slist;   
};


/***************************PQueueCreate***************************************/
pqueue_t* PQueueCreate(pqueue_compare_t compare)
{
	pqueue_t* pqueue = NULL;
		
	assert(NULL != compare);	
	
	pqueue = (pqueue_t*)malloc(sizeof(pqueue_t));
	if(NULL == pqueue)
	{
		return NULL;
	}
	
	pqueue->slist = SListCreate(compare);
	if(NULL == pqueue->slist)
	{
		free(pqueue);
		return NULL;
	}
			
	return pqueue;					
}	


/**************************PQueueDestroy**************************************/	
void PQueueDestroy(pqueue_t* pqueue)
{	
	assert(pqueue);
	
	SListDestroy(pqueue->slist);
	memset(pqueue, 0, sizeof(pqueue_t));
	free(pqueue);
}		
		

/***************************PQueueEnqueue*************************************/	
int PQueueEnqueue(pqueue_t* pqueue, void* data)
{
	assert(pqueue);
	
	return SListIsIterEqual(
		   SListInsert(pqueue->slist, data), SListEnd(pqueue->slist));		
}	


/**************************PQueueDequeue**************************************/
void* PQueueDequeue(pqueue_t* pqueue)
{
	assert(pqueue);
	
	return SListPopBack(pqueue->slist);
}


/***************************PQueuePeek***************************************/
void* PQueuePeek(const pqueue_t* pqueue)
{
	assert(pqueue);
	
	return SListGetData(SListPrev(SListEnd(pqueue->slist)));
}


/***************************PQueueSize***************************************/
size_t PQueueSize(const pqueue_t* pqueue)
{
	assert(pqueue);
	
	return SListCount(pqueue->slist);	
}


/**************************PQueueIsEmpty***********************************/
int PQueueIsEmpty(const pqueue_t* pqueue)
{
	assert(pqueue);
	
	return SListIsEmpty(pqueue->slist);
}


/***************************PQueueClear***************************************/
pqueue_t* PQueueClear(pqueue_t* pqueue)
{
	assert(pqueue);
	
	while(!PQueueIsEmpty(pqueue)) 
	{
		PQueueDequeue(pqueue);
	}
	
	return pqueue;
}		


/**************************PQueueRemoveBy*************************************/
void* PQueueRemoveBy(pqueue_t* pqueue, pqueue_match_t match_func, void* params)
{	
	void* data = NULL;
	slist_iter_t pos = {0};
	
	assert(pqueue);
	assert(match_func); 
	assert(params);
	
	pos = SListFindIf(SListBegin(pqueue->slist), SListEnd(pqueue->slist),
					  params, match_func);
	data = SListGetData(pos);					
	SListRemove(pos);	
						
	return data;			
}


