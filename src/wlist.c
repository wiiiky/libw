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

#include "wlist.h"
#include "m4.h"
#include <stdlib.h>

WList *w_list_new()
{
    return NULL;
}

WList *w_list_first(WList * list)
{
    while (w_list_prev(list)) {
        list = w_list_prev(list);
    }
    return list;
}

WList *w_list_last(WList * list)
{
    while (w_list_next(list)) {
        list = w_list_next(list);
    }
    return list;
}


WList *w_list_append(WList * list, void *data)
{
    WList *ele = w_list_alloc(data);
    WL_RETURN_VAL_IF_FAIL(ele != NULL, list);

    if (list == NULL) {
        /* NULL is a empty list */
        return ele;
    }

    WList *last = w_list_last(list);
    last->next = ele;
    ele->prev = last;

    return list;
}

WList *w_list_insert(WList * list, void *data, int position)
{
    if (position < 0 || list == NULL) {
        /* if position <0, append data to the end of the list */
        /* if list == NULL, whatever position is */
        return w_list_append(list, data);
    }
    int i = 0;
    WList *ptr = list;
    while (i < position && ptr) {
        i++;
        ptr = w_list_next(ptr);
    }
    if (ptr == NULL) {
        return w_list_append(list, data);
    }

    WList *ele = w_list_alloc(data);
    WL_RETURN_VAL_IF_FAIL(ele != NULL, list);

    /* insert data before ptr */
    if (w_list_prev(ptr) == NULL) {
        /* insert data to the first of list */
        ele->next = ptr;
        ptr->prev = ele;
        return ele;
    }
    ptr->prev->next = ele;
    ele->next = ptr;
    ele->prev = ptr->prev;
    ptr->prev = ele;
    return list;
}

void w_list_foreach(WList * list, WForeachFunc func, void *user_data)
{
    WL_RETURN_IF_FAIL(list != NULL);

    while (list) {
        /* call function for each element */
        func(list->data, user_data);
        list = w_list_next(list);
    }
}

void w_list_free(WList * list)
{
    WL_RETURN_IF_FAIL(list != NULL);

    WList *lp = w_list_next(list);
    while (list) {
        lp = w_list_next(list);
        free(list);
        list = lp;
    }
}

void w_list_free_full(WList * list, WListDestroy destroy)
{
    WL_RETURN_IF_FAIL(list != NULL);

    WList *lp = w_list_next(list);
    while (list) {
        lp = w_list_next(list);
        destroy(list->data);
        free(list);
        list = lp;
    }
}

WList *w_list_find_custom(WList * list, WCompareFunc func, const void *b)
{
    WL_RETURN_VAL_IF_FAIL(list != NULL, NULL);

    while (list) {
        if (func(list->data, b) == 0) {
            return list;
        }
        list = w_list_next(list);
    }
    return NULL;
}

WList *w_list_find(WList * list, void *data)
{
    WL_RETURN_VAL_IF_FAIL(list != NULL, NULL);
    while (list) {
        if (list->data == data) {
            return list;
        }
        list = w_list_next(list);
    }
    return NULL;
}

static WList *w_list_remove_internal(WList * list, void *data,
                                     WListDestroy destroy)
{
    WL_RETURN_VAL_IF_FAIL(list != NULL, NULL);

    WList *rm = w_list_find(list, data);
    if (rm == NULL) {           /* not find */
        return list;
    }
    if (destroy) {
        destroy(rm->data);
    }
    WList *prev = w_list_prev(rm);
    WList *next = w_list_next(rm);
    if (prev == NULL) {
        free(rm);
        return next;
    }
    prev->next = next;
    if (next != NULL) {
        next->prev = prev;
    }
    free(rm);
    return list;
}

WList *w_list_remove(WList * list, void *data)
{
    return w_list_remove_internal(list, data, NULL);
}

WList *w_list_remove_full(WList * list, void *data, WListDestroy destroy)
{
    return w_list_remove_internal(list, data, destroy);
}

WList *w_list_alloc(void *data)
{
    WList *list = (WList *) malloc(sizeof(WList));
    WL_RETURN_VAL_IF_FAIL(list != NULL, NULL);
    list->prev = list->next = NULL;
    list->data = data;
    return list;
}
