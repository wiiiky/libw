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


#ifndef __WL_M4_H__
#define __WL_M4_H__

#define WL_LIKELY(x) __builtin_expect(!!(x),1)
#define WL_UNLIKELY(x) __builtin_expect(!!(x),0)


#define STMT_START  do{
#define STMT_EDN	}while(0)

#define WL_RETURN_VAL_IF_FAIL(expr,val) STMT_START if(!(expr))\
							{return (val);} STMT_EDN

#define WL_RETURN_IF_FAIL(expr) STMT_START if(!(expr))\
							{return;} STMT_EDN

#endif
