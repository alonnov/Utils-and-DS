/* *****************************
 Name:     Alon Nov
 Exercise: heap
 Date:	   12.12.2024   
 Reviewer: Mor Weisberg

********************************/
					
#ifndef _HEAP_H_ 
#define _HEAP_H_

#include <stddef.h> /* size_t */

#include "dvector.h"

typedef struct heap heap_t;

/*@Desc - compares between 2 given data
* @Params - data1: element's data
* @Params - data2: data to compare with
* @Return - number > 0 if data1 is larger than data2
* @Return - number < 0 if data1 is smaller than data2
* @Return - 0 if iterator_data and params are equal */
typedef int (*heap_compare_t)(const void* data1, const void* data2);


/*@Desc - compares between 2 given data
* @Params - data1: element's data
* @Params - data2: data to compare with
* @Return - 1(TRUE) if data match
* @Return - 0(FALSE) if data don't match */
typedef int (*heap_match_t)(const void* data1, const void* data2);


/*@Desc - creates a heap data structure
* @Params - compare: sorting function heap will adhere to
* @Return - pointer to the created heap
* @Return - NULL, if creation fails
* @Warnings - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
heap_t* HeapCreate(heap_compare_t compare);


/*@Desc - frees the heap
* @Params - heap: heap to destroy
* @Return - N/A
* @Warning - if heap param is not a pointer to a valid binary search tree, 
			 can cause UB
* @time complexity - O(1)  
* @Space complexity - O(1) */
void HeapDestroy(heap_t* heap);


/*@Desc - pushes an element onto the top of a given heap
* @Params - heap: heap to push element onto 
* @Params - data: data to assign to pushed element
* @Return - 0(SUCCESS), on success
* @Return - 1(FAILURE), on failure
* @Warning - if heap param is not a pointer to a valid heap,
			  can cause UB
* @Warning - if data param is a NULL pointer, can cause UB
* @time complexity - O(n) 
* @Space complexity - O(1) */
int HeapPush(heap_t* heap, void* data);


/*@Desc - removes the top(last) element on the heap
* @Params - heap: heap to remove top element of
* @Return - pointer to removed element's data
* @Warnings - if heap is empty, result will have UB 
* @time complexity - O(n)  
* @Space complexity - O(1) */
void* HeapPop(heap_t* heap);


/*@Desc - gets the data of the top element in a given heap
* @Params - heap: heap to peek
* @Return - on success, pointer to top peeked element's data
* @Return - NULL, if heap is empty 
* @Warnings - after popping/pushing to the same heap, previous peeked pointers may be invalid
* @time complexity - O(1)
* @Space complexity - O(1) */
void* HeapPeek(heap_t* heap);


/*@Desc - removes the first element that matches given data from the heap
* @Params - heap: heap to remove element from
* @Params - match: match function to use to find element to remove
* @Params - params: match function parameter, if needed
* @Return - pointer to removed element's data
* @Warnings - if heap is empty, result will have UB 
* @time complexity - O(n)  
* @Space complexity - O(1) */
void* HeapRemoveBy(heap_t* heap, heap_match_t match, void* params);


/*@Desc - tests if a given heap is empty (contains no elements)
* @Params - heap: heap to test for emptiness
* @Return - 1 (TRUE) if empty
* @Return - 0 (FALSE) if not empty
* @Warning - N/A
* @time complexity - O(1) 
* @Space complexity - O(1) */
int HeapIsEmpty(const heap_t* heap);


/*@desc - gets the number of elements in a given heap
* @param - heap: heap to get number of elements in
* @return - number of elements in given heap
* @Warning - N/A
* @time complexity - O(1) 
* @Space complexity - O(1) */
size_t HeapSize(const heap_t* heap);


#endif
