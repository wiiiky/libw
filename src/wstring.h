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
#ifndef __W_WSTRING_H__
#define __W_WSTRING_H__

/*
 * string and memory functions
 */


#define w_malloc(size) malloc(size)
#define w_free(ptr) free(ptr)
#define w_realloc(ptr,size) realloc(ptr,size)

/*
 * @description: duplicates a string
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
 * @description: creates a formated string
 * 
 * @params : see printf document for details
 * 
 * @return: a new allocated string or NULL if failed
 *			XXX the length of return string
 *				must be less than 1024.
 */
char *w_strdup_printf(const char *format, ...);


/*
 * @description: compares two strings, handles NULL,
 *              compares two NULL pointers returns 0,
 *              sorts NULL pointer before non-NULL string.
 * 
 * @param s1: a C string or NULL
 * @param s2: another C string or NULL
 * @return: a signed integer that represents s1-s2
 */
int w_strcmp0(const char *s1, const char *s2);

/*
 * @description: determines whether a character is an ASCII upper case letter
 * 
 * @return: 1 if c is a upper case letter, 0 if not.
 */
int w_isupper(char c);

/*
 * @description: convert an ASCII letter to its upper case
 * 
 * @return: the upper case of the character. non-lowercase leter unchanged
 */
char w_toupper(char c);

/*
 * @description: determines whether a character is an ASCII lower case letter
 * 
 * @return: 1 if c is a lower case letter, 0 if not.
 */
int w_islower(char c);


/*
 * @description: convert an ASCII letter to its lower case
 * 
 * @return: the lower case of the character. non-uppercase leter unchanged
 */
char w_tolower(char c);


/********************************** WString *******************************/
typedef struct _WString WString;

WString *w_string_new();

WString *w_string_new_with_data(const char *data);

const char *w_string_get_data(WString * string);
unsigned int w_string_get_length(WString * string);

void w_string_append(WString * string, const char *data);
void w_string_append_char(WString * string, char ch);


#endif
