/* *****************************
 Name:     Alon Nov
 Exercise: heap priority queue
 Date:	   12.12.2024   
 Reviewer: Mor Weisberg

********************************/

#include <stdlib.h>  /* size_t, malloc, free */
#include <string.h>  /* memset */
#include <assert.h>  /* assert */

#include "heap.h"   /* API */
#include "heap_PQ.h"   /* API */


struct pq
{
    heap_t* heap;   
};


/***************************PQCreate***************************************/
pq_t* PQCreate(pq_compare_t compare)
{
	pq_t* pq = NULL;
		
	assert(NULL != compare);	
	
	pq = (pq_t*)malloc(sizeof(pq_t));
	if(NULL == pq)
	{
		return NULL;
	}
	
	pq->heap = HeapCreate(compare);
	if(NULL == pq->heap)
	{
		free(pq);
		return NULL;
	}
			
	return pq;					
}	


/**************************PQDestroy**************************************/	
void PQDestroy(pq_t* pq)
{	
	assert(pq);
	
	HeapDestroy(pq->heap);
	memset(pq, 0, sizeof(pq_t));
	free(pq);
}		
		

/***************************PQEnqueue*************************************/	
int PQEnqueue(pq_t* pq, void* data)
{
	assert(pq);
	
	return HeapPush(pq->heap, data);
}	


/**************************PQDequeue**************************************/
void* PQDequeue(pq_t* pq)
{
	assert(pq);
	
	return HeapPop(pq->heap);
}


/***************************PQPeek***************************************/
void* PQPeek(const pq_t* pq)
{
	assert(pq);
	
	return HeapPeek(pq->heap);
}


/***************************PQSize***************************************/
size_t PQSize(const pq_t* pq)
{
	assert(pq);
	
	return HeapSize(pq->heap);	
}


/**************************PQIsEmpty***********************************/
int PQIsEmpty(const pq_t* pq)
{
	assert(pq);
	
	return HeapIsEmpty(pq->heap);
}


/***************************PQClear***************************************/
pq_t* PQClear(pq_t* pq)
{
	assert(pq);
	
	while(!HeapIsEmpty(pq->heap)) 
	{
		PQDequeue(pq);
	}
	
	return pq;
}		


/**************************PQRemoveBy*************************************/
void* PQRemoveBy(pq_t* pq, pq_match_t match_func, void* params)
{	
	assert(pq);
	assert(match_func);
	assert(params);
	
	return HeapRemoveBy(pq->heap, match_func, params);			
}


