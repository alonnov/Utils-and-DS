/* *****************************
 Name:     Alon Nov
 Exercise: queue
 Date:     22.10.2024
 Reviewer: Liran Mazor
 
********************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h>  /* size_t */

typedef struct queue queue_t;

/*
@Desc - Creates a Queue
@T.C. - O(1)
@S.C. - O(1)
@Params - No params
@Return - Pointer to the created Queue
@Warning - If creation fails, the function will return NULL */
queue_t* QCreate(void);

/*
@Desc - Frees all elements in a given Queue and the Queue itself
@T.C. - O(n)
@S.C. - O(1)
@Params - Queue to destroy
@Return - N/A
@Warning - N/A */
void QDestroy(queue_t* queue);

/*
@Desc - "Peeks" at the front element of a given Queue 
@T.C. - O(1)
@S.C. - O(1)
@Params - Queue to peek at the front of
@Return - Pointer to the data of front element in the given Queue
@Warning - If the given Queue is empty, the function will return NULL */
void* QPeek(const queue_t* queue);

/*
@Desc - Inserts an element at the back of a given Queue
@T.C. - O(1)
@S.C. - O(1)
@Params - queue: Queue to insert element into
@Params - data: data to assign to inserted element
@Return - 1 if insertion was successful, 0 if insertion failed
@Warning - If creation fails, the function will return NULL */
int QEnqueue(queue_t* queue, void* data);

/*
@Desc - Removes an element from the front of a given Queue
@T.C. - O(1)
@S.C. - O(1)
@Params - Queue from which to remove front element 
@Return - N/A
@Warning - N/A */
void QDequeue(queue_t* queue);

/*
@Desc - Calculates the number of elements in a given Queue
@T.C. - O(n)
@S.C. - O(1)
@Params - Queue to calculate the number of elements it contains
@Return - number of elements in given Queue
@Warning - N/A */
size_t QSize(const queue_t* queue);

/*
@Desc - Tests if a given Queue is empty(has no elements)
@T.C. - O(1)
@S.C. - O(1)
@Params - Queue to test emptiness of
@Return - 1 if given queue is empty(true), 0 if given queue is not empty(false)
@Warning - N/A */
int QIsEmpty(const queue_t* queue);

/*
@Desc - Appends a given Queue to a 2nd given Queue
@T.C. - O(1)
@S.C. - O(1)
@Params - dest: Queue to append to 
@Params - src: Queue which will be appended
@Return - Pointer to dest(with src appended)
@Warning - If appending fails, the function will return NULL */
queue_t* QAppend(queue_t* dest, queue_t* src);


#endif
