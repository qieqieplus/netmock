//
// Created by qieqie on 2021/1/27.
//

#ifndef NETWRAP_NETMOCK_H
#define NETWRAP_NETMOCK_H

typedef int (*ioctl_fn)(int fd, unsigned long request, void *data);

int ioctl(int fd, unsigned long request, void *data);

#endif//NETWRAP_NETMOCK_H
