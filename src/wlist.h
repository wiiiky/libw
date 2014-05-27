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

#ifndef __WL_WLIST_H__
#define __WL_WLIST_H__
/*
 * WList : double linked list
 */
typedef struct _WList WList;

struct _WList {
	WList *prev;
	WList *next;
	void *data;
};

/*
 * @description: The type of function passed to w_list_foreach
 * 
 * @param data: the data of element
 * @param user_data: user data passed to w_list foreach
 */
typedef void (*WForeachFunc) (void *data, void *user_data);

/*
 * @description: create a new element with data
 * 
 * @param data: the data for the new element
 * 
 * @return: a new allocated element
 */
WList *w_list_alloc(void *data);

/*
 * @description: create a new list without any element.
 * 
 * @return: NULL.
 */
WList *w_list_new();


/*
 * @description: get the first/last element of list
 * 
 * @param list: not NULL
 */
WList *w_list_first(WList * list);
WList *w_list_last(WList * list);


/*
 * @description: the previous/next element
 * @param list: not NULL
 */
#define w_list_next(list)   ((list)->next)
#define w_list_prev(list)   ((list)->prev)

/*
 * @description: append a new element with data to the end of the list.
 * 
 * @param list: a pointer to a WList.
 * @param data: the data for the new element.
 *
 * @return: the new start of the list.
 */
WList *w_list_append(WList * list, void *data);

/*
 * @description: insert a new element with data to the list 
 *				at the given position.
 * 
 * @param list: a pointer to a WList.
 * @param data: the data for the new element.
 * @param position: the position to insert.
 *					if position <0, data is append to the end of list.
 *					if position >=0, data is inserted into the position of list.
 * 
 * @return: the new start of the list
 */
WList *w_list_insert(WList * list, void *data, int position);


#endif
