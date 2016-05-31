#ifndef __NET_CONFIG_H__
#define __NET_CONFIG_H__

#include "lwip/err.h"
#include "lwip/netif.h"

extern void ethernetif_input(struct netif *netif);
extern err_t ethernetif_init(struct netif *netif);
void lwip_stack_init(void);

#endif
