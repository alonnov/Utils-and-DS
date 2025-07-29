/* *****************************
 Name:     Alon Nov
 Exercise: dvector
 Reviewer: Mor Weisberg
 Date:     20.10.2024
 
********************************/

#ifndef _DVECTOR_H_ 
#define _DVECTOR_H_

#include <stddef.h> /* size_t */

typedef struct dvector dvector_t;


/*
	@description creating and initializing a vector 
	@param capacity - the starting capaticy of the vector
	@param elem_size - the size of the elements inside the vector
	@returns a pointer to the created dvector on success and NULL on failure
*/
dvector_t* DvectorCreate(size_t capacity, size_t elem_size);

/*
	@description adds an element to the end of the vector and  increases the vector if needed
	@param vector - the vector to add to
	@param element - a pointer to the element to add
	@returns on success return 0 on failure return -1
*/
int DvectorPushBack(dvector_t* vector, const void* element);

/*
	@description removing the last element of the vector
	@param vector - the vector to remove from; 
*/
void DvectorPopBack(dvector_t* vector);

/*
	@description getting the pointer to the element at index
	@param vector - the vector to access
	@param index - the index to access at
	@returns a pointer to the element at index
	@Warning index must be smaller than size
*/
void* DvectorGetAccess(dvector_t* vector, size_t index);

/* 
	@description getting the size of the vector
	@param vector - the dvector to check
	@returns amount of elements in the vector
*/
size_t DvectorSize(const dvector_t* vector);

/* 
	@description getting the capacity of the vector
	@param vector - the dvector to check
	@returns the capacity of the vector
*/
size_t DvectorCapacity(const dvector_t* vector);

/*
	@description checks if the dvector is empty
	@param vector - the dvector to check on 
	@returns 0 if not empty 1 if it is
*/
int DvectorIsEmpty(const dvector_t* vector);

/*
	@description shrink the dvector capacity to size * 2 elements
	@param vector - the dvector to shrink
	@returns on success: 0, on fail: -1
*/
int DvectorShrink(dvector_t* vector);

/*
	@description increasing the capacity of the vector to updated capacity
	@param vector - the vector to update
	@param updated_capacity - the new capacity
	@returns if the reserve worked 0 otherwise -1;
	@Warning updated_capacity must be bigger than the current capacity 
*/
int DvectorReserve(dvector_t* vector, size_t updated_capacity);

/*
	@description deallocates the dvector
	@param vector - the vector to deallocate
*/
void DvectorDestroy(dvector_t* vector);

  

#endif
