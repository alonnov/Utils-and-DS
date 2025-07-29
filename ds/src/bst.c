/* *****************************
 Name:     Alon Nov
 Exercise: binary search tree
 Date:	   26.11.2024   
 Reviewer: Mor Weisberg

********************************/

#include <stdlib.h>  /* calloc, free */
#include <string.h>  /* memset */
#include <assert.h>  /* assert */

#include "bst.h" /* API */

typedef enum 
{
    SUCCESS,
    FAILURE
           
} STAT;

typedef struct node node_t;

struct node
{
    node_t* parent;
    node_t* smaller;
    node_t* bigger;
    void* data;
}; 

struct bst
{
    node_t root;
    bst_compare_t compare;
};

/***************************IterToNode**************************************/
static node_t* IterToNode(const bst_iter_t iter)
{
	return (node_t*)iter;
}		

/***************************NodeToIter**************************************/
static bst_iter_t NodeToIter(const node_t* node)
{
	return (bst_iter_t)node;
}

	
/**************************ConnectSmaller*************************************/
static void ConnectSmaller(node_t* node1, node_t* node2)
{
	node1->smaller = node2;
	node2->parent = node1;
}	
	

/**************************ConnectBigger*************************************/
static void ConnectBigger(node_t* node1, node_t* node2)
{
	node1->bigger = node2;
	node2->parent = node1;
}	


/***************************CreateNode**************************************/
static node_t* CreateNode(void* data)
{
	node_t* new_node = (node_t*)calloc(1, sizeof(node_t));	
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = data;
	
	return new_node;
}	


/***************************Smallest**************************************/
static node_t* Smallest(node_t* node)
{	
	for(; NULL != node->smaller ; node = node->smaller);	
	
	return node;	
}	


/***************************RemoveNode**************************************/
static void* RemoveNode(node_t* node)
{
	void* data = node->data;
	
	if(NULL == node->smaller && NULL == node->bigger)
	{
		if(node == node->parent->smaller)
		{
			node->parent->smaller = NULL;
		}
		
		else
		{
			node->parent->bigger = NULL;
		}	
	}
			
	else if(NULL == node->smaller)
	{
		if(node == node->parent->smaller)
		{
			ConnectSmaller(node->parent, node->bigger);
		}
		
		else
		{
			ConnectBigger(node->parent, node->bigger);
		}
	}
		
	else if(NULL == node->bigger)
	{
		if(node == node->parent->smaller)
		{
			ConnectSmaller(node->parent, node->smaller);
		}
		
		else
		{
			ConnectBigger(node->parent, node->smaller);
		}		
	}
	
	free(node);
	
	return data;									 
}


/***************************BSTCreate***************************************/
bst_t* BSTCreate(bst_compare_t compare)
{
	bst_t* tree = NULL;
	
	assert(compare);
	
	tree = (bst_t*)calloc(1, sizeof(bst_t));
	if(NULL == tree)
	{
		return NULL;
	}
	
	tree->compare = compare;
			
	return tree;					
}	


/***************************BSTDestroy**************************************/	
void BSTDestroy(bst_t* tree)
{
	node_t* curr = NULL;
	node_t* kill = NULL;
	node_t* end = NULL;
	
	assert(tree);
	
	end = BSTEnd(tree);
		
	for(curr = BSTBegin(tree) ; curr == end;)
	{		
		if(NULL == curr->bigger)
		{
			kill = curr;
			curr = curr->parent;
			if(curr->smaller == kill)
			{
				curr->smaller = NULL;
			}
			
			else
			{
				curr->bigger = NULL;
			}		
				
			free(kill);
			continue;
		}
						
		curr = Smallest(curr->bigger);			
	}
		
	memset(tree, 0, sizeof(bst_t));
	free(tree);			
}		


/***************************BSTInsert***************************************/
bst_iter_t BSTInsert(bst_t* tree, void* data)
{
	node_t* new_node = NULL;
	node_t* runner = NULL;
	
	assert(tree);
	
	new_node = CreateNode(data);	
	if(NULL == new_node)
	{
		return BSTEnd(tree);
	}	
	
	if(NULL == tree->root.smaller)
	{
		ConnectSmaller(&tree->root, new_node);
		return new_node;
	}
		
	for(runner = tree->root.smaller; 1;)
	{
		if(0 < tree->compare(BSTGetData(runner), new_node->data))
		{
			if(NULL == runner->smaller)
			{
				ConnectSmaller(runner, new_node);
				break;
			}	
			runner = runner->smaller;	 
		}
		
		else
		{
			if(NULL == runner->bigger)
			{
				ConnectBigger(runner, new_node);
				break;
			}	
			runner = runner->bigger;
		}
	}
	
	return new_node;
}	


