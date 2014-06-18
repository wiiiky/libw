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
#include "wasyncqueue.h"
#include "wqueue.h"
#include "m4.h"
#include <stdlib.h>
#include <pthread.h>

struct _WAsyncQueue {
    WQueue *queue;              /* standard queue */
    pthread_mutex_t lock;       /* POSIX thread mutex */
    unsigned int ref;           /* reference count */
    WAsyncQueueDestroy destroy; /* the function used to free data hold by WAsyncQueue */
};


WAsyncQueue *w_async_queue_new(void)
{
    return w_async_queue_new_full(NULL);
}

WAsyncQueue *w_async_queue_new_full(WAsyncQueueDestroy destroy)
{
    WAsyncQueue *queue = (WAsyncQueue *) malloc(sizeof(WAsyncQueue));
    if (queue == NULL || pthread_mutex_init(&queue->lock, NULL) != 0) {
        /* fail to allocate the memory or initialize the lock */
        free(queue);
        return NULL;
    }
    queue->ref = 1;
    queue->queue = w_queue_new();
    queue->destroy = destroy;
    return queue;
}

void w_async_queue_set_destroy(WAsyncQueue * queue,
                               WAsyncQueueDestroy destroy)
{
    WL_RETURN_IF_FAIL(queue != NULL);
    queue->destroy = destroy;
}

void w_async_queue_ref(WAsyncQueue * queue)
{
    WL_RETURN_IF_FAIL(queue != NULL);
    queue->ref++;
}

void w_async_queue_unref(WAsyncQueue * queue)
{
    WL_RETURN_IF_FAIL(queue != NULL);
    if (--queue->ref == 0) {
        w_async_queue_free(queue);
    }
}

void w_async_queue_free(WAsyncQueue * queue)
{
    WL_RETURN_IF_FAIL(queue != NULL);
    w_queue_free_full(queue->queue, queue->destroy);
    pthread_mutex_destroy(&queue->lock);
    free(queue);
}

int w_async_queue_lock(WAsyncQueue * queue)
{
    return pthread_mutex_lock(&queue->lock) == 0;
}

int w_async_queue_unlock(WAsyncQueue * queue)
{
    return pthread_mutex_unlock(&queue->lock) == 0;
}

int w_async_queue_trylock(WAsyncQueue * queue)
{
    return pthread_mutex_trylock(&queue->lock) == 0;
}

void w_async_queue_push_unlocked(WAsyncQueue * queue, void *data)
{
    WL_RETURN_IF_FAIL(queue != NULL && data != NULL);
    w_queue_push(queue->queue, data);
}

void w_async_queue_push(WAsyncQueue * queue, void *data)
{
    WL_RETURN_IF_FAIL(queue != NULL && data != NULL);
    w_async_queue_lock(queue);
    w_async_queue_push_unlocked(queue, data);
    w_async_queue_unlock(queue);
}

void *w_async_queue_try_pop_unlocked(WAsyncQueue * queue)
{
    WL_RETURN_VAL_IF_FAIL(queue != NULL, NULL);
    return w_queue_pop(queue->queue);
}

void *w_async_queue_try_pop(WAsyncQueue * queue)
{
    void *data = NULL;
    w_async_queue_lock(queue);
    data = w_async_queue_pop_unlocked(queue);
    w_async_queue_unlock(queue);
    return data;
}

void *w_async_queue_pop_unlocked(WAsyncQueue * queue)
{
    WL_RETURN_VAL_IF_FAIL(queue != NULL, NULL);
    void *data = NULL;
    if (w_queue_length(queue->queue)) {
        /* data available */
        data = w_queue_pop(queue->queue);
    } else {
        /* no data available, blocked until new data pushed into the queue */
        /* TODO */
    }
    return data;
}
