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

#include "wstring.h"
#include "m4.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

char *w_strdup(const char *str)
{
    W_RETURN_VAL_IF_FAIL(str != NULL, NULL);
    return strdup(str);
}

char *w_strndup(const char *str, int n)
{
    W_RETURN_VAL_IF_FAIL(str != NULL, NULL);
    if (n < 0) {
        return strdup(str);
    }
    return strndup(str, n);
}

char *w_strdup_printf(const char *format, ...)
{
    W_RETURN_VAL_IF_FAIL(format != NULL, NULL);

    va_list vl;
    char buf[LARGE_BUF];

    va_start(vl, format);

    vsnprintf(buf, LARGE_BUF, format, vl);

    va_end(vl);

    return w_strdup(buf);
}

int w_strcmp0(const char *s1, const char *s2)
{
    if (s1 == NULL && s2 == NULL) {
        return 0;
    } else if (s1 == NULL) {
        return -1;
    } else if (s2 == NULL) {
        return 1;
    }
    return strcmp(s1, s2);
}

int w_isupper(char c)
{
    if (c >= 'A' && c <= 'Z') {
        return 1;
    }
    return 0;
}

char w_toupper(char c)
{
    return w_islower(c) ? (c - 'a' + 'A') : c;
}

int w_islower(char c)
{
    if (c >= 'a' && c <= 'z') {
        return 1;
    }
    return 0;
}

char w_tolower(char c)
{
    return w_isupper(c) ? (c - 'A' + 'a') : c;
}

/************************** WString ******************************/

struct _WString {
    char *data;
    unsigned int len;
    unsigned int allocated_len;
};

#define W_STRING_MIN    128

static inline unsigned int w_string_get_odd(WString * string)
{
    return string->allocated_len - string->len;
}

WString *w_string_new()
{
    WString *str = (WString *) malloc(sizeof(WString));
    str->data = (char *) malloc(sizeof(char) * W_STRING_MIN);
    str->len = 0;
    str->allocated_len = W_STRING_MIN;
    str->data[0] = '\0';

    return str;
}

WString *w_string_new_with_data(const char *data)
{
    WString *string = w_string_new();
    w_string_append(string, data);
    return string;
}

static inline void w_string_enlarge_internal(WString * string)
{
    string->allocated_len = string->allocated_len << 1;
    string->data = realloc(string->data, string->allocated_len);
}

static inline void w_string_enlarge(WString * string, unsigned int len)
{
    while (w_string_get_odd(string) <= len) {
        w_string_enlarge_internal(string);
    }
}

static inline void w_string_append_internal(WString * string,
                                            const char *data,
                                            unsigned int len)
{
    strncpy(string->data + string->len, data, len + 1);
    string->len += len;
}

static inline void w_string_append_char_internal(WString * string, char ch)
{
    string->data[string->len] = ch;
    string->len++;
}

const char *w_string_get_data(WString * string)
{
    return string->data;
}

unsigned int w_string_get_length(WString * string)
{
    return string->len;
}

void w_string_append(WString * string, const char *data)
{
    unsigned int len = strlen(data);
    w_string_enlarge(string, len);
    w_string_append_internal(string, data, len);
}

void w_string_append_char(WString * string, char ch)
{
    w_string_enlarge(string, 1);
    w_string_append_char_internal(string, ch);
}

char *w_string_free(WString * string)
{
    char *data = string->data;
    w_free(string);
    return data;
}

void w_string_free_full(WString * string)
{
    w_free(string->data);
    w_free(string);
}
