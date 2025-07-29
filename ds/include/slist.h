/* *****************************
 Name:     Alon Nov
 Exercise: sorted list 
 Date:	   29.10.2024   
 Reviewer: Liad Tiblum

********************************/

#ifndef _SLIST_H_ 
#define _SLIST_H_

#include <stddef.h> /* size_t */

#include "dll.h"	/* dll_iter */

typedef struct slist slist_t;

typedef struct slist_iter
{
    dll_iter_t dll_iter;
#ifndef NDEBUG
    slist_t* list;
#endif
} slist_iter_t;
	
/*@Desc - compares between given user data and given iterator position's data 
* @Params - data1: iterator position's data
* @Params - data2: data to compare with
* @Return - number > 0 if data1 is larger than data2
* @Return - number < 0 if data1 is smaller than data2
* @Return - 0 if iterator_data and params are equal */
typedef int (*slist_compare_t)(const void* data1, const void* data2);


/*@Desc - searches for a match between given user data and 
		  element's data in a list 
* @Params - data1: iterator position's data
* @Params - data2: data to compare with
* @Return - 1(TRUE) if a match is found
* @Return - 0(FALSE) if no match is found */
typedef int (*slist_match_t)(const void* data1, const void* data2);


/*@Desc - performs an action
* @Params - data1: iterator position's element's data
* @Params - data2: data to perform action with
* @Return - 0 on success
* @Return - non 0 value on fail */
typedef int (*slist_action_t)(void* data1, void* data2);


/*@Desc - creates a sorted list
* @Params - sorting function list will adhere to
* @Return - pointer to the created sorted list
* @Return - NULL, if creation fails
* @Warnings - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
slist_t* SListCreate(slist_compare_t compare);


/*@Desc - frees all elements in a given sorted list and the list itself
* @Params - list to destroy
* @Return - N/A
* @Warning - if list param is not a pointer to a valid sorted list, 
			 can cause UB
* @time complexity - O(n)  
* @Space complexity - O(1) */
void SListDestroy(slist_t* list);


/*@Desc - inserts an element into a given sorted list in its 
		  appropriate position
* @Params - list: list to insert element into 
* @Params - data: data to assign to inserted element
* @Return - iterator position of the inserted element 
* @Return - on fail, iterator position of SListEnd(list)
* @Warning - if list param is not a pointer to a valid sorted list,
			  can cause UB
* @Warning - if data param is a NULL pointer, can cause UB
* @time complexity - O(n)   
* @Space complexity - O(1) */
slist_iter_t SListInsert(slist_t* list, void* data); 


/*@Desc - removes the list element at given iterator position
* @Params - to_remove: iterator position's element to remove
* @Return - the next iterator position after the removed one
* @Warnings - if to_remove param == SListEnd(list), result will have UB 
* @time complexity - O(1)  
* @Space complexity - O(1) */
slist_iter_t SListRemove(slist_iter_t to_remove);


/*@Desc - removes the element at the last iterator position of a given list
* @Params - list: list to remove element from end of 
* @Return - pointer to the removed element's data
* @Warning - if list param is not a pointer to a valid sorted list,
			  can cause UB 
* @time complexity - O(1)  
* @Space complexity - O(1) */
void* SListPopBack(slist_t* list); 


/*@Desc - removes the element at the first iterator position of a given list
* @Params - list: list to remove element from start of 
* @Return - pointer to the removed element's data 
* @Warning - if list param is not a pointer to a valid sorted list,
			  can cause UB 
* @time complexity - O(1)  
* @Space complexity - O(1) */
void* SListPopFront(slist_t* list); 


/*@Desc - gets the next iterator position after the given one
* @Params - curr: iterator position of which to get the next 
					  iterator position of
* @Return - next iterator position in given list
* @Warning - if curr param == SListEnd(list), result will have UB
* @time complexity - O(1) 
* @Space complexity - O(1) */
slist_iter_t SListNext(slist_iter_t curr);


/*@Desc - gets the previous iterator position before the given one
* @Params - curr: iterator position of which to get the 
					  previous iterator position of
* @Return - previous iterator position in the list
* @Warning - curr param cannot be == SListBegin(list)
* @time complexity - O(1) 
* @Space complexity - O(1) */
slist_iter_t SListPrev(slist_iter_t curr);


