/********************************
 Name:     Alon Nov
 Exercise: variable size allocator 
 Date:	   17.11.2024   
 Reviewer: Shani Davidian

********************************/

#include <limits.h> /* LONG_MAX */
#include <assert.h> /* assert */

#include "vsa.h"	/* API */

#define END -0X1C960606C4C089
#define FLAG 0X5BC1DA3990BBB1
#define HEADER_SIZE sizeof(vsa_t)
#define UNDER_WORD (sizeof(void*) - 1)
#define ABS(x) (((x) > 0) ? (x) : -(x))

struct block_header 
{
    long block_size;
#ifndef NDEBUG
	size_t flag;
#endif	
};	


/******************************NextBlock**************************************/
static vsa_t* NextBlock(vsa_t* block)
{
    assert(block);
        
    return (vsa_t*)((char*)block + HEADER_SIZE + ABS(block->block_size));
}	


/******************************Defrag*****************************************/
static void Defrag(vsa_t* block, size_t size)
{
	vsa_t* next = NULL;
	
	assert(block);
		
	for(next = NextBlock(block); 
		block->block_size < (long)size && 0 <= next->block_size;
		next = NextBlock(next))		   
	{
   		block->block_size += HEADER_SIZE + next->block_size; 	
	}
}				
	

/******************************VSAInit****************************************/
vsa_t* VSAInit(void* allocated_space, size_t total_size)
{
	vsa_t* initer = NULL;
	
	assert(allocated_space);
	assert(total_size >= sizeof(HEADER_SIZE) * 2 + 1);
	
	if(0 == total_size)
	{
		return NULL;
	}
		
	total_size = total_size & ~UNDER_WORD;
	initer = (vsa_t*)allocated_space;		
	initer->block_size = total_size - 2 * HEADER_SIZE;		
#ifndef NDEBUG
	initer->flag = FLAG;
#endif
	initer = NextBlock(initer);
	initer->block_size = END;	

	return (vsa_t*)allocated_space;					
}


/***************************VSAAlloc****************************************/	
void* VSAAlloc(vsa_t* vsa, size_t requested_size)
{
	vsa_t* block = NULL;
	
	assert(vsa);	
	assert(requested_size < LONG_MAX);
	
	if(0 == requested_size)
	{
		return NULL;
	}
	
	requested_size = (requested_size + UNDER_WORD) & ~UNDER_WORD;
	
	block = vsa;		
	while(1)
	{		
		while(0 > block->block_size)
		{
			if(END == block->block_size)
			{
				return NULL;
			}
			block = NextBlock(block);
		}
		
		if((block->block_size) == (long)requested_size)
		{
			block->block_size *= -1;		
			break;
		}
				
		if((block->block_size) >= (long)(requested_size + HEADER_SIZE))	
		{
 			block->block_size -= (requested_size + HEADER_SIZE);
			block = NextBlock(block);
			block->block_size = -requested_size;										
		#ifndef NDEBUG
			block->flag = FLAG;
		#endif
			break;
 		} 		
 		
 		Defrag(block, requested_size);	
 		
 		if(block->block_size < (long)requested_size)
		{
			block = NextBlock(block);
		}				
	}
	
	return (char*)block + HEADER_SIZE;
} 		
	

/************************VSADeAlloc*******************************************/
void VSADeAlloc(void* block)
{	
	vsa_t* header = (vsa_t*)((char*)block - HEADER_SIZE);
	
	assert(block);
	
#ifndef NDEBUG
	assert(FLAG == header->flag);
	header->flag = 0;
#endif		
	header->block_size *= -1;
}


/********************LargestBlockAvailable************************************/
size_t LargestBlockAvailable(vsa_t* vsa)
{	
	long max_size = 0;
	
	assert(vsa);
 
	for(;END != vsa->block_size ; vsa = NextBlock(vsa))
	{
		Defrag(vsa, LONG_MAX);	
				
		if(vsa->block_size > max_size)
		{
			max_size = vsa->block_size;
		}	
	}
				
	return (size_t)max_size;	
}	
	
	
