/* *****************************
 Name:     Alon Nov
 Exercise: binary search tree
 Date:	   26.11.2024   
 Reviewer: Mor Weisberg

********************************/
					
#ifndef _BST_H_ 
#define _BST_H_

#include <stddef.h> /* size_t */

typedef struct bst bst_t;
typedef struct node* bst_iter_t;


/*@Desc - compares between 2 given data
* @Params - data1: iterator position's data
* @Params - data2: data to compare with
* @Return - number > 0 if data1 is larger than data2
* @Return - number < 0 if data1 is smaller than data2
* @Return - 0 if iterator_data and params are equal */
typedef int (*bst_compare_t)(const void* data1, const void* data2);


/*@Desc - performs an action
* @Params - data: list element's data pointed to by iterator
* @Params - params: paramater to perform action with
* @Return - 0 on success
* @Return - non 0 value on fail */
typedef int (*bst_action_t)(const void* data, const void* params);


/*@Desc - creates a binary search tree
* @Params - compare: sorting function tree will adhere to
* @Return - pointer to the created binary search tree
* @Return - NULL, if creation fails
* @Warnings - N/A
* @time complexity - O(1)  
* @Space complexity - O(1) */
bst_t* BSTCreate(bst_compare_t compare);


/*@Desc - frees all elements in the tree and the tree itself
* @Params - tree: tree to destroy
* @Return - N/A
* @Warning - if list param is not a pointer to a valid binary search tree, 
			  can cause UB
* @time complexity - O(n)  
* @Space complexity - O(1) */
void BSTDestroy(bst_t* tree);


/*@Desc - inserts an element into a given binary search tree in its 
		  appropriate position
* @Params - tree: list to insert element into 
* @Params - data: data to assign to inserted element
* @Return - iterator position of the inserted element 
* @Return - on fail, iterator position of BSTEnd(tree)
* @Warning - if list param is not a pointer to a binary search tree,
			  can cause UB
* @Warning - if data param is a NULL pointer, can cause UB
* @Warning - cannot insert the same data that already exists in the tree
* @time complexity - O(h) where h is the current height of the tree    
* @Space complexity - O(1) */
bst_iter_t BSTInsert(bst_t* tree, void* data);


/*@Desc - removes the tree element at given iterator position
* @Params - pos: iterator position's element to remove
* @Return - N/A
* @Warnings - if pos param == BSTEnd(tree), result will have UB 
* @Warnings - removing an element will cause iterator invalidation
			  for iterators at it's position
* @time complexity - O(n)  
* @Space complexity - O(1) */
void* BSTRemove(bst_iter_t pos);


/*@Desc - within a given binary search tree, searches for element with data
 		  that matches given data  
* @Params - tree: tree to search in
* @Params - data: data to match
* @Return - iterator position of element that matches the data, on success
* @Return - iterator position of last element in given tree, on failure
* @Warnings - N/A
* @time complexity - O(h) where h is the current height of the tree 
* @Space complexity - O(1) */
bst_iter_t BSTFind(const bst_t* tree, void* data);


/*@Desc - gets given iterator position's element's data
* @Params - pos: iterator position to get element data of
* @Return - pointer to data of given iterator position
* @Warning - if pos param == BSTEnd(tree), result will have UB 
* @time complexity - O(1) 
* @Space complexity - O(1) */
void* BSTGetData(bst_iter_t pos);


/*@Desc - tests if a given tree is empty (contains no elements)
* @Params - tree: tree to test for emptiness
* @Return - 1 (TRUE) if empty
* @Return - 0 (FALSE) if not empty
* @time complexity - O(1) 
* @Space complexity - O(1) */
int BSTIsEmpty(const bst_t* tree);


/*@Desc - gets the iterator position of the first element in a given
		  binary search tree
* @Params - tree: tree to get iterator position of first element
* @Return - iterator position of first element in the tree 
* @Warning - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
bst_iter_t BSTBegin(const bst_t* tree);


/*@Desc - gets the iterator position of the last element in a given 
		  binary search tree 
* @Params - tree: tree to get iterator position of last element
* @Return - iterator position of last element in the tree (invalid) 
* @Warning - N/A
* @time complexity - O(1) 
* @Space complexity - O(1) */
bst_iter_t BSTEnd(const bst_t* tree);


/*@Desc - gets the tree element in the next iterator position
* @Params - pos: iterator position from which to move iterator to the next one
* @Return - next iterator position in the tree
* @Warning - if pos param == BSTEnd(tree), result will have UB 
* @time complexity - O(n) 
* @Space complexity - O(1) */
bst_iter_t BSTNext(bst_iter_t pos);


/*@Desc - gets the previous iterator position before the given one
* @Params - pos: iterator position from which to move iterator to the previous one
* @Return - previous iterator position in the list
* @Warning - if pos param == BSTBegin(tree), result will have UB 
* @time complexity - O(n) 
* @Space complexity - O(1) */
bst_iter_t BSTPrev(bst_iter_t pos);


/*@desc - counts the number of elements in a given binary search tree
* @param - tree: tree to get number of elements in
* @return - number of elements in given tree
* @Warning - N/A
* @time complexity - O(n) 
* @Space complexity - O(1) */
size_t BSTSize(const bst_t* tree);


/*@Desc - tests if two given iterator position's elements are equal
* @Params - iter1: first iterator position
* @Params - iter2: second iterator position
* @Return - 1 (TRUE) if equal
* @Return - 0 (FALSE) if not equal
* @time complexity - O(1) 
* @Space complexity - O(1) */
int BSTIsIterEqual(bst_iter_t iter1, bst_iter_t iter2);


/*@Desc - performs a given action on every iterator position's element
 		  in a given range
* @Params - start: first iterator position in range to perform action on
* @Params - end: last iterator position in range to perform action on
* @Params - params: iterator position's data to perform action on
* @Params - action_func: function to perform action with
* @Return - return 0 for success or non 0 value for fail, if action_func can fail 
* @Return - return 0, if action_func can't fail     
* @Warning - if the function_func fails in any iteratrion, 
			 stops the program and returns non-zero value
* @time complexity - O(n) 
* @Space complexity - O(1) */
int BSTForEach(bst_iter_t start, bst_iter_t end, 
			   bst_action_t action_func, void* params);

#endif
