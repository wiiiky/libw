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

#include "wlog.h"
#include "m4.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void wlog(WLogType type, const char *format, ...)
{
    WL_RETURN_IF_FAIL(format != NULL);

    va_list args;
    va_start(args, format);

    switch (type) {
    case WLOG_VERBOSE:
        break;
    case WLOG_DEBUG:
        fprintf(stderr, "Debug(%s:%d): ", __FILE__, __LINE__);
        break;
    case WLOG_ERROR:
        fprintf(stderr, "\033[01;31mError(%s:%d)\033[0m: ",
                __FILE__, __LINE__);
        break;
    default:
        break;
    }
    vfprintf(stderr, format, args);
}
