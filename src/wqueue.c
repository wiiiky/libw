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
#include <pthread.h>

struct _WQueue {
    WList *list;                /* double-linked list */
    pthread_mutex_t lock;       /* POSIX thread mutex */
    unsigned int ref;           /* reference count */
    WQueueDestroy destroy;      /* the function used to free data hold by WQueue */
};


WQueue *w_queue_new(void)
{
    return w_queue_new_full (NULL);
}

WQueue *w_queue_new_full(WQueueDestroy destroy)
{
    WQueue *queue = (WQueue *) malloc(sizeof(WQueue));
    if (queue == NULL || pthread_mutex_init(&queue->lock, NULL) != 0) {
        /* fail to allocate the memory or initialize the lock */
        free(queue);
        return NULL;
    }
    queue->ref = 1;
    queue->list = NULL;
    queue->destroy = destroy;
    return queue;
}

void w_queue_set_destroy(WQueue * queue, WQueueDestroy destroy)
{
    WL_RETURN_IF_FAIL(queue != NULL);
    queue->destroy = destroy;
}

void w_queue_ref(WQueue * queue)
{
    WL_RETURN_IF_FAIL(queue != NULL);
    queue->ref++;
}

void w_queue_unref(WQueue * queue)
{
    WL_RETURN_IF_FAIL(queue != NULL);
    if (--queue->ref == 0) {
        w_queue_free(queue);
    }
}

void w_queue_free(WQueue * queue)
{
    WL_RETURN_IF_FAIL(queue != NULL);
    w_list_free_full(queue->list, queue->destroy);
    pthread_mutex_destroy(&queue->lock);
    free(queue);
}

int w_queue_lock(WQueue * queue)
{
    return pthread_mutex_lock(&queue->lock) == 0;
}

int w_queue_unlock(WQueue * queue)
{
    return pthread_mutex_unlock(&queue->lock) == 0;
}

int w_queue_trylock(WQueue * queue)
{
    return pthread_mutex_trylock(&queue->lock) == 0;
}

void w_queue_push_unlocked(WQueue * queue, void *data)
{
    WL_RETURN_IF_FAIL(queue != NULL && data != NULL);
    queue->list = w_list_append(queue->list, data);
}

void w_queue_push(WQueue * queue, void *data)
{
    WL_RETURN_IF_FAIL(queue != NULL && data != NULL);
    w_queue_lock(queue);
    w_queue_push_unlocked(queue, data);
    w_queue_unlock(queue);
}
