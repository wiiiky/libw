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

#ifndef __W_WLOG_H__
#define __W_WLOG_H__

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
 *               this function is not recommanded to use.
 *               use convenient macro like WDEBUG WERROR WVERBOSE or WLOG
 * 
 * @param type: the log type, verbose, debug or error
 * @param file: the source file name
 * @param line: the line number in the source file that gives out message
 * @param format: the message format, see printf document
 * @param ...: the paramters to insert into the format string
 */
void wlog(WLogType type, const char *file, int line, const char *format,
          ...);



/*
 * macros
 */
#define WLOG(type, format, ...) wlog((type),__FILE__,__LINE__,(format), __VA_ARGS__)
#define WDEBUG(format, ...)  WLOG(WLOG_DEBUG, format, __VA_ARGS__)
#define WERROR(format, ...)  WLOG(WLOG_ERROR, format, __VA_ARGS__)
#define WVERBOSE(format, ...) WLOG(WLOG_VERBOSE, format, __VA_ARGS__)

#endif
