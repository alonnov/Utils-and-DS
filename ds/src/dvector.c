/* *****************************
 Name:     Alon Nov
 Exercise: dvector
 Reviewer: Mor Weisberg
 Date:     20.10.2024
 
********************************/

#include <stdlib.h>  /* size_t, malloc, realloc, free */
#include <string.h>  /* memcpy */
#include <assert.h>  /* assert */
#include <stdio.h>
#include "dvector.h" /* API */

struct dvector
{
	void* data;
	int last;
	size_t cap;
	size_t esize;
}vector;

static int g_rate = 2;

dvector_t* DvectorCreate(size_t capacity, size_t elem_size)
{
	dvector_t* vector = malloc(sizeof(dvector_t));
	if(NULL == vector)
	{
		return NULL;
	}
	vector->last = -1;
	vector->cap = capacity;
	vector->esize = elem_size;	
	vector->data = malloc(capacity * elem_size);
		
	if(NULL == vector->data)
	{
		return NULL;
	}
		
	return vector;					
}	


int DvectorPushBack(dvector_t* vector, const void* element)
{
	assert(NULL != vector);
	if(vector->cap == DvectorSize(vector))
	{
		vector->cap *= g_rate;
		vector->data = realloc(vector->data, vector->cap * vector->esize);
		if(NULL == vector->data)
		{
			return -1;
		}
	}
	++vector->last;
	memcpy(DvectorGetAccess(vector, vector->last), element, vector->esize);
	
	return 0;	
}


void DvectorPopBack(dvector_t* vector) 
{
	assert(NULL != vector);
	
	if(DvectorIsEmpty(vector))
	{
		return;
	}
	--vector->last;		
}


void* DvectorGetAccess(dvector_t* vector, size_t index)
{
	assert(NULL != vector);
		
	return (char*)vector->data + (index * vector->esize);
}


size_t DvectorSize(const dvector_t* vector) 
{
	assert(NULL != vector);
			
	return (size_t)(vector->last + 1);
}	


size_t DvectorCapacity(const dvector_t* vector)
{
	assert(NULL != vector);
	
	return vector->cap;
} 
	

int DvectorIsEmpty(const dvector_t* vector)
{
	assert(NULL != vector);
	
	return -1 == vector->last;
}		


int DvectorShrink(dvector_t* vector)
{
	assert(NULL != vector);
	if((DvectorSize(vector) * g_rate) > vector->cap)
		{
			return 0;
		}
	vector->data = 
	realloc(vector->data, (DvectorSize(vector) * g_rate) * vector->esize);
	if(NULL == vector->data)
		{
			return -1;
		}
	vector->cap = DvectorSize(vector) * g_rate;	
	return 0;	
}	 

	
int DvectorReserve(dvector_t* vector, size_t updated_capacity)
{
	assert(NULL != vector);
	assert(vector->cap < updated_capacity);
	
	vector->data = realloc(vector->data, updated_capacity * vector->esize);
	if(NULL == vector->data)
		{
			return -1;
		}
	vector->cap = updated_capacity;
	
	return 0;	
}	

	
void DvectorDestroy(dvector_t* vector)
{
	assert(NULL != vector);

	free(vector->data);	
	vector->data = NULL;
	free(vector);
	vector = NULL;
}

