/********************************
 Name:     Alon Nov
 Exercise: variable size allocator 
 Date:	   17.11.2024   
 Reviewer: Shani Davidian

********************************/

#ifndef _VSA_H_ 
#define _VSA_H_

#include <stddef.h> /* size_t */

typedef struct block_header vsa_t;
	
	
/*@Desc - initializes a variable size allocator
* @Params - allocated_space: pointer to allocator's memory pool
* @Params - total_size: max size (in bytes) that can be given for the 
			allocator's memory pool
* @Return - pointer to the created allocator's memory pool
* @Return - NULL, if creation fails
* @Warnings - can cause UB if allocated_space param is not a pointer to a 
			  valid memory location 
* @Warnings - allocated_space param must point to an aligned memory location
* @Warnings - if total_size param is 0, returns NULL   
* @time complexity - O(1)  
* @Space complexity - O(1) */
vsa_t* VSAInit(void* allocated_space, size_t total_size);


/*@Desc - allocates a block of memory of a given size from given allocator's 
		  memory pool
* @Params - vsa: pointer to the allocator's memory pool
* @Params - requested_size: size of memory block to allocate 
* @Return - pointer to allocated memory block
* @Return - NULL on failure
* @Warning - can cause UB if vsa param is not a pointer to a 
			 valid allocator memory pool
* @Warning - if requested_size param is 0, returns NULL 
* @Warning - requested_size param cannot be larger than LONG_MAX		 		 
* @time complexity - O(n)   
* @Space complexity - O(1) */
void* VSAAlloc(vsa_t* vsa, size_t requested_size);  
           
                             
/*@Desc - deallocates a block of memory and returns it to the given allocator's 
		  memory pool
* @Params - block: pointer to the block of memory to deallocate
* @Return - N/A
* @Warning - block param must be a pointer to a memory block previously 
			 allocated	 
* @time complexity - O(1)  
* @Space complexity - O(1) */
void VSADeAlloc(void* block);


/*@desc - gets the size of the largest memory block available for allocation
* @param - vsa: pointer to the allocator's memory pool 
* @return - size of the largest memory block available for allocation
* @Warning - can cause UB if vsa param is not a pointer to a 
			 valid allocator memory poo
* @time complexity - O(n) 
* @Space complexity - O(1) */
size_t LargestBlockAvailable(vsa_t* vsa);
	
	
#endif