/***************************BSTRemove***************************************/
void* BSTRemove(bst_iter_t pos)
{
	node_t* temp = NULL;
	node_t* node = NULL;
	void* data = NULL;
	
	assert(pos);
	assert(pos->parent);
	
	node = IterToNode(pos);
	
	if(NULL != node->smaller && NULL != node->bigger)
	{
		temp = node;
		node = IterToNode(BSTNext(NodeToIter(node)));
		data = temp->data; 
		node->data = data;
	}				 			
	
	return RemoveNode(node);
}


/****************************BSTFind**************************************/
bst_iter_t BSTFind(const bst_t* tree, void* data)
{	
	node_t* runner = NULL;
	int result = 0;
	
	assert(tree);
	
	for(runner = tree->root.smaller; NULL != runner;)
	{	
		result = tree->compare(runner->data, data);
				
		if(0 == result)
		{
			return runner;
		}
			
		runner = result > 0 ? runner->smaller : runner->bigger;	 
		
	}
	
	return BSTEnd(tree);	
}			


/**************************BSTGetData*************************************/
void* BSTGetData(bst_iter_t pos)
{
	node_t* node = NULL;
	
	assert(pos);
	
	node = IterToNode(pos);
	
	return node->data;
}


/**************************BSTIsEmpty***********************************/
int BSTIsEmpty(const bst_t* tree)
{
	assert(tree);
		
	return NULL == tree->root.smaller;
}		


/***************************BSTBegin**************************************/
bst_iter_t BSTBegin(const bst_t* tree)
{	
	node_t* node = NULL;
	
	assert(tree);
	
	node = 	Smallest((node_t*)&tree->root);
	
	return NodeToIter(node);		
}


/***************************BSTEnd****************************************/
bst_iter_t BSTEnd(const bst_t* tree)
{
	assert(tree);
	
	return NodeToIter(&tree->root);
}


/***************************BSTNext***************************************/
bst_iter_t BSTNext(bst_iter_t pos)
{
	node_t* node = NULL;
	
	assert(pos);
	assert(pos->parent);
		
	node = IterToNode(pos);
	
	if(NULL != pos->bigger)
	{
		node = Smallest(pos->bigger);
		return NodeToIter(node);
	}
		
	for(; node != node->parent->smaller ; node = node->parent); 
	
	node = node->parent;
		
	return NodeToIter(node);
}	

	
/***************************BSTPrev***************************************/
bst_iter_t BSTPrev(bst_iter_t pos)
{
	node_t* node = NULL;
	
	assert(pos);
	assert(pos->parent);
	
	node = IterToNode(pos);
		
	if(NULL != node->smaller)
	{
		for(node = node->smaller ; NULL != node->bigger ; node = node->bigger);	
 
		return NodeToIter(node);
	}
	
	for(; node != node->parent->bigger ; node = node->parent); 
		
	node = node->parent;
		
	return NodeToIter(node);
}	


/****************************Count*****************************************/
static int Count(const void* unused, const void* len)
{
	(void)unused;
	++*(size_t*)len;

	return SUCCESS;
}	


/***************************BSTSize***************************************/
size_t BSTSize(const bst_t* tree)
{
	bst_iter_t begin = NULL;
	bst_iter_t end = NULL;
	size_t len = 0;

	assert(tree);
	
	begin = BSTBegin(tree);
	end = BSTEnd(tree);
	
	BSTForEach(begin, end, Count, &len);

	return len;
}	


/**************************BSTIsIterEqual***********************************/
int BSTIsIterEqual(bst_iter_t pos1, bst_iter_t pos2)
{
	assert(pos1);
	assert(pos1);
	
	return pos1 == pos2;
}


/***************************BSTForEach************************************/
int BSTForEach(bst_iter_t start, bst_iter_t end, 
			   bst_action_t action_func, void* params)
{			   
	bst_iter_t runner = NULL;	
	int res = 0;
	
	assert(start);
	assert(end);
	assert(action_func);

	for(runner = start; (SUCCESS == res) && !BSTIsIterEqual(runner, end);	
		runner = BSTNext(runner))
	{
		res = action_func(BSTGetData(runner), params);
	}
	
	return res;
}	


