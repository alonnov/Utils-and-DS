/* *****************************
 Name:     Alon Nov
 Exercise: stack
 Reviewer: Mor Weisberg
 Date:     14.10.2024
 
********************************/

#ifndef _STACK_H_ 
#define _STACK_H_

#include <stdlib.h> /* size_t */

typedef struct stack stack_t;

/*creates a stack with the capacity of total_elements element_size and returns
	a pointer to the created stack. */
/* total_elements = max number of elements in stack.
	element_size = size of element in bytes */
/* "stack" must be pointer to valid stack */	
stack_t* StackCreate(size_t total_elements, size_t element_size); 

/* frees the memory allocated for "stack" */
/* "stack" must be pointer to valid stack */
void StackDestroy(stack_t* stack);

/* removes last(top) element of "stack" */
/* "stack" must be pointer to valid stack */
/* can fail if "stack" is empty */
void StackPop(stack_t* stack); 

/* Returns a pointer to the last(top) element of "stack" 
	without removing it from "stack". 
	returns NULL if "stack" is empty */
/* "stack" must be pointer to valid stack */
void* StackPeek(const stack_t* stack); 

/* copies "element" to end of "stack" */
/* "stack" must be pointer to valid stack */
/* can fail if "stack" is full */
void StackPush(stack_t* stack, const void* element); 

/* returns current number of elements in "stack" */
/* "stack" must be pointer to valid stack */
size_t StackSize(const stack_t* stack); 

/* function for checking whether the stack is empty(has no elements) */
/* returns non-zero value if stack is not empty */
/* "stack" must be pointer to valid stack */
int IsStackEmpty(const stack_t* stack); 

/* returns number of elements "stack" can hold of size "element_size" */
/* "stack" must be pointer to valid stack */
size_t StackCapacity(const stack_t* stack);

#endif
