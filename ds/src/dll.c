/* *****************************
 Name:     Alon Nov
 Exercise: doubly linked list 
 Date:	   27.10.2024   
 Reviewer: Yael Priz 

********************************/

#include <stdlib.h>  /* size_t, malloc, free */
#include <assert.h>  /* assert */

#include "dll.h" /* API */

typedef enum 
{
    SUCCESS,
    FAILURE
           
} STAT;


typedef struct node
{
	void* data;
	struct node* prev;
	struct node* next;
} node_t;


struct dll
{
	node_t head;
	node_t tail;	
};	

/***************************IterToNode**************************************/
static node_t* IterToNode(dll_iter_t iter)
{
	return iter;
}		

/***************************NodeToIter**************************************/
static dll_iter_t NodeToIter(node_t* node)
{
	return (dll_iter_t)node;
}

	
/**************************ConnectNodes*************************************/
static void ConnectNodes(node_t* node1, node_t* node2)
{
	node1->next = node2;
	node2->prev = node1;
}	
	

/***************************CreateNode**************************************/
static node_t* CreateNode(void* data)
{
	node_t* new_node = malloc(sizeof(node_t));	
	if(NULL == new_node)
	{
		return NULL;
	}
	
	DLLSetData(new_node, data);
	
	return new_node;
}	

/***************************DLLCreate***************************************/
dll_t* DLLCreate(void)
{
	dll_t* list = malloc(sizeof(dll_t));	
	if(NULL == list)
	{
		return NULL;
	}
	
	list->head.prev = NULL;
	list->head.next = &list->tail;
	
	list->tail.prev = &list->head;
	list->tail.next = NULL;
			
	return list;					
}	

/***************************DLLDestroy**************************************/	
void DLLDestroy(dll_t* list)
{
	node_t* curr = NULL;
	node_t* next = NULL;
	
	assert(list);
		
	for(curr = list->head.next; curr != &list->tail; curr = next) 
	{	
		next = curr->next;
		free(curr);
	}		
	free(list);
}		

/***************************DLLInsert***************************************/
dll_iter_t DLLInsert(dll_t* list, dll_iter_t pos, void* new_data)
{
	node_t* new_node = NULL;
	
	assert(list);
	assert(pos);
	
	new_node = CreateNode(new_data);	
	if(NULL == new_node)
	{
		return DLLEnd(list);
	}	
		
	ConnectNodes(DLLPrev(pos), new_node);
	ConnectNodes(new_node, pos);
		
	return new_node;
}	

/***************************DLLPushBack***************************************/
dll_iter_t DLLPushBack(dll_t* list, void* data)
{	
	assert(list);
	
	return DLLInsert(list, DLLEnd(list), data);
}

/***************************DLLPushFront**************************************/
dll_iter_t DLLPushFront(dll_t* list, void* data)
{
	assert(list);
	
	return DLLInsert(list, DLLBegin(list), data);

}

/***************************DLLRemove***************************************/
dll_iter_t DLLRemove(dll_iter_t pos)
{
	struct node* temp = NULL;
	
	assert(pos);
	assert(pos->next);
	
	temp = DLLNext(pos);
	ConnectNodes(DLLPrev(pos), DLLNext(pos));			

	free(pos);
	
	return temp;
}

/****************************DLLPopBack***************************************/
void* DLLPopBack(dll_t* list)
{
	void* pop_data = NULL;
	
	assert(list);
	
	pop_data = DLLGetData(DLLPrev(DLLEnd(list)));
	
	DLLRemove(DLLPrev(DLLEnd(list)));
	
	return pop_data;
}

/****************************DLLPopFront**************************************/	
void* DLLPopFront(dll_t* list)
{
	void* pop_data = NULL;
	
	assert(list);
	
	pop_data = DLLGetData(DLLBegin(list));
	
	DLLRemove(DLLBegin(list));
	
	return pop_data;
}


