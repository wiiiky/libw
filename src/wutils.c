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
#include "wutils.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/capability.h>


int w_have_capabilities(uint32_t cap)
{
    struct __user_cap_header_struct hdrp = {
        _LINUX_CAPABILITY_VERSION_1,    /* XXX */
        getpid()
    };
    struct __user_cap_data_struct datap;

    if (capget(&hdrp, &datap)) {
        return 0;
    }

    if (datap.effective & cap ||
        datap.permitted & cap || datap.inheritable & cap) {
        return 1;
    }
    return 0;
}


void w_sudo(int argc, char **argv)
{
    if (w_have_capabilities(CAP_NET_RAW)) {
        return;
    }

    int len = argc + 2;
    char **args = (char **) malloc(sizeof(char *) * len);
    args[0] = "-S";
    int i;
    for (i = 0; i < argc; i++) {
        args[i + 1] = argv[i];
    }
    args[len - 1] = NULL;
    execvp("sudo", args);

    /* ERROR */
    fprintf(stderr, "Fatal Error!!!\n");
    exit(-1);
}
