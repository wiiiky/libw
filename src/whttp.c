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


struct _WHttpHeaders {
    WHashTable *headers;
};


WHttpHeaders *w_httper_headers_new(void)
{
    /*
     * Is 5 (31 buckets) is a good default ? FIXME
     */
    WHttpHeaders *hdrs = malloc(sizeof(WHttpHeaders));
    if (W_UNLIKELY(hdrs == NULL)) {
        return NULL;
    }
    hdrs->headers =
        w_hash_table_new(5, w_str_hash, w_str_equal, free, free);
    if (W_UNLIKELY(hdrs->headers == NULL)) {
        free(hdrs);
        return NULL;
    }
    return hdrs;
}

void w_httper_headers_free(WHttpHeaders * hdrs)
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
