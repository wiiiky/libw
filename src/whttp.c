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
#include "whttp.h"
#include "whashtable.h"
#include "m4.h"
#include "wstring.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>


struct _WHttpHeaders {
    WHashTable *headers;
};

struct _WHttpBody {
    WString *data;
};

struct _WHttpRequest {
    WHttpMethod method;
    char *path;
    WHttpVersion version;
    WHttpHeaders *hdrs;
    WHttpBody *body;
};

struct _WHttpResponse {
    WHttpVersion version;
    uint32_t status;
    char *phrase;
    WHttpHeaders *hdrs;
    WHttpBody *body;
};

/**************************** WHttpHeaders ***********************************/

/*
 * ignore the case of characters
 */
static int w_str_equal_case(const void *s1, const void *s2)
{
    return strcasecmp((const char *) s1, (const char *) s2);
}

static unsigned int w_str_hash_case(const void *data)
{
    const char *s = (const char *) data;
    unsigned int h = 0;
    while (*s) {
        h = (h << 3) + w_tolower(*s);
        s++;
    }
    return h;
}

WHttpHeaders *w_http_headers_new()
{
    /*
     * Is 5 (31 buckets) is a good default ? FIXME
     */
    WHttpHeaders *hdrs = malloc(sizeof(WHttpHeaders));
    if (W_UNLIKELY(hdrs == NULL)) {
        return NULL;
    }
    hdrs->headers =
        w_hash_table_new(5, w_str_hash_case, w_str_equal_case, free, free);
    if (W_UNLIKELY(hdrs->headers == NULL)) {
        free(hdrs);
        return NULL;
    }
    return hdrs;
}

void w_http_headers_free(WHttpHeaders * hdrs)
{
    W_RETURN_IF_FAIL(hdrs != NULL);
    w_hash_table_free_full(hdrs->headers);
    free(hdrs);
}

void w_http_headers_append(WHttpHeaders * hdrs,
                           const char *name, const char *value)
{
    W_RETURN_IF_FAIL(hdrs != NULL && name != NULL && value != NULL);

    w_hash_table_insert(hdrs->headers, w_strdup(name), w_strdup(value));
}

const char *w_http_headers_get(WHttpHeaders * hdrs, const char *name)
{
    W_RETURN_VAL_IF_FAIL(hdrs != NULL && name != NULL, NULL);

    return (const char *) w_hash_table_find(hdrs->headers, name);
}

/***************************** WHttpBody ************************************/
WHttpBody *w_http_body_new()
{
    WHttpBody *body = (WHttpBody *) malloc(sizeof(WHttpBody));
    body->data = w_string_new();
    return body;
}

WHttpBody *w_http_body_new_from_data(const char *data)
{
    WHttpBody *body = (WHttpBody *) malloc(sizeof(WHttpBody));
    body->data = w_string_new_with_data(data);
    return body;
}

char *w_http_body_free(WHttpBody * body)
{
    char *data = w_string_free(body->data);
    w_free(body);
    return data;
}

void w_http_body_free_full(WHttpBody * body)
{
    w_string_free_full(body->data);
    w_free(body);
}

const char *w_http_body_get_data(WHttpBody * body)
{
    return w_string_get_data(body->data);
}

unsigned int w_http_body_get_length(WHttpBody * body)
{
    return w_string_get_length(body->data);
}


/***************************** WHttpRequest **********************************/
WHttpRequest *w_http_request_new(WHttpMethod method, const char *path,
                                 WHttpVersion version)
{
    WHttpRequest *req = (WHttpRequest *) malloc(sizeof(WHttpRequest));
    req->method = method;
    req->path = strdup(path);
    req->version = version;
    req->hdrs = w_http_headers_new();
    req->body = w_http_body_new();
    return req;
}

void w_http_request_free(WHttpRequest * req)
{
    w_free(req->path);
    w_http_headers_free(req->hdrs);
    w_http_body_free_full(req->body);
    w_free(req);
}

void w_http_request_append(WHttpRequest * req, const char *name,
                           const char *value)
{
    W_RETURN_IF_FAIL(req != NULL && name != NULL && value != NULL);

    w_http_headers_append(req->hdrs, name, value);
}

WHttpHeaders *w_http_request_get_headers(WHttpRequest * req)
{
    W_RETURN_VAL_IF_FAIL(req != NULL, NULL);
    return req->hdrs;
}

WHttpBody *w_http_request_get_body(WHttpRequest * req)
{
    return req->body;
}

const char *w_http_request_get_body_data(WHttpRequest * req)
{
    return w_http_body_get_data(req->body);
}

unsigned int w_http_request_get_body_length(WHttpRequest * req)
{
    return w_http_body_get_length(req->body);
}

WHttpMethod w_http_request_get_method(WHttpRequest * req)
{
    return req->method;
}

const char *w_http_request_get_path(WHttpRequest * req)
{
    return req->path;
}

WHttpVersion w_http_request_get_version(WHttpRequest * req)
{
    return req->version;
}

WHttpRequest *w_http_request_new_from_data(const char *data)
{
    /* TODO */
    return NULL;
}
