//
// Created by qieqie on 2021/1/27.
//

#include "netmock.h"
#include "env.h"
#include <dlfcn.h>
#include <net/if.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#ifndef RTLD_NEXT
#define RTLD_NEXT ((void *) -1l)
#endif

static ioctl_fn __ioctl = NULL;
extern struct net_if config;

void ip_addr_modify(void *data) {
    struct ifreq *req = (struct ifreq *) data;
    if (strcmp(req->ifr_name, config.name) == 0) {
        size_t offset = 2;
        for (size_t i = 0; i < 4; i++) {
            req->ifr_addr.sa_data[i + offset] = (char) config.ip[i];
        }
    }
}

void mac_addr_modify(void *data) {
    struct ifreq *req = (struct ifreq *) data;
    if (strcmp(req->ifr_name, config.name) == 0) {
        for (size_t i = 0; i < 6; i++) {
            req->ifr_hwaddr.sa_data[i] = (char) config.mac[i];
        }
    }
}

int ioctl(int fd, unsigned long request, ...) {
    char *msg;
    if (__ioctl == NULL) {
        __ioctl = (ioctl_fn) dlsym(RTLD_NEXT, "ioctl");
        if ((msg = dlerror()) != NULL) {
            fprintf(stderr, "ioctl: dlsym failed : %s\n", msg);
            fflush(stderr);
            exit(1);
        }
    }

    va_list args;
    void *data;

    va_start(args, request);
    data = va_arg(args, void *);
    va_end(args);

    int ret = __ioctl(fd, request, data);
    if (ret == 0) {
        switch (request) {
            case SIOCGIFHWADDR:
                mac_addr_modify(data);
                break;
            case SIOCGIFADDR:
                ip_addr_modify(data);
                break;
            default:;
        }
    }
    return ret;
}
