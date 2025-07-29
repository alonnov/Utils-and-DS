/* *****************************
 Name:     Alon Nov
 Exercise: sorted list 
 Date:	   29.10.2024   
 Reviewer: Liad Tiblum

********************************/

#include <stdlib.h>  /* size_t, malloc, free */
#include <string.h>  /* memset */
#include <assert.h>  /* assert */

#include "dll.h"     /*DLLCreate, DLLDestroy, DLLInsert, DLLRemove, DLLPopBack, 
					   DLLPopFront, DLLNext, DLLPrev, DLLBegin, DLLEnd,  
					   DLLIsIterEqual, DLLGetData, DLLForEach, DLLFind, 
					   DLLSplice, DLLCount, DLLIsEmpty */
#include "slist.h"   /* API */

struct slist
{
    slist_compare_t compare;
    dll_t* dll;   
};

	      
/***************************Operator***************************************/
typedef enum 
{
    OP_EQ, /* == */
    OP_G /* >= */
           
} op_t;

static int Operator(int data, op_t op)
{
		switch(op) 
		{
		case OP_EQ:
			return data == 0;
		case OP_G:
			return data >= 0;
		default:
			return 0;
		}    		
}


/***************************FindPos***************************************/
static slist_iter_t FindPos(slist_t* list, slist_iter_t start, 
							 slist_iter_t end, void* data, op_t op)
{
	slist_iter_t pos = start;		

	for(;!SListIsIterEqual(pos, end); pos = SListNext(pos))
	{		
		if(Operator(list->compare(SListGetData(pos), data), op))
		{
			break;
		}	
	}
				
	return pos;		
}		


/***************************SListCreate***************************************/
slist_t* SListCreate(slist_compare_t compare)
{
	slist_t* list = NULL;
	
	
	list = (slist_t*)malloc(sizeof(slist_t));
	if(NULL == list)
	{
		return NULL;
	}
	
	list->dll = DLLCreate();
	if(NULL == list->dll)
	{
		free(list);
		return NULL;
	}
	
	list->compare = compare;
			
	return list;					
}	


/***************************SListDestroy**************************************/	
void SListDestroy(slist_t* list)
{	
	assert(list);
	
	DLLDestroy(list->dll);	
	memset(list, 0, sizeof(slist_t));
	free(list);
}		
		

/***************************SListInsert***************************************/
slist_iter_t SListInsert(slist_t* list, void* data)
{	
	slist_iter_t pos = {0};
		
	assert(list);
	assert(list->dll);

	pos = FindPos(list, SListBegin(list), SListEnd(list), data, OP_G);
	
	pos.dll_iter = DLLInsert(list->dll, pos.dll_iter, data);
	
#ifndef NDEBUG
	pos.list = list;
#endif

	return pos;
}	


/***************************SListRemove***************************************/
slist_iter_t SListRemove(slist_iter_t pos)
{	
	pos.dll_iter = DLLRemove(pos.dll_iter);
	
	return pos;
}


/****************************SListPopBack*************************************/
void* SListPopBack(slist_t* list)
{	
	assert(list);
	assert(!SListIsEmpty(list));
		
	return DLLPopBack(list->dll);
}


/****************************SListPopFront**************************************/	
void* SListPopFront(slist_t* list)
{
	assert(list);
	assert(!SListIsEmpty(list));
	
	return DLLPopFront(list->dll);
}


/***************************SListNext***************************************/
slist_iter_t SListNext(slist_iter_t pos)
{
	pos.dll_iter = DLLNext(pos.dll_iter);
	
	return pos;
}


/***************************SListPrev***************************************/
slist_iter_t SListPrev(slist_iter_t pos)
{	
	pos.dll_iter = DLLPrev(pos.dll_iter);
	
	return pos;
}


/***************************SListBegin**************************************/
slist_iter_t SListBegin(slist_t* list)
{
	slist_iter_t first = {0};
	
	assert(list);
	
	first.dll_iter = DLLBegin(list->dll);
	
#ifndef NDEBUG
    first.list = list;
#endif

	
	return first;
}


/***************************SListEnd****************************************/
slist_iter_t SListEnd(slist_t* list)
{
	slist_iter_t last = {0};
	
	assert(list);
	
	last.dll_iter = DLLEnd(list->dll);
	
#ifndef NDEBUG
    last.list = list;
#endif

	return last;
}	


/**************************SListIsIterEqual***********************************/
int SListIsIterEqual(slist_iter_t pos1, slist_iter_t pos2)
{
	return DLLIsIterEqual(pos1.dll_iter, pos2.dll_iter);
}


/**************************SListGetData*************************************/
void* SListGetData(slist_iter_t iter)
{
	return DLLGetData(iter.dll_iter);
}


/***************************SListForEach************************************/
int SListForEach(slist_iter_t start, slist_iter_t end, void* params,
                 slist_action_t action_func)                
{
	assert(start.list == end.list);
	
	return DLLForEach(start.dll_iter, end.dll_iter, params, action_func);
}


/****************************SListFind**************************************/
slist_iter_t SListFind(slist_t* list, slist_iter_t start,
                       slist_iter_t end, void* data)
{	
	assert(list);

	assert(start.list == end.list);
	
	return FindPos(list, start, end, data, OP_EQ);
}			


/****************************SListFindIf*************************************/
slist_iter_t SListFindIf(slist_iter_t start, slist_iter_t end,
                         void* data, slist_match_t match)                        
{	
	slist_iter_t pos = {0};
	
	assert(start.list == end.list);

	pos.dll_iter = DLLFind(start.dll_iter, end.dll_iter, data, match);
	
#ifndef NDEBUG
    pos.list = start.list;
#endif
	
	return pos;
}


/***************************SListMerge************************************/
slist_t* SListMerge(slist_t* dest, slist_t* src)
{	
	slist_iter_t dest_pos = {0};
	slist_iter_t src_pos = {0};
	slist_iter_t start = {0};
	
	assert(dest);
	assert(src);
	assert(dest->compare == src->compare);
	
	dest_pos = SListBegin(dest);
	src_pos = SListBegin(src);
				
	while(!SListIsIterEqual(src_pos, SListEnd(src)))
	{	
		dest_pos = FindPos(dest, dest_pos, SListEnd(dest), 
		SListGetData(src_pos), OP_G);
		if(SListIsIterEqual(dest_pos, SListEnd(dest)))
		{
			break;
		}			
		start = src_pos;
		src_pos = FindPos(src, start, SListEnd(src), 
		SListGetData(dest_pos), OP_G);	
					
		DLLSplice(dest_pos.dll_iter, start.dll_iter, src_pos.dll_iter);
	}
	
	if(!SListIsIterEqual(src_pos, SListEnd(src)))
	{
		DLLSplice(dest_pos.dll_iter, src_pos.dll_iter, DLLEnd(src->dll));
	}	
	
	return dest; 
}


/***************************SListCount***************************************/
size_t SListCount(const slist_t* list)
{
	assert(list);
	
	return DLLCount(list->dll);
}	


/**************************SListIsEmpty***********************************/
int SListIsEmpty(const slist_t* list)
{
	assert(list);
	
	return DLLIsEmpty(list->dll);
}		
	

