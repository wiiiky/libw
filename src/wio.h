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
#ifndef __WL_WIO_H__
#define __WL_WIO_H__

/*
 * wraper of read()
 */
int w_read(int fd, void *buf, unsigned int count);

/*
 * wraper of write() 
 */
int w_write(int fd, void *buf, unsigned int count);

/*
 * @description: check if fd is a socket or not
 * 
 * @return: if fd is socket, return 1. Otherwise 0.
 */
int w_is_fd_socket(int fd);

/*
 * @description: check if fd is a FIFO descriptor or not
 * 
 * @return: if fd is FIFO, return 1. Otherwise 0;
 */
int w_is_fd_fifo(int fd);


/*
 * @description: check if fd is ok to read (won't cause SIGPIPE) or not
 *
 * @return: return 1 if ok, otherwise 0
 */
int w_is_fd_ok_to_read(int fd);


/*
 * @description: read a line from file
 *				this function will cache data
 *
 * @param fd: the file descriptor
 * @param: the buffer 
 * @param: the buffer size
 *
 * @return: the size read
 */
int w_readline(int fd, void *buf, unsigned int count);


#endif
