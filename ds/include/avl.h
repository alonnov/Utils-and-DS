/* *****************************
 Name:     Alon Nov
 Exercise: AVL
 Date:	   10.12.2024   
 Reviewer: Yonathan Levy

********************************/
					
#ifndef _AVL_H_ 
#define _AVL_H_

#include <stddef.h> /* size_t */
#include <sys/types.h> /* ssize_t */

typedef enum avl_search_order_t
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER           
}avl_search_order;

typedef struct avl avl_t;

typedef int (*avl_action_t)(void* param1, void* param2);
typedef int (*avl_compare_t)(const void* data1, const void* data2);
typedef int (*avl_match_t)(const void* elem1, const void* elem2);


/*@Desc-  creates a new AVL and allocates memory to hold it. 
* @Params - compare - compare function to compare by the data in the AVL
* @Return - returns pointer to created AVL. upon faliure returns NULL.
* @Space complexity - O(1)
* @time complexity - O(1)*/
avl_t* AVLCreate(avl_compare_t compare);


/*@desc  - Destroys the tree
* @params - avl: a pointer to an avl structure
* @Space complexity - O(1)
* @time complexity - O(n log n) */
void AVLDestroy(avl_t* avl);


/*@Desc - within a given avl, search for the element with data that mache the given data;   .
* @Params - avl: the tree to search in
* @Params - to_find: the given data to find;
* @Return - the matches data it find on success, if it doesn't find it - return NULL;
* @Space complexity - O(1)
* @time complexity - O(logn) */
void* AVLFind(const avl_t* avl,const void* to_find);


/*@Desc - Inserts a given element into the right place according to a comparison parameter.
* @Params - avl: A pointer to an avl struct
* @Params - to_insert: A pointer to an element
* @Return - 1 or 0 whether it succeeded or not
* @Space complexity - O(1)
* @time complexity - O(logn) 
* @Warning - Insert multiple instaces with the same data is undefined behavior */
int AVLInsert(avl_t* avl, void* to_insert);


/*@desc  -   finds and removes the first element matching the data
*            to_remove
* @param -   avl: AVL pointer 
*            to_remove: the data to find and remove
* @returns - the data of the removed element
* @Space complexity - O(1)
* @time complexity - O(logn) 
* @Warning - Remove from an empty tree is undefined
*/
void* AVLRemove(avl_t* avl, void* to_remove);


/*@desc  - check whether the AVL is empty
* @param - avl: a pointer to an avl managibg structure
* @returns true if AVL is empty, false otherwise
* @Space complexity - O(1)
* @time complexity - O(1) */
int AVLIsEmpty(const avl_t* avl);


/*@desc  - Check the tree size
* @param - avl: a pointer to an avl structure
* @Space complexity - O(1)
* @time complexity - O(nlogn) */
size_t AVLSize(const avl_t* avl);


/*@Desc - preforms an action on every element in the tree.
* @T.C. - O(nlogn)
* @S.C. - O(1)
* @Params - avl: AVL pointer
* @Params -	action_func: action function
* @Params -	params: data for the action function
* @Params -	search_order: how the tree is ordered 
			(in-order, post-order, pre-order), default is in_order.
* @Return - 0, on success. 
* @Return - action function result (return value), on failure.
* @Warning - undefined behavior if the action function can corrupt the tree.*/
int AVLForEach(avl_t* avl, avl_action_t action, void* params, avl_search_order order);



/*@description returns the height of the tree
* @params avl - the avl to get the height of
* @returns the height of the avl
* @time complexity - O(logn)
* @Space complexity - O(1)*/
ssize_t AVLHeight(const avl_t* avl);


/*
* @desc   - finds multiple elements in list that fit match function parameters
* @params - avl - a pointer to an avl managing structure
* @params - match_func - a match function used to find and match elements
* @params - params - parameters for the match function
* @params - list - a dll into which pointers to the found elements will be inserted
* @return - the number of elements found. Returns -1 if DLLInsert fails.
* @Space complexity - O(m)
* @time complexity - O(log(n))
ssize_t AVLMultiFind(avl_t* avl, avl_match_t match_func, void* params, dll_t* list);*/


/*@Desc   - remove multiple elements in list that fit match function parameters
* @Params - avl - a pointer to an avl managing structure
* @Params - match_func - a match function used to find matched elements
* @Params - params - parameters for the match function
* @Return - the number of elements found, zero if no element found
* @Space complexity - O(1)
* @Time complexity - O(log(n))
* @Warning - the function permanently remove matched elements, if backup neeeded - use 
*@ AVLMultiFind before.*/
size_t AVLMultiRemove(avl_t* avl, avl_match_t match_func, void* params);
int PrintNode(void* root, void* unused);
void Print(void* root, void* unused);

#endif
