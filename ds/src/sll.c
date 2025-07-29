/* *****************************
 Name:     Alon Nov
 Exercise: singly linked list
 Reviewer: Israela Zimro
 Date:     20.10.2024
 
********************************/

#include <stdlib.h>  /* size_t, malloc, free */
#include <assert.h>  /* assert */

#include "sll.h" /* API */

struct sll
{
	sll_iter_t head;
	sll_iter_t tail;	
};		

struct node
{
	void* data;
	sll_iter_t next;
};

/***************************CreateNode**************************************/
static sll_iter_t CreateNode(void* data, sll_iter_t ptr_next)
{
	sll_iter_t new_node = malloc(sizeof(struct node));	
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	new_node->next = ptr_next;
	
	return new_node;
}	

/***************************SLLCreate***************************************/
sll_t* SLLCreate(void)
{
	sll_t* list = malloc(sizeof(sll_t));
	sll_iter_t dummy = NULL;
	if(NULL == list)
	{
		return NULL;
	}
	
	dummy = CreateNode((void*)list, NULL);		
	list->head = dummy;
	list->tail = dummy;
			
	return list;					
}	

/***************************SLLDestroy**************************************/	
void SLLDestroy(sll_t* list)
{
	sll_iter_t temp = list->head;
	
	while(temp != list->tail) 
	{
		temp = SLLRemove(temp);
	}
		
	free(list->tail);		
	free(list);
}		

/***************************SLLInsert***************************************/
sll_iter_t SLLInsert(sll_t* list, sll_iter_t pos, void* new_data)
{
	sll_iter_t new_node = CreateNode(pos->data, pos->next);	
	if(NULL == new_node)
	{
		return NULL;
	}	
	
	if(list->tail == pos)
	{
		list->tail = new_node;
	}

	pos->data = new_data;
	pos->next = new_node;
		
	return pos;
}	

/***************************SLLRemove***************************************/
sll_iter_t SLLRemove(sll_iter_t pos)
{	
	sll_iter_t temp = pos->next;
	
	pos->data = temp->data;
	pos->next = temp->next;
	
	if(NULL == temp->next)
	{
		((sll_t*)temp->data)->tail = pos;	
	}	
	
	free(temp);
	
	return pos;
}

/****************************Count*****************************************/
static int Count(void* unused, void* len)
{
	(void)unused;
	++*(size_t*)len;
	
	return 0;
}	

/***************************SLLCount***************************************/
size_t SLLCount(const sll_t* list)
{
	size_t len = 0;
	SLLForEach(list->head, list->tail, &len, Count);
	
	return len;
}	

/***************************SLLNext***************************************/
sll_iter_t SLLNext(sll_iter_t pos)
{
	return pos->next;
}

/***************************SLLBegin**************************************/
sll_iter_t SLLBegin(const sll_t* list)
{
	return list->head;
}

/***************************SLLEnd****************************************/
sll_iter_t SLLEnd(const sll_t* list)
{
	return list->tail;
}	

/**************************SLLGetData*************************************/
void* SLLGetData(sll_iter_t pos)
{
	return pos->data;
}

/**************************SLLSetData*************************************/
void SLLSetData(sll_iter_t pos, void* data)
{
	pos->data = data;
}

/****************************SLLFind**************************************/
sll_iter_t SLLFind(sll_iter_t start, sll_iter_t end, 
const void* data_match, sll_match_t match_func)
{	
	sll_iter_t temp = start;
	
	for(; SLLIsIterEq(temp,end); temp = SLLNext(temp))
	{
		if(match_func(temp->data, data_match))
		{
			break;
		}
	}
	
	return temp;
}			

/***************************SLLForEach************************************/
int SLLForEach(sll_iter_t start, sll_iter_t end,
 void* params, sll_action_t action_func)
{
	int res = 0;
	sll_iter_t temp = start;
	
	while((0 == res) && SLLIsIterEq(temp, end))
	{
		res = action_func(temp->data, params);
		temp = SLLNext(temp);
	}		
	
	return res;
}

/**************************SLLIsIterEq***********************************/
int SLLIsIterEq(sll_iter_t pos1,sll_iter_t pos2)
{
	return pos1 == pos2;
}

/***************************SLLAppend************************************/
sll_t* SLLAppend(sll_t* dest, sll_t* src)
{
	dest->tail->data = src->head->data;
	dest->tail->next = src->head->next;
	dest->tail = src->tail;
	
	src->head->data = src;
	src->head->next = NULL;
	src->tail = src->head;
	
	dest->tail->data = dest;

	return dest; 
}	
		
	

