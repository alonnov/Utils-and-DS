/********************************
 Name:     Alon Nov
 Exercise: fixed size allocator 
 Date:	   14.11.2024   
 Reviewer: Mor Weisberg

********************************/

#include <assert.h>  /* assert */

#include "fsa.h"	/* API */

#define END 0
#define FSA_SIZE sizeof(fsa_t)
#define UNDER_WORD (sizeof(void*) - 1)


struct MemoryBlock 
{
    size_t next_free;
};	


/******************************AlignedSize************************************/
static size_t AlignedSize(size_t block_size)
{
	return (block_size + UNDER_WORD) & ~UNDER_WORD;
}	
	
	
/**************************SizeNeeded***************************************/	
size_t SizeNeeded(size_t block_size, size_t total_blocks)
{	
	return AlignedSize(block_size) * total_blocks + FSA_SIZE;
}
		

/******************************FSAInit****************************************/
fsa_t* FSAInit(void* allocated_space, size_t block_size, 
			   size_t number_of_blocks)
{
	fsa_t* initer = NULL;
	size_t i = 1;
	
	assert(allocated_space);
	assert(block_size >= UNDER_WORD + 1);
	assert(number_of_blocks);
	
	initer = (fsa_t*)allocated_space;
	block_size = AlignedSize(block_size);
	
	initer->next_free = FSA_SIZE;
	initer = (char*)initer + FSA_SIZE;
	
	for(; i < number_of_blocks; 
		initer = (fsa_t*)((char*)initer + block_size), ++i)
	{			
		initer->next_free = FSA_SIZE + block_size * i;
	}
	initer->next_free = END;
	
	return (fsa_t*)allocated_space;					
}


/***************************FSAAlloc****************************************/	
void* FSAAlloc(fsa_t* fsa)
{	
	void* block = NULL;
	
	assert(fsa);	
	
	if(END == fsa->next_free)
	{
		return NULL;
	}
		
	block = (char*)fsa + fsa->next_free; 	
	fsa->next_free = ((fsa_t*)block)->next_free;
	
	return block; 
}	


/************************FSADeAlloc*******************************************/
void FSADeAlloc(fsa_t* fsa, void* block)
{
	assert(fsa);	
	assert(block);
	
	((fsa_t*)block)->next_free = fsa->next_free;
	fsa->next_free = (size_t)((char*)block - (char*)fsa);	
}


/********************FSACountFreeBlocks***************************************/
size_t FSACountFreeBlocks(fsa_t* fsa)
{
	size_t counter = 0;
	fsa_t* runner = NULL;
	
	assert(fsa);
	 	
	for(runner = fsa; runner->next_free; 
		runner = (fsa_t*)((char*)fsa + runner->next_free), ++counter);
				
	return counter;	
}	
	
	
