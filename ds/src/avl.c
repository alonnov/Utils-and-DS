/* *****************************
 Name:     Alon Nov
 Exercise: AVL
 Date:	   10.12.2024   
 Reviewer: Yonathan Levy

********************************/

#include <stdlib.h>  /* calloc, free */
#include <string.h>  /* memset */
#include <assert.h>  /* assert */

#include "avl.h" /* API */

#define MAX(x, y) ((x) > (y) ? (x) : (y))

typedef enum stat
{
    SUCCESS,
    FAILURE          
}status;

typedef enum testy
{
    FALSE,
    TRUE          
}test;

typedef struct node node_t;

struct avl
{
    node_t* root;
    avl_compare_t comp;
};

struct node 
{
    void* data;
    node_t* left;
    node_t* right;
    int height;
};


/***************************CreateNode**************************************/
static node_t* CreateNode(void* data)
{
	node_t* node = (node_t*)malloc(sizeof(node_t));	
	if(NULL == node)
	{
		return NULL;
	}
	
	node->data = data;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;

	return node;
}	


/***************************Leftmost**************************************/
static node_t* Leftmost(node_t* node)
{		
	if(NULL == node)
	{
		return NULL;
	}

	if(NULL == node->left)
	{
		return node;
	}

	return Leftmost(node->left);	
}	


/**************************GetHeight****************************************/
static int GetHeight(node_t* node)
{
    if(NULL == node)
    {
        return 0;
    }

    return node->height;
}

/**************************Rotations****************************************/
static node_t* RotL(node_t* node)
{
	node_t* temp = node->right;
	
	node->right = temp->left;
	temp->left = node;

	node->height = MAX(GetHeight(node->left), GetHeight(node->right)) + 1;
	temp->height = MAX(GetHeight(temp->left), GetHeight(temp->right)) + 1;

	return temp;
}

static node_t* RotR(node_t* node)
{
	node_t* temp = node->left;

	node->left = temp->right;
	temp->right = node;

	node->height = MAX(GetHeight(node->left), GetHeight(node->right)) + 1;
	temp->height = MAX(GetHeight(temp->left), GetHeight(temp->right)) + 1;

	return temp;
}


/**************************Balance****************************************/
static int CalcBalance(node_t* node)
{
	return GetHeight(node->left) - GetHeight(node->right);
}


/**************************Balance****************************************/
static node_t* Balance(avl_t* tree, node_t* node)
{	
	int balance = CalcBalance(node);
	
	if(1 < balance)
	{
		if(CalcBalance(node->left) <= -1)
		{
			node->left = RotL(node->left);	
		}
		return RotR(node);	 	
	}
	else if(balance < -1) 
	{
		if(1 <= CalcBalance(node->right))
		{
			node->right = RotR(node->right);	
		}
		return RotL(node);
	}

	return node;
}


/***************************AVLCreate***************************************/
avl_t* AVLCreate(avl_compare_t compare)
{
	avl_t* tree = NULL;
	
	assert(compare);
	
	tree = (avl_t*)malloc(sizeof(avl_t));
	if(NULL == tree)
	{
		return NULL;
	}
	tree->root = NULL;
	tree->comp = compare;

	return tree;					
}	


/***************************DestroyRec**************************************/
void DestroyRec(avl_t* tree, node_t* node)
{
	if(NULL == node)
	{
		return;
	}
	
	DestroyRec(tree, node->left);
	DestroyRec(tree, node->right);
	free(node);
}


/***************************AVLDestroy**************************************/
void AVLDestroy(avl_t* tree)
{
	assert(tree);
	
	DestroyRec(tree, tree->root);
	memset(tree, 0, sizeof(avl_t));
	free(tree);
}		


/**************************InsertRec******************************************/
static node_t* InsertRec(avl_t* tree, node_t* node, node_t* new_node)
{
	if(NULL == node)					 
	{
		return new_node;
	}

	if(tree->comp(new_node->data, node->data) < 0)
	{
		node->left = InsertRec(tree, node->left, new_node);
	}
 	else
	{
		node->right = InsertRec(tree, node->right, new_node);
	}

	node->height = MAX(GetHeight(node->left), GetHeight(node->right)) + 1;
		
	return Balance(tree, node);
}


/***************************AVLInsert***************************************/
int AVLInsert(avl_t* tree, void* data)
{
	node_t* new_node = NULL;

	assert(tree);
	assert(data);

	new_node = CreateNode(data);	
	if(NULL == new_node)
	{
		return FAILURE;
	}	

	if(NULL == tree->root)
	{		
		tree->root = new_node;
		tree->root->height = 1;
		return SUCCESS;
	}

	tree->root = InsertRec(tree, tree->root, new_node);

	return SUCCESS;
}	


