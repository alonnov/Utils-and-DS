/* *****************************
 Name:     Alon Nov
 Exercise: hash table
 Date:     16.12.2024
 Reviewer: 
 
********************************/

#include <stdlib.h>  /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h>  /* assert */

#include "dll.h" /* dll_t, DLLCreate, DLLDestroy, DLLPushBack, DLLPopBack, 
					DLLBegin, DLLEnd, DLLGetData, DLLRemove, DLLIsEmpty, 
					DLLIsEmpty, DLLForEach */ 
#include "hash.h" /* API */

enum STAT
{
    SUCCESS,
    FAILURE      
};

enum test
{
    FALSE,
    TRUE          
};

struct hash
{
	hash_func_t hasher;
	hash_key_cmp_t comp;
	size_t capacity;	
	dll_t* buckets[1];
};		

typedef struct key_value
{
	void* key;
	void* value;
}key_val_t;

typedef struct kcmp
{
	void* key;
	hash_key_cmp_t cmp_func;
}match_t;

typedef struct act
{
	void* params;
	hash_action_t act_func;
}action_t;


int HashMatch(const void* data, const void* params)
{
	hash_key_cmp_t cmp_fun = ((match_t*)params)->cmp_func;

	return cmp_fun(((key_val_t*)data)->key, ((match_t*)params)->key);
}

int HashAction(void* data, void* params)
{	
	return (((action_t*)params)->act_func(((key_val_t*)data)->value,
		   ((action_t*)params)->params));
}

static dll_iter_t FindNode(hash_t* hash, dll_t* bucket, void* key)
{
	match_t data = {0};
	data.cmp_func = hash->comp;
	data.key = key;

	return DLLFind(DLLBegin(bucket), DLLEnd(bucket), &data, HashMatch);
}

/*
static dll_iter_t FindNode(hash_t* hash, dll_t* bucket, void* key)
{
	dll_iter_t node = NULL;

	for(node = DLLBegin(bucket); !DLLIsIterEqual(node, DLLEnd(bucket)) ; 
		node = DLLNext(node)) 
	{
		if(TRUE == hash->comp(((key_val_t*)DLLGetData(node))->key, key))
		{
			break;
		}
	}

	return node;
}
*/

/***************************HashCreate***************************************/
hash_t* HashCreate(hash_func_t hash_func, size_t capacity, hash_key_cmp_t key_cmp)
{
	size_t i = 0;
	hash_t* hash = (hash_t*)malloc(sizeof(hash_t) + capacity  * sizeof(dll_t*));
	if(NULL == hash)
	{
		return NULL;
	}
	
	hash->hasher = hash_func;
	hash->comp = key_cmp;
	hash->capacity = capacity;

	for(; i < capacity; ++i)
	{
		hash->buckets[i] = DLLCreate();
		if(NULL == hash->buckets[i])
		{
			for(; 0 < i ; --i)
			{
				free(hash->buckets[i]);
			}
			free(hash->buckets[0]);
			free(hash);
			return NULL;
		}
	}	

	return hash;					
}	

/***************************HashDestroy**************************************/	
void HashDestroy(hash_t* hash)
{	
	size_t i = 0;
	dll_t* bucket = NULL;
	
	assert(hash);

	for(bucket = hash->buckets[0]; i < hash->capacity;
	    ++i, bucket = hash->buckets[i])
	{
		while(FALSE == DLLIsEmpty(bucket))
		{
			free(DLLPopBack(bucket));
		}
		DLLDestroy(bucket);
	}	
	memset(hash, 0, sizeof(hash_t));
	free(hash);
}		

/***************************HashInsert***************************************/
int HashInsert(hash_t* hash, void* value, void* key)
{
	dll_t* bucket = NULL;
	key_val_t* key_val = NULL; 

	assert(hash);
	assert(value);
	assert(key);
		
	key_val = (key_val_t*)malloc(sizeof(key_val_t));
	if(NULL == key_val)
	{
		return FAILURE;
	}

	key_val->key = key;
	key_val->value = value;

	bucket = hash->buckets[hash->hasher(key) % (hash->capacity)];

	if(DLLPushBack(bucket, key_val) ==
	   DLLEnd(bucket))
	{
		free(key_val);
		return FAILURE;
	}
			
	return SUCCESS;
}	


/***************************HashRemove***************************************/
void* HashRemove(hash_t* hash, void* key)
{		
	dll_iter_t node = NULL; 
	dll_t* bucket = NULL;
	key_val_t* data = NULL;
	void* val = NULL;

	assert(hash);
	assert(key);

	bucket = hash->buckets[hash->hasher(key) % (hash->capacity)];
	node = FindNode(hash, bucket, key);
	if(DLLEnd(bucket) == node)
	{
		return NULL;
	}
	data = (key_val_t*)DLLGetData(node);
	val = data->value;

	free(data);
	DLLRemove(node); 

	return val;
}

/***************************HashFind****************************************/
void* HashFind(hash_t* hash, void* key)
{	
	dll_t* bucket = NULL;
	dll_iter_t node = NULL;
	key_val_t* data = NULL;

	assert(hash);
	assert(key);

	bucket = hash->buckets[hash->hasher(key) % (hash->capacity)];
	node = FindNode(hash, bucket, key);
	if(node == DLLEnd(bucket))
	{
		return NULL;
	}
	data = DLLGetData(node);

	return (void*)data->value;
}	

/******************************HashForEach****************************************/
int HashForEach(hash_t* hash, hash_action_t action_func, void* params)
{
	dll_t* runner = NULL;
	size_t i = 0;
	int res = 0;
	action_t action = {0};

	assert(hash);
	assert(action_func);

	action.act_func = action_func;
	action.params = params;

	for(runner = hash->buckets[0]; i < hash->capacity && res == SUCCESS; 
		++i, runner = hash->buckets[i])
	{
		if(FALSE == DLLIsEmpty(runner))
		{
			res = DLLForEach(DLLBegin(runner), DLLEnd(runner), &action, HashAction);		
		}
	}

	return res;
}


/***************************HashSize******************************************/
size_t HashSize(const hash_t* hash)
{	
	size_t size = 0;
	size_t i = 0;

	assert(hash);
	
	for(; i < hash->capacity; ++i)
	{
		size += DLLCount(hash->buckets[i]);
	}
	
	return size;
}

/***************************HashIsEmpty***************************************/
int HashIsEmpty(const hash_t* hash)
{
	size_t i = 0;

	assert(hash);
	
	for(; i < hash->capacity; ++i)
	{
		if(!DLLIsEmpty(hash->buckets[i]))
		{
			return FALSE;
		}
	}
	
	return TRUE;
}	


