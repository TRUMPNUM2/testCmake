#ifndef __GET_IP_DOMAIN__
#define __GET_IP_DOMAIN__

#include <stdio.h>
#include "utarray.h"
#include "uthash.h"
#include "utlist.h"
#include "utringbuffer.h"
#include "utstack.h"
#include "utstring.h"
#include <sys/types.h>
#include <wait.h>
#include <errno.h>
#include "csapp.h"

#include <unistd.h>

#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#define MAC_SIZE    18
#define IP_SIZE     16

// function declare
int get_ip_by_domain(const char *domain, char *ip); // 根据域名获取ip
int get_local_mac(const char *eth_inf, char *mac);  // 获取本机mac
int get_local_ip(const char *eth_inf, char *ip);    // 获取本机ip

#endif
