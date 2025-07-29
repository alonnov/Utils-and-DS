/* *****************************
 Name:     Alon Nov
 Exercise: bit_arr
 Reviewer: Shani Davidian
 Date:     14.10.2024
 
********************************/

#include <stdio.h>   /* size_t, puts */
#include <stdint.h>  /* uint64_t */
#include <limits.h>  /* CHAR_BIT */

#include "bit_arr.h" /* API */

static bit_arr_t altr_mask0 = 0xAAAAAAAAAAAAAAAA; /*1010101010101010 */
static bit_arr_t altr_mask1 = 0x5555555555555555; /*0101010101010101 */
static bit_arr_t pair_mask0 = 0xCCCCCCCCCCCCCCCC; /*1100110011001100 */
static bit_arr_t pair_mask1 = 0x3333333333333333; /*0011001100110011 */
static bit_arr_t quad_mask0 = 0xF0F0F0F0F0F0F0F0; 
static bit_arr_t quad_mask1 = 0x0F0F0F0F0F0F0F0F; 
static bit_arr_t octa_mask0 = 0xFF00FF00FF00FF00; 
static bit_arr_t octa_mask1 = 0x00FF00FF00FF00FF; 
static bit_arr_t hexa_mask0 = 0xFFFF0000FFFF0000; 
static bit_arr_t hexa_mask1 = 0x0000FFFF0000FFFF;
static bit_arr_t half_mask0 = 0xFFFFFFFF00000000;
static bit_arr_t half_mask1 = 0x00000000FFFFFFFF;
static size_t count_lut[] = {0x0, 0x1, 0x1, 0x2, 0x1, 0x2, 0x2, 0x3, 0x1, 
0x2, 0x2, 0x3, 0x2, 0x3, 0x3, 0x4};
static size_t mirror_lut[] = {0x0, 0x8, 0x4, 0xC, 0x2, 0xA, 0x6, 0xE,
 0x1, 0x9, 0x5 ,0xD, 0x3, 0xB, 0x7, 0xF};


bit_arr_t BitArrSetAll(bit_arr_t bit_arr)
{
	return ~(bit_arr & 0);
}


bit_arr_t BitArrResetAll(bit_arr_t bit_arr)
{
	return bit_arr & 0;
}

	
bit_arr_t BitArrSetBitOn(bit_arr_t bit_arr, size_t idx)
{
	return bit_arr | ((bit_arr_t)1 << idx);
}	


bit_arr_t BitArrSetBitOff(bit_arr_t bit_arr, size_t idx)
{
	return bit_arr & ~((bit_arr_t)1 << idx);
}	


bit_arr_t BitArrSetBit(bit_arr_t bit_arr, size_t idx, int val)
{
	return BitArrSetBitOff(bit_arr, idx) | ((bit_arr_t)val << idx);
}


int BitArrGetVal(bit_arr_t bit_arr, size_t idx)
{
	return ((bit_arr >> idx) & (bit_arr_t)1);
}


bit_arr_t BitArrFlipBit(bit_arr_t bit_arr, size_t idx)
{	
	return bit_arr ^ ((bit_arr_t)1 << idx);
}	
	

bit_arr_t BitArrMirror(bit_arr_t bit_arr)
{
	bit_arr = ((bit_arr & half_mask0) >> 32) | ((bit_arr & half_mask1) << 32);
	bit_arr = ((bit_arr & hexa_mask0) >> 16) | ((bit_arr & hexa_mask1) << 16);
	bit_arr = ((bit_arr & octa_mask0) >> 8) | ((bit_arr & octa_mask1) << 8);
	bit_arr = ((bit_arr & quad_mask0) >> 4) | ((bit_arr & quad_mask1) << 4);
	bit_arr = ((bit_arr & pair_mask0) >> 2) | ((bit_arr & pair_mask1) << 2);
	bit_arr = ((bit_arr & altr_mask0) >> 1) | ((bit_arr & altr_mask1) << 1);
	
	return bit_arr;Only nodes themselves may be changed.
}	

bit_arr_t BitArrMirrorLut(bit_arr_t bit_arr) 
{
	bit_arr_t mirror = 0;
	size_t i = 0;
	size_t nibble = CHAR_BIT / 2;
	bit_arr_t mask = 0x0F;

	
	for(; (sizeof(bit_arr) * CHAR_BIT) > i; i += nibble)
	{
		mirror <<= nibble;
		mirror |= mirror_lut[bit_arr & mask];
		bit_arr >>= nibble;
	}	
	
	return mirror;	 
} 

bit_arr_t BitArrRotateRight(bit_arr_t bit_arr)
{	
	return (bit_arr >> 1) |
	((bit_arr_t)BitArrGetVal(bit_arr, 0) << (sizeof(bit_arr) * CHAR_BIT - 1));
}

	
bit_arr_t BitArrRotateLeft(bit_arr_t bit_arr)
{
	return (bit_arr << 1) | 
	((bit_arr_t)BitArrGetVal(bit_arr, (sizeof(bit_arr) * CHAR_BIT - 1)));
}

	
size_t BitArrCountOn(bit_arr_t bit_arr)
{
	bit_arr = ((bit_arr & altr_mask0) >> 1) + (bit_arr & altr_mask1);
	bit_arr = ((bit_arr & pair_mask0) >> 2) + (bit_arr & pair_mask1);
	bit_arr = ((bit_arr & quad_mask0) >> 4) + (bit_arr & quad_mask1);
	bit_arr = ((bit_arr & octa_mask0) >> 8) + (bit_arr & octa_mask1);
	bit_arr = ((bit_arr & hexa_mask0) >> 16) + (bit_arr & hexa_mask1);
	bit_arr = ((bit_arr & half_mask0) >> 32) + (bit_arr & half_mask1);
	
	return bit_arr;		
}

size_t BitArrCountOnLut(bit_arr_t bit_arr)
{
	size_t count = 0; 
	size_t nibble = CHAR_BIT / 2;
	
	for(;bit_arr ; bit_arr <<= nibble)
	{
		count += count_lut[bit_arr >> (sizeof(bit_arr) * CHAR_BIT - nibble)];
	}	
	return count;
}


size_t BitArrCountOff(bit_arr_t bit_arr)
{
	return BitArrCountOn(~(bit_arr));
}


void BitArrToString(bit_arr_t bit_arr, char* dest)
{
	size_t len = (sizeof(bit_arr) * CHAR_BIT);
	
		
	for(; 0 < len ; ++dest, --len)
	{
		*dest = BitArrGetVal(bit_arr, len - 1) + '0';
	}
	
	*dest = '\0';
}		
	


