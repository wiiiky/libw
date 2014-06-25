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
#ifndef __W_WASYNCQUEUE_H__
#define __W_WASYNCQUEUE_H__

/*
 * WAsyncQueue, a queue that is used for multi-threads communication.
 */

/*
 * the structure of WAsyncQueue is private
 */
typedef struct _WAsyncQueue WAsyncQueue;

typedef void (*WAsyncQueueDestroy) (void *data);


/*
 * @description: creates a new WAsyncQueue
 * 
 * @return: the pointer to the WAsyncQueue on success, or NULL on error
 */
WAsyncQueue *w_async_queue_new(void);

WAsyncQueue *w_async_queue_new_full(WAsyncQueueDestroy destroy);


/*
 * @description: return the length of WAsyncQueue
 * 
 * @return: the length of WAsyncQueue
 */
unsigned int w_async_queue_length(WAsyncQueue * queue);


/*
 * @description: sets the destroy function for data that WAsyncQueue holds.
 *               Not need to hold the lock
 * 
 * @param destroy: the destroy function for data
 */
void w_async_queue_set_destroy(WAsyncQueue * queue,
                               WAsyncQueueDestroy destroy);

/*
 * @description: increases the reference count of WAsyncQueue by 1, do not need to hold the lock
 */
void w_async_queue_ref(WAsyncQueue * queue);
/*
 * @description: decreases the reference count of WAsyncQueue by 1,
 *              if the count went to 0, the queue is destroyed.
 */
void w_async_queue_unref(WAsyncQueue * queue);


/*
 * @description: destroys the queue anyway. No matter what the count of reference
 */
void w_async_queue_free(WAsyncQueue * queue);

/*
 * @description: locks the WAsyncQueue, if the queue is already locked, blocked unitl lock is released
 * 
 * @return: 1 on success, 0 on error
 */
int w_async_queue_lock(WAsyncQueue * queue);

/*
 * @description: unlocks the WAsyncQueue
 * 
 * @return: 1 on success, 0 on error
 */
int w_async_queue_unlock(WAsyncQueue * queue);

/*
 * @description: tries to lock the WAsyncQueue, won't blocked.
 *               If WAsyncQueue is not locked, this function will lock it and return 0,
 *               otherwise return error.
 * 
 * @return: 1 on success(hold the lock of WAsyncQueue), 0 on error
 */
int w_async_queue_trylock(WAsyncQueue * queue);

/*
 * @description: pushes data into queue.
 *               The lock of queue must be hold before calling this function.
 *
 * @param data: the data pushed, not NULL
 */
void w_async_queue_push_unlocked(WAsyncQueue * queue, void *data);

/*
 * @description: pushes data into queue,
 *               this function will try to hold the lock of queue, so it may blocked
 *
 * @param data: the data pushed, not NULL
 */
void w_async_queue_push(WAsyncQueue * queue, void *data);

/*
 * @description: tries to pop data from queue. This function will return immediately.
 *               Must hold the lock before calling it.
 * 
 * @return: the pointer to the data if avaiable, or NULL if no data avaiable
 */
void *w_async_queue_try_pop_unlocked(WAsyncQueue * queue);

/*
 * @description: tries to pop data from queue. This function will return immediately.
 * 
 * @return: the pointer to the data if avaiable, or NULL if no data avaiable at present
 */
void *w_async_queue_try_pop(WAsyncQueue * queue);

/*
 * @description: tries to pop data from queue. If no data available at present,
 *               this function will block
 * 
 * @return : the pointer to the data, NULL on error
 */
void *w_async_queue_pop_unlocked(WAsyncQueue * queue);
void *w_async_queue_pop(WAsyncQueue * queue);


#endif