/*@Desc - gets the first iterator position of a given list
* @Params - list: list to get first iterator position of
* @Return - iterator position of first valid element in the list 
* @Warning - N/A
* @time complexity - O(1) 
* @Space complexity - O(1) */
slist_iter_t SListBegin(slist_t* list); 


/*@Desc - gets the last iterator position of a given list
* @Params - list: list to get last iterator position of
* @Return - iterator position of last element in the list (invalid) 
* @Warning - N/A
* @time complexity - O(1) 
* @Space complexity - O(1) */
slist_iter_t SListEnd(slist_t* list);


/*@Desc - tests if two given iterator position's elements are equal
* @Params - first_iter: first iterator position
* @Params - second_iter: second iterator position
* @Return - 1 (TRUE) if equal
* @Return - 0 (FALSE) if not equal
* @time complexity - O(1) 
* @Space complexity - O(1) */
int SListIsIterEqual(slist_iter_t first_iter, slist_iter_t second_iter);


/*@Desc - gets given iterator position's element's data
* @Params - iter: given iterator position of which to get element data of
* @Return - pointer to data of given iterator position's element
* @Warning - if iter param == SListEnd(list), result will have UB
* @time complexity - O(1) 
* @Space complexity - O(1) */
void* SListGetData(slist_iter_t iter);


/*@Desc - performs a given action on every iterator position's element
 		  in a given iterator range
* @Params - start: first iterator position in range to perform action on
* @Params - end: last iterator position in range to perform action on
* @Params - params: iterator position's element's data to perform action on
* @Params - action_func: function to perform action with
* @Return - if action_func can fail, return 0 for success or non 0 value
		    for fail
* @Return - if the action can't fail, return 0	    
* @Warning - if the function_func fails in any iteratrion, 
			 stops the program and returns non-zero value
* @Warning - changing data may ruin the ordering of the list			 
* @time complexity - O(n) 
* @Space complexity - O(1) */
int SListForEach(slist_iter_t start, slist_iter_t end, void* params,
                 slist_action_t action_func);
			   
			   
/*@Desc - searches for iterator position's data that matches 
		  given data in a given iterator range within a given sorted list 
		  according to the given lists compare function
* @Params - list: list to search within
* @Params - start: first iterator position in range to be searched
* @Params - end: last iterator position in range to be searched
* @Params - to_find: iterator position's data to match
* @Return - first iterator position of list element that matches the data
* @Return - iterator position of end of given range, 
			if no match is found in given range
* @Warning - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
slist_iter_t SListFind(slist_t* list, slist_iter_t start,
                       slist_iter_t end, void* to_find);
				   
				   
/*@Desc - searches for iterator position's data that matches 
		  given data in a given iterator range within a given sorted list 
		  according to the given match function
* @Params - list: list to search within
* @Params - start: first iterator position in range to be searched
* @Params - end: last iterator position in range to be searched
* @Params - to_find: iterator position's data to match
* @Return - first iterator position of list element that matches the data
* @Return - iterator position of end of given range, 
			if no match is found in given range
* @Warning - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
slist_iter_t SListFindIf(slist_iter_t start, slist_iter_t end,
                         void* to_find, slist_match_t match);
				 				 				   			   

/*@Desc - merge 2 given sorted lists into 1 sorted list
* @Params - dest: sorted list to move elements to
* @Params - src: sorted list to move elements from
* @Return - merged sorted list 
* @Warning - both lists must be sorted by the same criteria
* @time complexity - O(m + n)  
* @Space complexity - O(1) */
slist_t* SListMerge(slist_t* dest, slist_t* src);


/*@desc - counts the number of elements in a given sorted list
* @param - list: list to get number of elements in
* @return - number of elements in the list
* @Warning - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
size_t SListCount(const slist_t* list);


/*@Desc - tests if a given list is empty (contains no elements)
* @Params - list: list to test for emptiness
* @Return - 1 (TRUE) if empty
* @Return - 0 (FALSE) if not empty
* @time complexity - O(1) 
* @Space complexity - O(1) */
int SListIsEmpty(const slist_t* list); 
  

 
#endif
