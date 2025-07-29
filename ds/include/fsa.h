/********************************
 Name:     Alon Nov
 Exercise: fixed size allocator 
 Date:	   14.11.2024   
 Reviewer: Mor Weisberg

********************************/

#ifndef _FSA_H_ 
#define _FSA_H_

#include <stddef.h> /* size_t */

typedef struct MemoryBlock fsa_t;
	
	
/*@Desc - initializes a fixed size allocator
* @Params - allocated_space: pointer to allocator's memory pool
* @Params - block_size: size of memory blocks to devide allocator 
			memory pool into
* @Params - number_of_blocks: number of memory blocks to be in the allocator's
		    memory pool
* @Return - pointer to the created allocator's memory pool
* @Return - NULL, if creation fails
* @Warnings - can cause UB if allocated_space param is not a pointer to a 
			  valid memory location
* @Warnings - block_size must be at least "word size" 
* @Warnings - block_size & number_of_blocks must be the same as in 
			  function SizeNeeded 
* @Warnings - allocated_space must point to an aligned memory location  
* @time complexity - O(n)  
* @Space complexity - O(1) */
fsa_t* FSAInit(void* allocated_space, size_t block_size, 
			   size_t number_of_blocks);


/*@Desc - calculates the size of the memory pool needed for the allocator
* @Params - block_size: size of memory blocks given allocator to manage
* @Params - number_of_blocks: number of memory blocks for given 
			allocator to manage
* @Return - amount of memory needed for the allocator
* @Warning - block_size must be at least "word size"
* @Warnings - block_size & total_blocks must be the same as in function FSAInit 
* @time complexity - O(n)  
* @Space complexity - O(1) */
size_t SizeNeeded(size_t block_size, size_t total_blocks);


/*@Desc - allocates a block of memory from given allocator's memory pool
* @Params - fsa: pointer to the allocator's memory pool
* @Return - pointer to allocated memory block
* @Return - NULL on failure
* @Warning - can cause UB if fsa param is not a pointer to a 
			 valid allocator memory pool
* @Warning - can cause UB if no free blocks are available		 
* @time complexity - O(1)   
* @Space complexity - O(1) */
void* FSAAlloc(fsa_t* fsa);
                             
                             
/*@Desc - deallocates a block of memory and returns it to the given allocator's 
		  memory pool
* @Params - fsa: pointer to the allocator's memory pool 
* @Params - block: pointer to the block to deallocate
* @Return - N/A
* @Warning - block param must be a pointer to a memory block previously 
			 allocated by "fsa"
* @time complexity - O(1)  
* @Space complexity - O(1) */
void FSADeAlloc(fsa_t* fsa, void* block);


/*@desc - counts the number of free blocks in the memory pool
* @param - fsa: pointer to the allocator's memory pool 
* @return - number of free blocks in the memory pool
* @Warning - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
size_t FSACountFreeBlocks(fsa_t* fsa);
	
	
#endif
