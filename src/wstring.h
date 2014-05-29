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
#ifndef __WL_WSTRING_H__
#define __WL_WSTRING_H__

/*
 * string functions
 */

/*
 * @description: duplicate a string
 * 
 * @param str: the source string
 * @return: a new allocated string or NULL if failed
 */
char *w_strdup(const char *str);

/*
 * @param n: size to duplicate
 * 
 * if n<0 return total string duplicate
 * if n==0 return a new allocated empty string ""
 * ...
 */
char *w_strndup(const char *str, int n);


/*
 * @description: create a formated string
 * 
 * @params : see printf document for details
 * 
 * @return: a new allocated string or NULL if failed
 *			XXX the length of return string
 *				must be less than 1024.
 */
char *w_strdup_printf(const char *format, ...);



#endif