/***************************DLLSplice************************************/
dll_iter_t DLLSplice(dll_iter_t where, dll_iter_t start, dll_iter_t end)
{	
	assert(where);
	assert(start);
	assert(end);
	
	end = DLLPrev(end);	
	ConnectNodes(DLLPrev(start), DLLNext(end));			
	ConnectNodes(DLLPrev(where), start);
	ConnectNodes(end, where);

	return start; 
}	


/****************************DLLFind**************************************/
dll_iter_t DLLFind(dll_iter_t start, dll_iter_t end, 
const void* params, dll_match_t match_func)
{	
	struct node* temp = NULL;
	
	assert(start);
	assert(end);
	assert(params);
	
	for(temp = start; !DLLIsIterEqual(temp,end); temp = DLLNext(temp))
	{
		if(match_func(temp->data, params))
		{
			break;
		}
	}
	
	return temp;
}			

/****************************DLLFindMulti*************************************/
int DLLFindMulti(dll_t* res_list, dll_iter_t start, dll_iter_t end, 
				 const void* params, dll_match_t match_func)
{
	struct node* temp = NULL;
	
	assert(res_list);
	assert(start);
	assert(end);
	assert(params);

	for(temp = start; !DLLIsIterEqual(temp,end); temp = DLLNext(temp))
	{
		if(match_func(DLLGetData(temp), params))
		{
			if(DLLEnd(res_list) == DLLPushBack(res_list, DLLGetData(temp)))
			{
				return FAILURE;
			}
		}
	}
	
	return SUCCESS;

}


/***************************DLLForEach************************************/
int DLLForEach(dll_iter_t start, dll_iter_t end,
 void* params, dll_action_t action_func)
{
	int res = 0;
	struct node* temp = NULL;
	
	assert(start);
	assert(end);
	assert(action_func);
	
	for(temp = start; (SUCCESS == res) && !DLLIsIterEqual(temp, end);	
		temp = DLLNext(temp))
	{
		res = action_func(DLLGetData(temp), params);
	}

	return res;
}


/***************************DLLNext***************************************/
dll_iter_t DLLNext(dll_iter_t pos)
{
	assert(pos);
	assert(pos->next);
	
	return pos->next;
}


/***************************DLLPrev***************************************/
dll_iter_t DLLPrev(dll_iter_t pos)
{
	assert(pos);
	assert(pos->prev);
		
	return pos->prev;
}


/**************************DLLSetData*************************************/
void DLLSetData(dll_iter_t pos, void* data)
{
	assert(pos);
	
	pos->data = data;
}


/**************************DLLGetData*************************************/
void* DLLGetData(dll_iter_t pos)
{
	assert(pos);
	
	return pos->data;
}


/***************************DLLBegin**************************************/
dll_iter_t DLLBegin(const dll_t* list)
{
	assert(list);
		
	return DLLNext((struct node*)&list->head);
}

/***************************DLLEnd****************************************/
dll_iter_t DLLEnd(const dll_t* list)
{
	assert(list);
	
	return (struct node*)&list->tail;
}	


/****************************Count*****************************************/
static int Count(void* unused, void* len)
{
	(void)unused;
	++*(size_t*)len;

	return 0;
}	

/***************************DLLCount***************************************/
size_t DLLCount(const dll_t* list)
{
	size_t len = 0;
	
	assert(list);
	
	DLLForEach(DLLBegin(list), DLLEnd(list), &len, Count);

	return len;
}	


/**************************DLLIsIterEq***********************************/
int DLLIsIterEqual(dll_iter_t pos1, dll_iter_t pos2)
{
	assert(pos1);
	assert(pos2);
	
	return pos1 == pos2;
}


/**************************DLLIsEmpty***********************************/
int DLLIsEmpty(const dll_t* list)
{
	assert(list);
		
	return DLLIsIterEqual(DLLBegin(list), DLLEnd(list));
}		

