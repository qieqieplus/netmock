//
// Created by qieqie on 2021/1/27.
//

#ifndef NETWRAP_ENV_H
#define NETWRAP_ENV_H
struct net_if {
    char name[8];
    unsigned char ip[4];
    unsigned char mac[6];
};
#endif//NETWRAP_ENV_H
