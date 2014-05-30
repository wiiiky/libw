/*
 * Copyright (C) 2014  Wiky L
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with main.c; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */
#ifndef __WL_WHASHTABLE_H__
#define __WL_WHASHTABLE_H__
/*
 * hash table
 */

/*
 * The structure of WHastTable is not public
 */
typedef struct _WHashTable WHashTable;


/*
 * The hash function
 * 
 * @return: the hash code
 */
typedef unsigned int (*WHashFunc) (const void *data);
/*
 * The equal function
 * 
 * @return: zero if equal, non-zero if not.
 */
typedef int (*WEqualFunc) (const void *a, const void *b);
/*
 * the key & value destroy function
 */
typedef void (*WKeyDestroyFunc) (void *key);
typedef void (*WValueDestroyFunc) (void *value);

/*
 *
 */
typedef int (*WNodeFunc) (void *key, void *value, void *user_data);

/*
 * create a new WHastTable
 */
WHashTable *w_hash_table_new(unsigned short i,
							 WHashFunc hash_func,
							 WEqualFunc equal_func,
							 WKeyDestroyFunc key_func,
							 WValueDestroyFunc value_func);

/*
 * @description: Insert a new key:value into hash table
 *				 if the key already exists, just update its value
 *				 if you want to insert a same key , use w_hash_table_append
 * @param h: the hash table
 * @param key: the key
 * @param value: the value
 */
void w_hash_table_insert(WHashTable * h, void *key, void *value);


/*
 * @description: find the value associated to to key
 * 
 * @return: the value if found, or NULL
 */
void *w_hash_table_find(WHashTable * h, void *key);

/*
 * @description: find the node that make node_func return 0
 * 
 * @return: the value 
 */
void *w_hash_table_find_custom(WHashTable * h, WNodeFunc node_func,
							   void *data);


/*
 * @description: free a hash table
 *				 this function will call WKeyDestroyFunc and 
 *				 WValueDestroyFunc on every element.
 */
void w_hash_table_free_full(WHashTable * h);

/*
 * @descrition: just free hash table itself
 */
void w_hash_table_free(WHashTable * h);


/*
 * hash and equal functions
 */
unsigned int w_str_hash(const void *p);
int w_str_equal(const void *s1, const void *s2);



void w_hash_table_print(WHashTable * h);



#endif
