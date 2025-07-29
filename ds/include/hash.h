/* *****************************
 Name:     Alon Nov
 Exercise: hash table
 Date:     16.12.2024
 Reviewer: 
 
********************************/

#ifndef __HASH_H__
#define __HASH_H__

#include <stddef.h> /* size_t */

typedef struct hash hash_t;

typedef size_t (*hash_func_t)(const void* key);
typedef int (*hash_key_cmp_t)(const void* key1, const void* key2);
typedef int (*hash_action_t)(void* data, void* params);

/*@Desc- creates a new Hash table data structure.
* @Param - hash_func: function to calculate and find the position 
                       of inserted key-value pair into the Hash table.
* @Param - num_of_buckets: the total number of backets in the hash table.
* @Param - key_cmp: function to find the currect key-value pair within 
                     each bucket
* @Return - returns a pointer to the newly created Hash Table, or NULL otherwise.
* @time complexity - O(1)
* @Space complexity - O(1) */
hash_t* HashCreate(hash_func_t hash_func, size_t capacity, hash_key_cmp_t key_cmp);


/*@Desc - Destroy and free the hash table
* @Param - hash: hash table to destroy
* @Return - N/A
* @time complexity  - O(m * n)
* @Space complexity - O(1) */
void HashDestroy(hash_t* hash);


/*@Desc - Inserts a given value into the given hash table in a particular place according to whatever index is generated from the given key
* @Param - hash - A pointer to hash table struct
* @Param - value - A pointer to a value which should be stored in the hast table
* @Param - key - A pointer to a key which is required to generate a unique idx
* @Return - 0 value on success and non 0 value on failure 
* @time complexity  - O(1)
* @Space complexity - O(1) */
int HashInsert(hash_t* hash, void* value, void* key);

/*@Desc - remove a key from hash, using  hash_key_cmp_t function
* @Param - hash , key = key to remove fron hash 
* @Return - return the key's value. if key's not found return NULL;
* @time complexity - O(n) 
* @Space complexity - O(1) */  
void* HashRemove(hash_t* hash, void* key);

/*@Desc - finds the  value that matches "key" using the hash_key_cmp_t function
* @Param - hash: the hast 
* @Param - key: the key to find
* @Return - the value matches the key, if it doesn't find it - return NULL
* @time complexity - O(n)
* @Space complexity - O(1) */
void* HashFind(hash_t* hash, void* key);


/*@Desc - performs a given action on every element in a given hash table
* @Param - hash: hash table
* @Param - action_func: function to perform action with
* @Param - params: argument for action_func
* @Return - 0(SUCCESS) on success and/or if action_func can't fail
* @Return - non 0 value on failure, if action_func can fail 
* @Warning - if action_func fails in any iteratrion, 
			 the program stops and returns non-zero value
* @time complexity - O(n) 
* @Space complexity - O(1) */
int HashForEach(hash_t* hash, hash_action_t action_func, void* params);


/*@description returns the amount of elements in the hash table
* @param - hash: hash table
* @return - number of elements in hash
* @time-complexity - O(n)
* @space-complexity - O(1) */
size_t HashSize(const hash_t* hash); 


/*@desc  - checks whether the Hash Table is empty
* @param - hash: a pointer to an Hash managibg structure
* @return - true if Hash is empty, false otherwise
* * @time complexity - O(m) (number of buckets)
* @Space complexity - O(1) */
int HashIsEmpty(const hash_t* hash);

#endif /*__HASH_T__*/
