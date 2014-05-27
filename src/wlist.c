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


WList *w_list_append(WList * list, void *data)
{
	WList *ele = w_list_alloc(data);
	WL_RETURN_VAL_IF_FAIL(ele != NULL, list);

	return list;
}


WList *w_list_alloc(void *data)
{
	WList *list = (WList *) malloc(sizeof(WList));
	WL_RETURN_VAL_IF_FAIL(list != NULL, NULL);
	list->prev = list->next = NULL;
	list->data = data;
	return list;
}
