/* *****************************
 Name:     Alon Nov
 Exercise: circular buffer
 Date:     23.10.2024
 Reviewer: Alex Katznelson
 
********************************/

#ifndef __CBUFF_H__
#define __CBUFF_H__

#include <sys/types.h> /* ssize_t */
#include <stddef.h>    /* size_t */

typedef struct cbuff cbuff_t;

/*@Desc - creates a buffer with a given capacity
* @Params - capacity: buffer capacity in bytes (must be larger than 0)
* @Return - returns pointer to the created buffer 
* @Return - on fail returns NULL
* @Warning - capacity must be larger than 0 
* @time complexity - O(1)
* @space complexity - O(1)  */
cbuff_t* CBCreate(size_t capacity);

/*@Desc - frees buffer
* @Params - buff: buffer to free
* @Warnings - if cbuff param is not a pointer to a valid buffer,
			  can cause UB 
* @time complexity - O(1)
* @Space complexity - O(1)  */
void CBDestroy(cbuff_t* cbuff);

/*@Desc - reads a given number of bytes from a given source and writes
		  them to a given buffer
* @Params - buff: buffer to write data to
* @Params - src: source to read data from
* @Params - bytes: number of bytes to read/write
* @Return - returns number of read/written bytes
* @Return - on fail returns 0
* @Warnings - if cbuff param is not a pointer to a valid buffer,
			  can cause UB
* @Warning - UB if "bytes" is larger than "src" 
* @time complexity - O(n) 
* @Space complexity - O(1)  */
ssize_t CBWrite(cbuff_t* cbuff, const char* src, size_t bytes);

/*@Desc - reads a given number of bytes from a given buffer and writes 
		  them to a given destination
* @Params - buff: buffer to read data from
* @Params - dest: destination to write data to
* @Params - bytes: number of bytes to read/write
* @Return - returns number of read/written bytes
* @Return - on fail returns 0
* @Warnings - if cbuff param is not a pointer to a valid buffer,
			  can cause UB
* @Warning - UB if "bytes" is larger than "dest" 
* @time complexity - O(n) 
* @Space complexity - O(1)  */
ssize_t CBRead(cbuff_t* cbuff, char* dest, size_t bytes);

/*@Desc - tests whether a given buffer is empty
* @Params - buff: buffer to test
* @Return - returns 1 (true) if empty
* @Return - returns 0 (false) if not empty
* @Warnings - if cbuff param is not a pointer to a valid buffer,
			  can cause UB
* @time complexity - O(1) 
* @Space complexity - O(1)  */
int CBIsEmpty(const cbuff_t* buff);

/*@Desc - calculates amount of occupied memory in a given buffer
* @Params - buff: buffer in which to calculate occupied memory 
* @Return - returns number of occupied bytes in given buffer
* @Warnings - if cbuff param is not a pointer to a valid buffer,
			  can cause UB
* @time complexity - O(1) 
* @Space complexity - O(1)  */
size_t CBSize(const cbuff_t* buff);

/*@Desc - calculates amount of unoccupied memory in a given buffer
* @Params - buff: buffer in which to calculate unoccupied memory 
* @Return - returns number of unoccupied bytes in given buffer
* @Warnings - if cbuff param is not a pointer to a valid buffer,
			  can cause UB
* @time complexity - O(1) 
* @Space complexity - O(1)  */
size_t CBFreeSpace(const cbuff_t* buff);

/*@Desc - calculates the capacity of a given buffer
* @Params - buff: buffer of which to calculate capacity 
* @Return - returns number of bytes in given buffer
* @Warnings - if cbuff param is not a pointer to a valid buffer,
			  can cause UB
* @time complexity - O(1) 
* @Space complexity - O(1)  */
size_t CBCapacity(const cbuff_t* buff);


#endif

