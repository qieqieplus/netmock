//
// Created by qieqie on 2021/1/27.
//

#include "env.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void init() __attribute__((constructor));
struct net_if config;

void mac2byte(unsigned char *to, const char *from) {
    sscanf(from, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &to[0], &to[1], &to[2],
           &to[3], &to[4], &to[5]);
}

void ip2byte(unsigned char *to, const char *from) {
    sscanf(from, "%hhu.%hhu.%hhu.%hhu",
           &to[0], &to[1], &to[2], &to[3]);
}

void init() {
    char *vif, *vmac, *vip;

    if ((vif = getenv("VIF")) == NULL) {
        vif = "en0";
    }
    if ((vmac = getenv("VMAC")) == NULL) {
        vmac = "ff:ff:ff:ff:ff:ff";
    }
    if ((vip = getenv("VIP")) == NULL) {
        vip = "127.0.0.1";
    }

    strncpy(config.name, vif, sizeof(config.name));
    mac2byte(config.mac, vmac);
    ip2byte(config.ip, vip);
}
