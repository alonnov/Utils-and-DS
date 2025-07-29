/* *****************************
 Name:     Alon Nov
 Exercise: stack
 Reviewer: Mor Weisberg
 Date:     14.10.2024
 
********************************/

#include <stdlib.h> /* size_t, malloc, free */
#include <string.h> /* memcpy */

#include "stack.h"	/* API */

struct stack
{
	void* data;
	int top;
	size_t elems;
	size_t esize;
};

stack_t* StackCreate(size_t total_elements, size_t element_size)
{
	stack_t* stack = malloc(sizeof(stack_t) + total_elements * element_size);	
	stack->top = -1;
	stack->elems = total_elements;
	stack->esize = element_size;	
	stack->data = (char*)stack + sizeof(stack_t);
	
	return stack;					
}	

void StackDestroy(stack_t* stack)
{
	free(stack);
	stack = NULL;
}


void StackPop(stack_t* stack) 
{
	--stack->top;		
}


void* StackPeek(const stack_t* stack) 
{		
	return (char*)stack->data + (stack->top * stack->esize);
}	

		
void StackPush(stack_t* stack, const void* element) 
{
	++stack->top;
	memcpy(StackPeek(stack), element, stack->esize);
}	


size_t StackSize(const stack_t* stack) 
{		
	return stack->top + 1;
}	


size_t StackCapacity(const stack_t* stack)
{
	return stack->elems;
} 
	

int IsStackEmpty(const stack_t* stack)
{
	return -1 == stack->top;
}		
