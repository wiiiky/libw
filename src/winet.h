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
#ifndef __WL_WINET_H__
#define __WL_WINET_H__

#include <sys/types.h>
#include <sys/socket.h>

/*
 * network-related functions
 */

/*
 * wrapper of socket()
 */
int w_socket(int domain, int type, int protocol);

/*
 * wrapper of bind()
 */
int w_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);


/*
 * @description: bind a local port to given socket descriptor
 * 
 * @param sockfd: socket descriptor
 * @param doamin: AF_INET or AF_INET6
 * @param port: the port
 * 
 * @return: 0 on success, -1 on error.
 */
int w_bind_local(int sockfd, int domain, unsigned short port);


#endif
