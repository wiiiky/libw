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
#ifndef __WL_WQUEUE_H__
#define __WL_WQUEUE_H__

/*
 * WQueue, a queue that support multi-threads.
 * 			Can be used to transfer data in threads.
 */

/*
 * the structure of WQueue is private
 */
typedef struct _WQueue WQueue;

typedef void (*WQueueDestroy) (void *data);


/*
 * @description: create a new WQueue
 * 
 * @return: the pointer to the WQueue on success, or NULL on error
 */
WQueue *w_queue_new(void);

WQueue *w_queue_new_full(WQueueDestroy destroy);


/*
 * @description: set the destroy function for data that WQueue holds.
 *               Not need to hold the lock
 * 
 * @param destroy: the destroy function for data
 */
void w_queue_set_destroy(WQueue * queue, WQueueDestroy destroy);

/*
 * @description: increases the reference count of WQueue by 1, do not need to hold the lock
 */
void w_queue_ref(WQueue * queue);
/*
 * @description: decreases the reference count of WQueue by 1,
 *              if the count went to 0, the queue is destroyed.
 */
void w_queue_unref(WQueue * queue);


/*
 * @description: destroy the queue anyway. No matter what the count of reference
 */
void w_queue_free(WQueue * queue);

/*
 * @description: lock the WQueue, if the queue is already locked, blocked unitl lock is released
 * 
 * @return: 1 on success, 0 on error
 */
int w_queue_lock(WQueue * queue);

/*
 * @description: unlock the WQueue
 * 
 * @return: 1 on success, 0 on error
 */
int w_queue_unlock(WQueue * queue);

/*
 * @description: try to lock the WQueue, won't blocked.
 *               If WQueue is not locked, this function will lock it and return 0,
 *               otherwise return error.
 * 
 * @return: 1 on success(hold the lock of WQueue), 0 on error
 */
int w_queue_trylock(WQueue * queue);

/*
 * @description: push data into queue,
 *               the lock of queue must be hold before calling this function
 *
 * @param data: the data pushed, not NULL
 */
void w_queue_push_unlocked(WQueue * queue, void *data);

/*
 * @description: push data into queue,
 *               this function will try to hold the lock of queue, so it may blocked
 *
 * @param data: the data pushed, not NULL
 */
void w_queue_push(WQueue * queue, void *data);


/* TODO */
void *w_queue_pop_unlocked(WQueue * queue);
void *w_queue_pop(WQueue * queue);
void *w_queue_try_pop_unlocked(WQueue * queue);
void *w_queue_try_pop(WQueue * queue);


#endif
