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


#ifndef __W_M4_H__
#define __W_M4_H__

#include "wlog.h"

#define W_LIKELY(x) __builtin_expect(!!(x),1)
#define W_UNLIKELY(x) __builtin_expect(!!(x),0)


#define STMT_START  do{
#define STMT_EDN	}while(0)

/*
 * #expr: convert expression ptr!=NULL to string "ptr!=NULL"
 */

#define W_RETURN_VAL_IF_FAIL(expr,val) STMT_START if(!(expr))\
							{WDEBUG("%s failed\n", #expr); return (val);} STMT_EDN

#define W_RETURN_IF_FAIL(expr) STMT_START if(!(expr))\
							{WDEBUG("%s failed\n", #expr); return;} STMT_EDN

#define LARGE_BUF  (1024)
#define MEDIUM__BUF   (256)
#define SMALL_BUF   (64)
#define TINY_BUF	(16)

#endif
