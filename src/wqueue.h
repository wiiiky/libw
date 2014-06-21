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
#ifndef __W_WQUEUE_H__
#define __W_WQUEUE_H__


/*
 * a standard queue data structure.
 */
typedef struct _WQueue WQueue;

/*
 * Why I have to define the same destroy function in every file! FIXME
 */
typedef void (*WQueueDestroy) (void *data);

/*
 * @description: creates a new queue
 */
WQueue *w_queue_new();

/*
 * @description: returns the length of queue
 */
unsigned int w_queue_length();


/*
 * @description: pushes data into the queue
 */
void w_queue_push(WQueue * queue, void *data);

/*
 * @description: removes the first element and return its data
 * 
 * @return: data hold by first element or NULL if queue is emptry
 */
void *w_queue_pop(WQueue * queue);


/*
 * @description: destroys queue, free memory that allocated for it
 */
void w_queue_free(WQueue * queue);
void w_queue_free_full(WQueue * queue, WQueueDestroy destroy);


#endif
