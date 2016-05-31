#include "lwip/init.h"
#include "lwip/netif.h"
#include "netconfig.h"

struct netif gsc3280_netif;

void lwip_stack_init(void)
{
    struct ip_addr ipaddr;
    struct ip_addr netmask;
    struct ip_addr gw;

    lwip_init();

    IP4_ADDR(&ipaddr, 192, 168, 2, 18);  		
    IP4_ADDR(&netmask, 255, 255, 255, 0);		
    IP4_ADDR(&gw, 192, 168, 2, 1);

    netif_add(&gsc3280_netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &ethernetif_input);

    netif_set_default(&gsc3280_netif);

    netif_set_up(&gsc3280_netif);
}
