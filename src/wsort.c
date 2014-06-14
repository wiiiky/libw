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
#include "wsort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



static void w_quick_sort_internal(void *data,
                                  void *key,
                                  int start, int end,
                                  WSortCompare compare,
                                  WSortAssign assign,
                                  WSortSave save, WSortRestore restore)
{
    if (start >= end) {
        return;
    }

    int i = start;
    int j = end;

    save(data, i, key);
    while (i < j) {
        while (compare(data, j, key) >= 0 && j > i) {
            j--;
        }
        assign(data, i, j);
        if (i >= j) {
            break;
        }
        while (compare(data, i, key) <= 0 && i < j) {
            i++;
        }
        assign(data, j, i);
    }
    restore(data, i, key);
    w_quick_sort_internal(data, key, start, i - 1, compare, assign, save,
                          restore);
    w_quick_sort_internal(data, key, i + 1, end, compare, assign, save,
                          restore);
}

void w_quick_sort(void *data, unsigned int count,
                  WSortCompare compare,
                  WSortAssign assign,
                  WSortSave save,
                  WSortRestore restore, WSortNew _new, WSortFree fre)
{
    void *key = _new();
    w_quick_sort_internal(data, key, 0, count - 1, compare, assign, save,
                          restore);
    fre(key);
}


/*
 * Integer functions for quick sort
 */
int w_quick_sort_int_compare(void *data, int index, void *b)
{
    int *A = (int *) data;
    int *B = (int *) b;
    return A[index] - *B;
}

void w_quick_sort_int_assign(void *data, int i, int j)
{
    int *ints = (int *) data;
    ints[i] = ints[j];
}

void w_quick_sort_int_save(void *data, int i, void *key)
{
    int *ints = (int *) data;
    *(int *) key = ints[i];
}

void w_quick_sort_int_restore(void *data, int index, void *key)
{
    int *ints = (int *) data;
    ints[index] = *((int *) key);
}

void *w_quick_sort_int_new()
{
    int *i = (int *) malloc(sizeof(int));
    return i;
}

void w_quick_sort_int_free(void *a)
{
    free(a);
}

/*
 * String functions for quick sort
 */
int w_quick_sort_string_compare(void *data, int i, void *key)
{
    char **str = (char **) data;
    char *s1 = str[i];
    char *s2 = *((char **) key);
    return strcmp(s1, s2);
}

void w_quick_sort_string_assign(void *data, int i, int j)
{
    char **str = (char **) data;
    str[i] = str[j];
}

void w_quick_sort_string_save(void *data, int i, void *key)
{
    char **k = (char **) key;
    char **str = (char **) data;
    *k = str[i];
}

void w_quick_sort_string_restore(void *data, int i, void *key)
{
    char **k = (char **) key;
    char **str = (char **) data;
    str[i] = *k;
}

void *w_quick_sort_string_new()
{
    char **key = (char **) malloc(sizeof(char *));
    return key;
}

void w_quick_sort_string_free(void *key)
{
    free(key);
}
