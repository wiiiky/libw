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

#ifndef __WL_WLOG_H__
#define __WL_WLOG_H__

/*
 * WLog logs a message to the terminal
 */

typedef enum {
    WLOG_VERBOSE,
    WLOG_DEBUG,
    WLOG_ERROR,
} WLogType;

/*
 * @description: log an error or debug message
 * 
 * @param type: the log type, verbose, debug or error
 * @param format: the message format, see printf document
 * @param ...: the paramters to insert into the format string
 */
void wlog(WLogType type, const char *format, ...);

/*
 * macros
 */
#define WDEBUG(format, ...)  wlog(WLOG_DEBUG, format, __VA_ARGS__)
#define WERROR(format, ...)  wlog(WLOG_ERROR, format, __VA_ARGS__)
#define WVERBOSE(format, ...) wlog(WLOG_VERBOSE, format, __VA_ARGS__)

#endif
