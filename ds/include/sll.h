/* *****************************
 Name:     Alon Nov
 Exercise: singly linked list
 Reviewer: Israela Zimro
 Date:     20.10.2024
 
********************************/

#ifndef _SLL_H_ 
#define _SLL_H_

#include <stddef.h> /* size_t */

typedef struct sll sll_t;
typedef struct node* sll_iter_t;

/*@Desc - matches between 2 data chunks
* @Params - iterator data
* @Params - user data
* @Return - return 1 if match, 0 if fail */
typedef int (*sll_match_t)(const void* iterator_data, const void* user_data);

/*@Desc - uses a function
* @Params - iterator data
* @Params - user data
* @Return - return 0 on success, non 0 value if fail*/
typedef int (*sll_action_t)(void* iterator_data, void* user_data);

/*@Desc - creates a singly linked list
* @Params - no params
* @Return - pointer to the created linked list
* @Warning - if create fail, the function will return NULL
* @Space complexity - O(1)
* @time complexity - O(1)  */
sll_t* SLLCreate(void);

/*@Desc - frees all iterators and the list
* @Params - the list 
* @Space complexity - O(1)
* @time complexity - O(n)  */
void SLLDestroy(sll_t* sll);

/*@Desc - adds an element to list before the given iterator position
* @Params - sll = the list
* @Params - sll_iter = where to insert iterator
* @Params - data = data
* @Return - return the inserted iterator position
* @Space complexity - O(1)
* @time complexity - O(1)  */
sll_iter_t SLLInsert(sll_t* sll, sll_iter_t sll_iter, void* data);

/*@Desc - removes the element at given iterator position
* @Params - sll_iter = iterator position to remove, if iterator = SLLEnd(sll) result will be undefined
* @Return - return the next iterator after the removed iterator
* @Space complexity - O(1)
* @time complexity - O(1)  */
sll_iter_t SLLRemove(sll_iter_t sll_iter);

/*@desc - gets the size of the list
 *@param - sll - the list to check
 *@returns number of elements in the list 
 * @Space complexity - O(1)
 *@time complexity - O(n) */
size_t SLLCount(const sll_t* sll);

/*@Desc - get the next iterator in the list
* @Params - iterator, if iterator = SLLEnd(sll) result will be undefined
* @Return - the next iterator in the list
* @Space complexity - O(1)
* @time complexity - O(1) */
sll_iter_t SLLNext(sll_iter_t sll_iter);

/*@Desc - gets the first iterator from the list
* @Params - the list
* @Return - the first iterator of the list, if the list is empty - return end iterator
* @Space complexity - O(1)
* @time complexity - O(1) */
sll_iter_t SLLBegin(const sll_t* sll);

/*@Desc - gets the last iterator position from the list
* @Params - the list
* @Return - the end iterator
* @Space complexity - O(1)
* @time complexity - O(1) */
sll_iter_t SLLEnd(const sll_t* sll);

/*@Desc - gets the data from the the given iterator position
* @Params - iterator, if iterator = SLLEnd(sll) result will be undefine
* @Return - the data at current iterator
* @Space complexity - O(1)
* @time complexity - O(1) */
void* SLLGetData(sll_iter_t sll_iter);

/*@Desc - sets the data at the given iterator position
* @Params - the iterator to set data, if iterator = SLLEnd(sll) result will be undefine
* @Params - the data
* @Warnings- sll_iter cannot be = SLLEnd(sll)
* @Space complexity - O(1)
* @time complexity - O(1) */
void SLLSetData(sll_iter_t sll_iter, void* data);

/*@Desc - finds the iterator position data that matches "data"
* @Params - start: start of the list to be searched
* @Params - end: end of the list to be searched
* @Params - data: the data to find
* @Params - match_func: return 1 if the function finds a match for "data", otherwise return 0
* @Return - the iterator that matches the data, if it doesn't find it - return last iterator
* @Space complexity - O(1)
* @time complexity - O(n) */
sll_iter_t SLLFind(sll_iter_t start, sll_iter_t end, const void* data, sll_match_t match_func);

/*@Desc - use the function on every iterator of the list
* @Params - start: start of the range in list to be searched
* @Params - end: end of the range in list to be searched
* @Params - action_func: the function to do on every iterator position
* @Params - data: data to perform action on
* @Return - if the action_func can fail, return 0 for success or non 0 value for fail. if the action can't fail, return 0
* @Warning - if the function fails in any iteratrion, stop the program and return the non-zero value
* @Space complexity - O(1)
* @time complexity - O(n) */
int SLLForEach(sll_iter_t start, sll_iter_t end, void* params, sll_action_t action_func);

/*@Desc - check if the iterators are equal
* @Params - first iterator
* @Params - second iterator
* @Return - return 1 (true) if equal, 0 (false) if not equal
* @Space complexity - O(1)
* @time complexity - O(1) */
int SLLIsIterEq(sll_iter_t first_iter,sll_iter_t second_iter);


/*
@Desc - Appends a given list to a 2nd given list
@T.C. - O(1)
@S.C. - O(1)
@Params - dest: list to append to 
@Params - src: list which will be appended
@Return - Pointer to dest(with src appended)
@Warning - If appending fails, the function will return NULL */
sll_t* SLLAppend(sll_t* dest, sll_t* src);   


  
#endif