/**************************RemoveRec******************************************/
static node_t* RemoveRec(avl_t* tree, node_t* node, void* data, test* removed)
{
	int res = 0;
	node_t* temp = NULL;

	if(NULL == node)		
	{
		return NULL;
	}

	res = tree->comp(data, node->data);

	if(res < 0)
	{
		node->left = RemoveRec(tree, node->left, data, removed);
	}
 	else if(res > 0)
	{
		node->right = RemoveRec(tree, node->right, data, removed);
	}
	else
	{
		*removed = TRUE;
		
		if(NULL == node->left && NULL == node->right)		
		{
			free(node);
			return NULL;
		}

		if(node->left && node->right)
		{
			temp = Leftmost(node->right);
			node->data = temp->data;
			node->right = RemoveRec(tree, node->right, temp->data, removed);
		}
		else
		{
			temp = (node->left) ? node->left : node->right;
			free(node);
			return temp;
		}		
	}	
	
	if(*removed == TRUE)
	{
		node->height = MAX(GetHeight(node->left), GetHeight(node->right)) + 1;
		return Balance(tree, node);	
	}
	
	return node;
}


/***************************AVLRemove***************************************/
void* AVLRemove(avl_t* tree, void* data)
{	
	test removed = FALSE;

	assert(tree);
	assert(data);

	if(NULL == tree->root)
	{
		return NULL;
	}

	tree->root = RemoveRec(tree, tree->root, data, &removed);

	return removed ? data : NULL;	 				
}


/**************************FindRec*******************************************/
static node_t* FindRec(avl_t* tree, node_t* node, const void* data, int* res)
{	
	if(0 == *res || NULL == node)
	{
		return node;
	}
	
	*res = tree->comp(data, node->data);

	if(0 > *res)
	{
		node = FindRec(tree, node->left, data, res);
	}
 	else if(0 < *res)
	{
		node = FindRec(tree, node->right, data, res);
	}	

	return node;
}


/****************************AVLFind**************************************/
void* AVLFind(const avl_t* tree, const void* data)
{	
	node_t* node = NULL;
	int res = 5;

	assert(tree);
	assert(data);

	if(TRUE == AVLIsEmpty(tree))
	{
		return NULL;
	}

	node = FindRec((avl_t*)tree, tree->root, data, &res);

	return NULL == node ? NULL : node->data;	
}			


/**************************AVLIsEmpty***********************************/
int AVLIsEmpty(const avl_t* tree)
{
	assert(tree);
		
	return NULL == tree->root;
}		


/****************************Count*****************************************/
static int Count(void* unused, void* len)
{
	(void)unused;
	++*(size_t*)len;

	return SUCCESS;
}	


/***************************AVLSize***************************************/
size_t AVLSize(const avl_t* tree)
{
	size_t len = 0;

	assert(tree);
	
	AVLForEach((avl_t*)tree, Count, &len, IN_ORDER);

	return len;
}	



/***************************Traversals**************************************/
static status PreOrder(node_t* root, avl_action_t action, void* params)
{
	if(NULL == root)
	{
		return SUCCESS;
	}

	if(FAILURE == action(root->data, params))
	{
		return FAILURE;
	}

	PreOrder(root->left, action, params);
	PreOrder(root->right, action, params);

	return SUCCESS;
}

static status InOrder(node_t* root, avl_action_t action, void* params)
{
	if(NULL == root)
	{
		return SUCCESS;
	}

	InOrder(root->left, action, params);

	if(FAILURE == action(root->data, params))
	{
		return FAILURE;
	}
	
	InOrder(root->right, action, params);

	return SUCCESS;
}

static status PostOrder(node_t* root, avl_action_t action, void* params)
{
	if(NULL == root)
	{
		return SUCCESS;
	}

	PostOrder(root->left, action, params);
	PostOrder(root->right, action, params);

	if(FAILURE == action(root->data, params))
	{
		return FAILURE;
	}

	return SUCCESS;
}

/***************************AVLForEach************************************/
int AVLForEach(avl_t* tree, avl_action_t action, void* params, avl_search_order order)
{			   
	int res = 0;
	
	assert(tree);
	assert(action);

	switch(order)
	{
	case PRE_ORDER:
		res = PreOrder(tree->root, action, params);
		break;

	case POST_ORDER:
		res = PostOrder(tree->root, action, params);
		break;

	default:
		res = InOrder(tree->root, action, params);
		break;
	}

	return res;
}	


ssize_t AVLHeight(const avl_t* tree)
{
	if(TRUE == AVLIsEmpty(tree))
	{
		return -1;
	}

	return tree->root->height - 1;
}










