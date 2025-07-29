/* *****************************
 Name:     Alon Nov
 Exercise: doubly linked list 
 Date:	   27.10.2024   
 Reviewer: Yael Priz 

********************************/

#ifndef _DLL_H_ 
#define _DLL_H_

#include <stddef.h> /* size_t */

typedef struct dll dll_t;
typedef struct node* dll_iter_t;

/*@Desc - searches for a match between given user data and 
		  element's data in a list 
* @Params - iterator data: list element's data pointed to by iterator
* @Params - params: data to match
* @Return - 1(TRUE) if a match is found
* @Return - 0(FALSE) if no match is found */
typedef int (*dll_match_t)(const void* iterator_data, const void* params);

/*@Desc - performs an action
* @Params - iterator data: list element's data pointed to by iterator
* @Params - params: data to perform action with
* @Return - 0 on success
* @Return - non 0 value on fail */
typedef int (*dll_action_t)(void* iterator_data, void* params);


/*@Desc - creates a doubly linked list
* @Params - N/A
* @Return - pointer to the created linked list
* @Return - NULL, if creation fails
* @Warnings - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
dll_t* DLLCreate(void);


/*@Desc - frees all elements in the list and the list itself
* @Params - list to destroy
* @Return - N/A
* @Warning - if list param is not a pointer to a valid doubly linked list, 
			  can cause UB
* @time complexity - O(n)  
* @Space complexity - O(1) */
void DLLDestroy(dll_t* list);


/*@Desc - inserts an element into a given list before a given iterator position
* @Params - list: list to insert element into 
* @Params - iter: iterator position to insert element before 
* @Params - data: data to assign to inserted element
* @Return - iterator to the inserted element 
* @Return - on fail, iterator to DLLEnd(list)
* @Warning - if list param is not a pointer to a valid doubly linked list,
			  can cause UB
* @time complexity - O(1)   
* @Space complexity - O(1) */
dll_iter_t DLLInsert(dll_t* list, dll_iter_t iter, void* data);


/*@Desc - inserts an element at the end of a given list
* @Params - list: list to insert element at end of 
* @Params - data: data to assign to inserted element 
* @Return - iterator to the inserted element 
* @Return - on fail, iterator to DLLEnd(list)  
* @Warning - if list param is not a pointer to a valid doubly linked list,
			  can cause UB 
* @time complexity - O(1)  
* @Space complexity - O(1) */
dll_iter_t DLLPushBack(dll_t* list, void* data);


/*@Desc - inserts an element at the start of a given list
* @Params - list: list to insert element at start of 
* @Params - data: data to assign to inserted element 
* @Return - pointer to the inserted element 
* @Return - on fail, pointer to DLLEnd(list);
* @Warning - if list param is not a pointer to a valid doubly linked list, 
			  can cause UB 
* @time complexity - O(1)  
* @Space complexity - O(1) */
dll_iter_t DLLPushFront(dll_t* list, void* data);


/*@Desc - removes the list element at given iterator position
* @Params - to_remove: element to remove
* @Return - the next list element after the removed one
* @Warnings - if to_remove param == DLLEnd(dll), result will be UB 
* @time complexity - O(1)  
* @Space complexity - O(1) */
dll_iter_t DLLRemove(dll_iter_t to_remove);


/*@Desc - removes the last element from a given list
* @Params - list: list to remove element from end of 
* @Return - pointer to the removed element's data
* @Warning - if list param is not a pointer to a valid doubly linked list,
			  can cause UB 
* @time complexity - O(1)  
* @Space complexity - O(1) */
void* DLLPopBack(dll_t* list);


/*@Desc - removes the first element from of a given list
* @Params - list: list to remove element from start of 
* @Return - pointer to the removed element's data 
* @Warning - if list param is not a pointer to a valid doubly linked list,
			  can cause UB 
* @time complexity - O(1)  
* @Space complexity - O(1) */
void* DLLPopFront(dll_t* list);


/*@Desc - moves a given range of elements up to the last one (not including)
		  to before a given eterator in a 2nd list
* @Params - where: iterator position to insert before
* @Params - start: first iterator position of range to move
* @Params - end: iterator position to end range (not moved)
* @Return - iterator to first list element moved 
* @Warnings - start must not be == to first iterator (invalid)
* @time complexity - O(1)  
* @Space complexity - O(1) */
dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t start, dll_iter_t end);


