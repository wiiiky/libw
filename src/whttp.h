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
#ifndef __W_WHTTP_H__
#define __W_WHTTP_H__


/*
 * HTTP request method
 * 
 * GET,POST,PUT,HEAD,DELETE
 */
typedef enum {
    W_HTTP_GET = 1,
    W_HTTP_POST,
    W_HTTP_PUT,
    W_HTTP_HEAD,
    W_HTTP_DELETE,
} WHttpMethod;

/*
 * HTTP version
 * 0.9, 1.0, 1.1
 */
typedef enum {
    W_HTTP_0_9 = 1,
    W_HTTP_1_0,
    W_HTTP_1_1,
} WHttpVersion;

/*
 * the structures of WHttpHeaders, WHttpRequest are private
 */
typedef struct _WHttpHeaders WHttpHeaders;
typedef struct _WHttpRequest WHttpRequest;


/*
 * @description: create a new WHttpHeaders
 * 
 * @return:
 */
WHttpHeaders *w_http_headers_new();


/*
 * @description: destroy a WHttpHeaders
 */
void w_http_headers_free(WHttpHeaders * hdrs);


/*
 * @description: append a new Http Header with name and value to hdrs,
 *               if name already exists, its value is replaced.
 * 
 * @param hdrs: WHttpHeaders
 * @param name: the name of new Http Header
 * @param value: the value of new Http Header
 */
void w_http_headers_append(WHttpHeaders * hdrs,
                           const char *name, const char *value);

/*
 * @description: get the value of HTTP Header with name
 * 
 * @param name: the name of HTTP Header
 * 
 * @return: the value of HTTP Header if name found, or NULL
 */
const char *w_http_headers_get(WHttpHeaders * hdrs, const char *name);



#endif
