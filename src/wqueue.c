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
#include "wqueue.h"
#include "wlist.h"
#include "m4.h"
#include <stdlib.h>

struct _WQueue {
    WList *first;
    WList *last;
    unsigned int length;
};


WQueue *w_queue_new(void)
{
    WQueue *queue = (WQueue *) malloc(sizeof(WQueue));
    queue->first = NULL;
    queue->last = NULL;
    queue->length = 0;
    return queue;
}

unsigned int w_queue_length(WQueue * queue)
{
    return queue->length;
}

void w_queue_push(WQueue * queue, void *data)
{
    WL_RETURN_IF_FAIL(queue != NULL && data != NULL);
    WList *ele = w_list_alloc(data);
    if (queue->last) {
        queue->last->next = ele;
        ele->prev = queue->last;
        queue->last = ele;
    } else {
        /* the only element */
        queue->first = queue->last = ele;
    }
    queue->length++;
}

void *w_queue_pop(WQueue * queue)
{
    WL_RETURN_VAL_IF_FAIL(queue != NULL, NULL);

    void *data = NULL;
    if (queue->first) {
        WList *pop = queue->first;
        queue->first = w_list_next(queue->first);
        if (queue->first) {
            queue->first->prev = NULL;
        } else {
            queue->last = NULL;
        }
        data = w_list_data(pop);
        w_list_free1(pop);
        queue->length--;
    }
    return data;
}

void w_queue_free(WQueue * queue)
{
    w_queue_free_full(queue, NULL);
}

void w_queue_free_full(WQueue * queue, WQueueDestroy destroy)
{
    WL_RETURN_IF_FAIL(queue != NULL);

    w_list_free_full(queue->first, destroy);
    free(queue);
}
