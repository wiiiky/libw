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

#ifndef __WL_WSORT_H__
#define __WL_WSORT_H__

/*
 * sort array
 */


typedef int (*WSortCompare) (void *data, int i, void *key);
typedef void (*WSortAssign) (void *data, int i, int j);
typedef void (*WSortSave) (void *data, int i, void *key);
typedef void (WSortRestore) (void *data, int i, void *key);
typedef void *(WSortNew) ();
typedef void (*WSortFree) (void *a);

/*
 * @descriptioin: sorts an array of any type using quick sort
 * 
 * @param data: the array, any type
 * @param count: the size of array
 * @param compare: the compare function for an element and the key
 * @param assign: the assign function for two elements
 * @param save: the save function to save the key
 * @param restore: the restore function to restore the key.
 * @param new: this function is used to allocate the memory space for key
 * @param fre: free the memory space of key.
 */
void w_quick_sort(void *data, unsigned int count,
                  WSortCompare compare,
                  WSortAssign assign,
                  WSortSave save,
                  WSortRestore restore, WSortNew _new, WSortFree fre);

/*
 * macro for integer array
 */
#define w_quick_sort_int(data,count) w_quick_sort((data),(count),\
                                    w_quick_sort_int_compare,\
                                    w_quick_sort_int_assign,\
                                    w_quick_sort_int_save,\
                                    w_quick_sort_int_restore,\
                                    w_quick_sort_int_new,\
                                    w_quick_sort_int_free)

/*
 * functions for integer array quick sort
 */
int w_quick_sort_int_compare(void *data, int i, void *key);
void w_quick_sort_int_assign(void *data, int i, int j);
void w_quick_sort_int_save(void *data, int i, void *key);
void w_quick_sort_int_restore(void *data, int i, void *key);
void *w_quick_sort_int_new();
void w_quick_sort_int_free(void *key);


/*
 * macro for string array
 */
#define w_quick_sort_string(data,count) w_quick_sort((data),(count),\
                                        w_quick_sort_string_compare,\
                                        w_quick_sort_string_assign,\
                                        w_quick_sort_string_save,\
                                        w_quick_sort_string_restore,\
                                        w_quick_sort_string_new,\
                                        w_quick_sort_string_free)

/*
 * functions for string array quick sort
 */
int w_quick_sort_string_compare(void *data, int i, void *key);
void w_quick_sort_string_assign(void *data, int i, int j);
void w_quick_sort_string_save(void *data, int i, void *key);
void w_quick_sort_string_restore(void *data, int i, void *key);
void *w_quick_sort_string_new();
void w_quick_sort_string_free(void *key);



#endif
