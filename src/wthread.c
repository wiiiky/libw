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
#include "wthread.h"
#include <pthread.h>
#include <stdlib.h>


static pthread_key_t pkey;
static pthread_once_t ponce = PTHREAD_ONCE_INIT;

static void pthread_free(void *data)
{
    free(data);
}

static void pthread_init(void)
{
    (void) pthread_key_create(&pkey, pthread_free);
}

void *w_thread_data(unsigned int len)
{
    pthread_once(&ponce, pthread_init);
    void *data = pthread_getspecific(pkey);
    if (data == NULL) {
        data = malloc(len);
        (void) pthread_setspecific(pkey, data);
    }
    return data;
}
