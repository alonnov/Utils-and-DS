/* *****************************
 Name:     Alon Nov
 Exercise: heap
 Date:	   12.12.2024   
 Reviewer: Mor Weisberg

********************************/

#include <stdlib.h>  /* malloc, free */
#include <string.h>  /* memset */
#include <assert.h>  /* assert */

#include "heap.h" /* API */
#include "dvector.h" /* DvectorCreate, DvectorDestroy, DvectorPushBack, 
						DvectorPopBack, DvectorIsEmpty, DvectorSize */

#define ESIZE (sizeof(void*))
#define INIT_SIZE (32)

enum status
{
    SUCCESS,
    FAILURE         
};

enum test
{
    FALSE,
    TRUE          
};

struct heap
{
	dvector_t* vector;
	heap_compare_t compare;
};



/***************************GetAccess*****************************************/
static void* GetAccess(dvector_t* vector, int index)
{
	return *(void**)DvectorGetAccess(vector, index);	
}


/***************************Swap**********************************************/
static void Swap(heap_t* heap, size_t ind1, size_t ind2)
{
	void** temp = NULL;
	void** elem1 = NULL;
	void** elem2 = NULL;

	elem1 = (void**)DvectorGetAccess(heap->vector, ind1);
	elem2 = (void**)DvectorGetAccess(heap->vector, ind2);

	temp = *elem1;
	*elem1 = *elem2;
	*elem2 = temp;
}


/***************************HeapifyUp***************************************/
static void HeapifyUp(heap_t* heap, size_t ind)
{
	size_t parent_ind = (ind - 1) / 2;
	void* curr = NULL;
	void* parent = NULL;

	while(0 < ind)
	{
		curr = GetAccess(heap->vector, ind);
		parent = GetAccess(heap->vector, parent_ind);

		if(heap->compare(parent, curr) <= 0)
		{
			return;
		}

		Swap(heap, parent_ind, ind);
		ind = parent_ind;
		parent_ind = (ind - 1) / 2;
	}
}	


/***************************HeapifyDown***************************************/
static void HeapifyDown(heap_t* heap, size_t ind)
{
	size_t left_ind = (2 * ind) + 1;
	size_t right_ind = (2 * ind) + 2;
	size_t size = HeapSize(heap);
	size_t smaller = 0;
	void* curr = NULL;
	void* left = NULL;
	void* right = NULL;

	while(left_ind < size)
	{
		curr = GetAccess(heap->vector, ind);
		left = GetAccess(heap->vector, left_ind);

		if(right_ind < size)
		{
			right = GetAccess(heap->vector, right_ind);
		} 

		smaller = left_ind;

		if(right_ind < size && heap->compare(right, left) < 0)
		{
			smaller = right_ind;
		}

		if(heap->compare(curr, GetAccess(heap->vector, smaller)) <= 0)
		{
			return;
		}

		Swap(heap, ind, smaller);

		ind = smaller;
		left_ind = (2 * ind) + 1;
		right_ind = (2 * ind) + 2;	
	}
}	


/***************************HeapCreate***************************************/
heap_t* HeapCreate(heap_compare_t compare)
{
	heap_t* heap = NULL;

	assert(compare);
	
	heap = (heap_t*)malloc(sizeof(heap_t));
	if(NULL == heap)
	{
		return NULL;
	}
	
	heap->vector = DvectorCreate(INIT_SIZE, ESIZE); 
	if(NULL == heap->vector)
	{
		free(heap);
		return NULL;
	}

	heap->compare = compare;
	
	return heap;					
}	


/***************************HeapDestroy**************************************/	
void HeapDestroy(heap_t* heap)
{
	assert(heap);
	
	DvectorDestroy(heap->vector);
	memset(heap, 0, sizeof(heap_t));	
	free(heap);
}		


/***************************HeapPush***************************************/
int HeapPush(heap_t* heap, void* data)
{
	assert(heap);
	assert(data);

	if(0 != DvectorPushBack(heap->vector, &data))
	{
		return FAILURE;
	}
	
	HeapifyUp(heap, HeapSize(heap) - 1);

	return SUCCESS;
}	


/***************************HeapPop***************************************/
void* HeapPop(heap_t* heap)
{
	void* data = NULL;

	assert(heap);
	assert(FALSE == HeapIsEmpty(heap));

	data = HeapPeek(heap);
	Swap(heap, 0, HeapSize(heap) -1);
	DvectorPopBack(heap->vector);	
	HeapifyDown(heap, 0);
	
	return data;
}


/**************************HeapPeek*******************************************/
void* HeapPeek(heap_t* heap)
{
	assert(heap);
	assert(FALSE == HeapIsEmpty(heap));

	return GetAccess(heap->vector, 0);
}


/****************************HeapRemoveBy*************************************/
void* HeapRemoveBy(heap_t* heap, heap_match_t match, void* params)
{	
	void* runner = NULL;
	size_t i = 0;
	size_t size = 0;

	assert(heap);
	assert(match);

	for(runner = GetAccess(heap->vector, 0), size = HeapSize(heap);
	 i < size; ++i, runner = GetAccess(heap->vector, i))
	{				
		if(match(runner, params))
		{
			Swap(heap, i, size - 1);
			DvectorPopBack(heap->vector);		
			HeapifyDown(heap, i);	
			return runner;
		}	
	}
	
	return NULL;	
}			



/**************************HeapIsEmpty***********************************/
int HeapIsEmpty(const heap_t* heap)
{
	assert(heap);
		
	return DvectorIsEmpty(heap->vector);
}		


/***************************HeapSize***************************************/
size_t HeapSize(const heap_t* heap)
{
	assert(heap);

	return DvectorSize(heap->vector);
}	




