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
