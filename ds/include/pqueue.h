/* *****************************
 Name:     Alon Nov
 Exercise: priority queue 
 Date:	   10.11.2024   
 Reviewer: Israela Zimro

********************************/

#ifndef _PQUEUE_H_ 
#define _PQUEUE_H_

#include <stddef.h> /* size_t */

typedef struct pqueue pqueue_t;
	
	
/*@Desc - compares between two given data 
* @Params - data1: first data to compare
* @Params - data2: second data to compare
* @Return - number > 0 if data1 is larger than data2
* @Return - number < 0 if data1 is smaller than data2
* @Return - 0 if iterator_data and params are equal */
typedef int (*pqueue_compare_t)(const void* data1, const void* data2);


/*@Desc - searches for a match between given user data 
		  and data in a priority queue 
* @Params - data1: iterator position's data
* @Params - data2: data to compare with
* @Return - 1(TRUE) if a match is found
* @Return - 0(FALSE) if no match is found */
typedef int (*pqueue_match_t)(const void* data1, const void* data2);


/*@Desc - creates a priority queue
* @Params - sorting function the created queue will adhere to
* @Return - pointer to the created priority queue
* @Return - NULL, if creation fails
* @Warnings - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
pqueue_t* PQueueCreate(pqueue_compare_t compare_func);


/*@Desc - frees all elements in a given priority queue and the queue itself
* @Params - priority queue to destroy
* @Return - N/A
* @Warning - if pqueue param is not a pointer to a valid priority queue, 
			 can cause UB
* @time complexity - O(n)  
* @Space complexity - O(1) */
void PQueueDestroy(pqueue_t* pqueue);


/*@Desc - inserts an element into a given priority queue adhering 
		  to the priority queue's compare function
* @Params - pqueue: priority queue to insert element into 
* @Params - data: data to assign to inserted element
* @Return - 0 on success
* @Return - non 0 value on fail
* @Warning - if pqueue param is not a pointer to a valid priority queue,
			  can cause UB
* @Warning - if data param is a NULL pointer, can cause UB
* @time complexity - O(n)   
* @Space complexity - O(1) */
int PQueueEnqueue(pqueue_t* pqueue, void* data);


/*@Desc - removes the element at the front of the given priority queue
* @Params - pqueue: priority queue to remove from
* @Return - data of the removed element
* @Warning - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
void* PQueueDequeue(pqueue_t* pqueue);


/*@Desc - gets the data of the element at the front of a given priority queue
* @Params - pqueue: priority queue to get first element of
* @Return - data of the element at the front of the queue
* @Warning - N/A
* @time complexity - O(1) 
* @Space complexity - O(1) */
void* PQueuePeek(const pqueue_t* pqueue);


/*@desc - gets the number of elements in a given priority queue
* @param - pqueue: priority queue to get number of elements in
* @return - number of elements in the given priority queue
* @Warning - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
size_t PQueueSize(const pqueue_t* pqueue);


/*@Desc - tests if a given priority queue is empty (contains no elements)
* @Params - pqueue: priority queue to test for emptiness
* @Return - 1 (TRUE) if empty
* @Return - 0 (FALSE) if not empty
* @time complexity - O(1) 
* @Space complexity - O(1) */
int PQueueIsEmpty(const pqueue_t* pqueue);


/*@Desc - removes all current elements from a given priority queue 
* @Params - pqueue: priority queue to remove elements of 
* @Return - the priority queue after element removal (empty)
* @Warning - if pqueue param is not a pointer to a valid priority queue,
			  can cause UB
* @Warning - N/A
* @time complexity - O(n)   
* @Space complexity - O(1) */
pqueue_t* PQueueClear(pqueue_t* pqueue);


/*@Desc - removes the first element from a given priority queue that it's data matches the given data
* @Params - pqueue: priority queue to remove element from
* @Params - match_func: function to test criteria with
* @Params - params: data to match with match_func
* @Return - data of the removed element
* @Return - NULL, if no matching element is found
* @Warning - if pqueue param is not a pointer to a valid priority queue,
			  can cause UB
* @Warning - N/A
* @time complexity - O(n)   
* @Space complexity - O(1) */
void* PQueueRemoveBy(pqueue_t* pqueue, pqueue_match_t match_func, void* params);

 
#endif
