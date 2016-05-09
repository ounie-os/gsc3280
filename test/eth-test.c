#include <stdio.h>
#include <def.h>
#include "can_gsc3280.h"
#include "timer_gsc3280.h"
#include "gpio_gsc3280.h"
#include "gsc3280_mac.h"
#include "canfestival.h"
#include "OD_0_0.h"
#include "net.h"


static unsigned char FrameBuf[1500]=    
{        
    0x12,0x12,0x12,0x12,0x12,0x12,        
    0x22,0x22,0x22,0x22,0x22,0x22,        
    0x88,0xa4,0x0e,0x10    
};

void eth_send_test(void)
{
	int i;
	
	gsc3280_eth_init();

    for(i=0;i<1000;i++)
        gsc3280_mac_eth_tx(FrameBuf, 150);
}

int main_loop(void)
{
    eth_send_test();

    while (1)
    {

    }
	
	return 0;
}
