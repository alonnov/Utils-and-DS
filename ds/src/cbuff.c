/* *****************************
 Name:     Alon Nov
 Exercise: circular buffer
 Date:     23.10.2024
 Reviewer: Alex Katznelson
 
********************************/

#include <stdlib.h>  /* size_t, ssize_t, malloc, free */
#include <string.h> /* memcpy */
#include <assert.h>  /* assert */

#include "cbuff.h" /* API */

struct cbuff
{
	size_t front;
	size_t rear;	
	size_t capacity;
	char data[1];
};		


/***************************CBCreate***************************************/
cbuff_t* CBCreate(size_t capacity)
{
	cbuff_t* cbuff = malloc(sizeof(cbuff_t) + capacity);
	if(NULL == cbuff)
	{
		return NULL;
	}
		
	cbuff->front = 0;
	cbuff->rear = 0;
	cbuff->capacity = capacity + 1;
			
	return cbuff;					
}	

/***************************CBDestory**************************************/	
void CBDestroy(cbuff_t* cbuff)
{	
	assert(NULL != cbuff);
	free(cbuff);
}		

/***************************CBWrite***************************************/
ssize_t CBWrite(cbuff_t* cbuff, const char* src, size_t bytes)
{
	size_t space = CBFreeSpace(cbuff);
	size_t to_end = CBCapacity(cbuff) - cbuff->rear;
	
	assert(NULL != cbuff);
	assert(NULL != src);
	
	if(0 == bytes) 
	{
		return 0;
	}
	
	if(space < bytes) 
	{
		bytes = space;
	}
	
	if(bytes > to_end)
	{
		memcpy((cbuff->data + cbuff->rear), src, to_end); 
		memcpy(cbuff->data, (src + to_end), (bytes - to_end));	 
	}
			
	else
	{			
		memcpy((cbuff->data + cbuff->rear), src, bytes);
	}
	
	cbuff->rear = (cbuff->rear + bytes) % cbuff->capacity;
			
	return bytes;
}	


/***************************CBRead***************************************/
ssize_t CBRead(cbuff_t* cbuff, char* dest, size_t bytes)
{		
	size_t space = CBSize(cbuff);
	size_t to_end = CBCapacity(cbuff) - cbuff->front;
	
	assert(NULL != cbuff);
	assert(NULL != dest);
	
	if(0 == bytes) 
	{
		return 0;
	}
	
	if(space < bytes) 
	{
		bytes = space;
	}
	
	if(bytes > to_end)
	{
		memcpy(dest, (cbuff->data + cbuff->front), to_end);	
		memcpy(dest + to_end, cbuff->data, (bytes - to_end));	
	}		
	else
	{			
		memcpy(dest, (cbuff->data + cbuff->front), bytes);
	}
	
	cbuff->front = (cbuff->front + bytes) % cbuff->capacity;
			
	return bytes;
}

/***************************CBIsEmpty****************************************/
int CBIsEmpty(const cbuff_t* cbuff)
{	
	assert(NULL != cbuff);
	
	return cbuff->front == cbuff->rear;
}	

/******************************CBSize****************************************/
size_t CBSize(const cbuff_t* cbuff)
{
	assert(NULL != cbuff);
	
	return (cbuff->capacity + cbuff->rear - cbuff->front) % cbuff->capacity;	
}

/***************************CBFreeSpace**************************************/
size_t CBFreeSpace(const cbuff_t* cbuff)
{	
	assert(NULL != cbuff);
	
	return CBCapacity(cbuff) - CBSize(cbuff);
}

/***************************CBCapacity***************************************/
size_t CBCapacity(const cbuff_t* cbuff)
{
	assert(NULL != cbuff);
	
	return cbuff->capacity - 1;
}	