/*@Desc - searches for iterator position's data that matches 
		  given data in a given iterator range within a given sorted list 
		  according to the given match function
* @Params - start: first iterator position in range to be searched
* @Params - end: last iterator position in range to be searched
* @Params - params: iterator position's data to find
* @Params - match_func: function to test match with
* @Return - iterator position of list element that matches the data
* @Return - iterator position of end param, if no match is found in given range
* @Warnings - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
dll_iter_t DLLFind(dll_iter_t start, dll_iter_t end, const void* params,
				   dll_match_t match_func);


/*@Desc - searches for any list element's data within a given range of 
		  itertor positions that matches a criteria related to given data 
		  and appends them to a given list
* @Params - list: list to add matching elements to	  
* @Params - start: first iterator position in range to be searched
* @Params - end: last iterator position in range to be searched
* @Params - params: iterator position's data to find
* @Params - match_func: function to test criteria with
* @Return - 0 on success
* @Return - non 0 value on fail
* @time complexity - O(n)  
* @Space complexity - O(1) */
int DLLFindMulti(dll_t* res_list, dll_iter_t start, dll_iter_t end, 
				 const void* params, dll_match_t match_func);


/*@Desc - performs a given action on every iterator positions element
 		  in a given range
* @Params - start: first iterator position in range to perform action on
* @Params - end: last iterator position in range to perform action on
* @Params - data: iterator position's data to perform action on
* @Params - action_func: function to perform action with
* @Return - if action_func can fail, return 0 for success or non 0 value
		    for fail
* @Return - if the action can't fail, return 0	    
* @Warning - if the function_func fails in any iteratrion, 
			 stops the program and returns non-zero value
* @time complexity - O(n) 
* @Space complexity - O(1) */
int DLLForEach(dll_iter_t start, dll_iter_t end, void* params, 
			   dll_action_t action_func);


/*@Desc - gets the next list element after the given one
* @Params - dll_iter: iterator position of which to get the next 
					  iterator position of
* @Return - next iterator position in the list
* @Warning - if dll_iter param == DLLEnd(dll), result will have UB
* @time complexity - O(1) 
* @Space complexity - O(1) */
dll_iter_t DLLNext(dll_iter_t dll_iter);


/*@Desc - gets the previous iterator position before the given one
* @Params - dll_iter: iterator position of which to get the 
					  previous iterator position of
* @Return - previous iterator position in the list
* @Warning - dll_iter param cannot be == DLLBegin(dll)
* @time complexity - O(1) 
* @Space complexity - O(1) */
dll_iter_t DLLPrev(dll_iter_t iter);


/*@Desc - sets the data of a given iterator position to the given data
* @Params - dll_iter: iterator position of which to set the data of
* @Params - data: data to set to iterator position
* @Return - N/A
* @Warning - if dll_iter param == DLLEnd(dll) or DLLBegin(dll), 
			 result will have UB
* @time complexity - O(1) 
* @Space complexity - O(1) */
void DLLSetData(dll_iter_t dll_iter, void* data);


/*@Desc - gets given iterator position's data
* @Params - dll_iter: given iterator position of which to get the data of
* @Return - pointer to data of given iterator position
* @Warning - if dll_iter param == DLLEnd(dll) result will have UB
* @time complexity - O(1) 
* @Space complexity - O(1) */
void* DLLGetData(dll_iter_t dll_iter);


/*@Desc - gets the first iterator position of a given list
* @Params - dll: list to get first iterator position of
* @Return - iterator position of first valid element in the list 
* @Warning - N/A
* @time complexity - O(1) 
* @Space complexity - O(1) */
dll_iter_t DLLBegin(const dll_t* dll);


/*@Desc - gets the last element of a given list
* @Params - dll: list to get last element of
* @Return - iterator position of last element in the list (not valid) 
* @Warning - N/A
* @time complexity - O(1) 
* @Space complexity - O(1) */
dll_iter_t DLLEnd(const dll_t* dll);


/*@desc - calculates the number of elements in a given list
* @param - dll: list to get number of elements in
* @return - number of elements in the list
* @Warning - N/A 
* @time complexity - O(n) 
* @Space complexity - O(1) */
size_t DLLCount(const dll_t* dll);


/*@Desc - tests if two given iterator position's elements are equal
* @Params - first_iter: first iterator position
* @Params - second_iter: second iterator position
* @Return - 1 (TRUE) if equal
* @Return - 0 (FALSE) if not equal
* @time complexity - O(1) 
* @Space complexity - O(1) */
int DLLIsIterEqual(dll_iter_t first_iter, dll_iter_t second_iter);


/*@Desc - tests if a given list is empty (contains no elements)
* @Params - list: list to test for emptiness
* @Return - 1 (TRUE) if empty
* @Return - 0 (FALSE) if not empty
* @time complexity - O(1) 
* @Space complexity - O(1) */
int DLLIsEmpty(const dll_t* list);   

 
#endif
