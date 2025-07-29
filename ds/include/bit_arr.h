/* *****************************
 Name:     Alon Nov
 Exercise: bit_arr
 Reviewer: Shani Davidian
 Date:     14.10.2024
 
********************************/

#ifndef __BIT_ARRAY_H__
#define __BIT_ARRAY_H__

#include <stdint.h>  /* uint64_t */
#include <stddef.h> /* size_t */

typedef uint64_t bit_arr_t;

/*@Desc - set all bits to 1
* @Params - bit_arr_t
* @Return - updated bit array */
bit_arr_t BitArrSetAll(bit_arr_t bit_arr);

/*@Desc - set all bits to 0
* @Params - bit_arr_t
* @Return - updated bit array*/
bit_arr_t BitArrResetAll(bit_arr_t bit_arr);

/*@Desc - set a bit index to 1
* @Params - bit_arr_t, index
* @Return - updated bit array
* idx must be between 0 and 63*/
bit_arr_t BitArrSetBitOn(bit_arr_t bit_arr, size_t idx);

/*@Desc - set a bit index to 0
* @Return - updated bit array
* idx must be between 0 and 63*/
bit_arr_t BitArrSetBitOff(bit_arr_t bit_arr, size_t idx);

/*@Desc - set a bit index to val
* @return - updated bit array
* idx must be between 0 and 63
* val must be 1 or 0*/
bit_arr_t BitArrSetBit(bit_arr_t bit_arr, size_t idx, int val);

/*@Desc - get value of a bit index
* @Return - value of bit index
* idx must be between 0 and 63*/
int BitArrGetVal(bit_arr_t bit_arr, size_t idx);

/*@Desc - flip value of a bit index (0 -> 1, 1 -> 0)
* @Params - bit_arr_t
* @Return - updated bit array
* idx must be between 0 and 63*/
bit_arr_t BitArrFlipBit(bit_arr_t bit_arr, size_t idx);

/*@Desc - Mirror positions of all bits (1100 -> 0011)
* @Return - updated bit array*/
bit_arr_t BitArrMirror(bit_arr_t bit_arr);

/*@Desc - shift all bits to right and move rightmost bit to leftmost position (0101 -> 1010)
* @Return - updated bit array*/
bit_arr_t BitArrRotateRight(bit_arr_t bit_arr);

/*@Desc - shift all bits to left and move leftmost bit to rightmost position (1010 -> 0101)
* @Return - updated bit array */
bit_arr_t BitArrRotateLeft(bit_arr_t bit_arr);

/*@Desc - count number of bits set to 1
* @Return - number of bits that are equal to 1 */
size_t BitArrCountOn(bit_arr_t bit_arr);

/*@Desc - count number of bits set to 0
* @Return - number of bits that are equal to 0 */
size_t BitArrCountOff(bit_arr_t bit_arr);

/*@Desc - parse bit_arr to string (0101 -> "0101")
* @Error - Does not check for dest size*/
void BitArrToString(bit_arr_t bit_arr, char* dest);

size_t BitArrCountOnLut(bit_arr_t bit_arr);

bit_arr_t BitArrMirrorLut(bit_arr_t bit_arr);

#endif

