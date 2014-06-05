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
#include "winet.h"
#include <netinet/in.h>
#include <ifaddrs.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


int w_socket(int domain, int type, int protocol)
{
    int sockfd = socket(domain, type, protocol);

    return sockfd;
}

int w_bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int ret = bind(sockfd, addr, addrlen);
    return ret;
}


static int w_bind_local4(int sockfd, unsigned short port)
{
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    return w_bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
}

static int w_bind_local6(int sockfd, unsigned short port)
{
    struct sockaddr_in6 addr;
    addr.sin6_family = AF_INET6;
    addr.sin6_addr = in6addr_any;
    addr.sin6_port = htons(port);
    return w_bind(sockfd, (struct sockaddr *) &addr, sizeof(addr));
}

/*
 * @description: bind a local port to given socket descriptor
 * 
 * @param sockfd: socket descriptor
 * @param doamin: AF_INET or AF_INET6
 * @param port: the port
 * 
 * @return: 0 on success, -1 on error.
 */
int w_bind_local(int sockfd, int domain, unsigned short port)
{
    if (domain == AF_INET) {
        return w_bind_local4(sockfd, port);
    } else if (domain == AF_INET6) {
        return w_bind_local6(sockfd, port);
    }
    return -1;
}

int get_iface_ip(struct sockaddr *addr, socklen_t addrlen, char *iface,
                 int domain)
{
    if (addr == NULL || iface == NULL
        || (domain != AF_INET && domain != AF_INET6)) {
        return -1;
    }

    struct ifaddrs *ifap = NULL;
    int ret = -1;

    if (getifaddrs(&ifap)) {
        return ret;
    }

    struct ifaddrs *ifptr = ifap;
    while (ifptr) {
        if (strcmp(iface, ifptr->ifa_name) == 0 &&
            ifptr->ifa_addr != NULL &&
            ifptr->ifa_addr->sa_family == domain) {
            addr->sa_family = domain;
            memcpy(addr, ifptr->ifa_addr, addrlen);
            ret = 0;
            break;
        }
        ifptr = ifptr->ifa_next;
    }

    freeifaddrs(ifap);

    return ret;
}
