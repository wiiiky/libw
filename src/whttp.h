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
 * the structures of WHttpHeaders, WHttpRequest and WHttpResponse are private
 */
typedef struct _WHttpHeaders WHttpHeaders;
typedef struct _WHttpRequest WHttpRequest;
typedef struct _WHttpResponse WHttpResponse;
typedef struct _WHttpBody WHttpBody;


/*
 * @description: creates a new WHttpHeaders
 * 
 * @return:
 */
WHttpHeaders *w_http_headers_new();


/*
 * @description: destroys a WHttpHeaders
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
 * @description: gets the value of HTTP Header with name
 * 
 * @param name: the name of HTTP Header
 * 
 * @return: the value of HTTP Header if name found, or NULL
 */
const char *w_http_headers_get(WHttpHeaders * hdrs, const char *name);


/*
 * WHttpBody
 */
WHttpBody *w_http_body_new();
WHttpBody *w_http_body_new_from_data(const char *data);
const char *w_http_body_get_data(WHttpBody * body);
unsigned int w_http_body_get_length(WHttpBody * body);


/*
 * @description: creates a new HTTP request with method, path and version
 * 
 * @param method: the HTTP request method, GET, POST, etc
 * @param path: the HTTP request path, / ,/index.html
 * @param version: the HTTP version, HTTP/1.1 HTTP/1.0
 * 
 * @return: the new WHttpRequest
 */
WHttpRequest *w_http_request_new(WHttpMethod method, const char *path,
                                 WHttpVersion version);

/*
 * @description: appends a new HTTP header to the WHttpRequest.
 *               If the header with name already exists, its value will be replaced
 * 
 * @param name: the name of HTTP header
 * @param value: the value of HTTP header
 */
void w_http_request_append(WHttpRequest * req, const char *name,
                           const char *value);


/*
 * @description: gets the HTTP headers of WHttpRequest
 * 
 */
WHttpHeaders *w_http_request_get_headers(WHttpRequest * req);

/*
 * @description: gets the method of WHttpRequest
 */
WHttpMethod w_http_request_get_method(WHttpRequest * req);

/*
 * @description: gets the path of WHttpRequest
 */
const char *w_http_request_get_path(WHttpRequest * req);

/*
 * @description: gets the version of HTTP
 */
WHttpVersion w_http_request_get_version(WHttpRequest * req);

/*
 * @description: parses the data to create WHttpRequest.
 * 
 * @param data: the string that contains HTTP request data
 * 
 * @return: a new WHttpRequest, or NULL on error
 */
WHttpRequest *w_http_request_new_from_data(const char *data);



#endif
