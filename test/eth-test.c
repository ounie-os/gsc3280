#include <stdio.h>
#include <def.h>
#include "can_gsc3280.h"
#include "timer_gsc3280.h"
#include "gpio_gsc3280.h"
#include "gsc3280_mac.h"
#include "canfestival.h"
#include "OD_0_0.h"
#include "net.h"
#include "lwip/tcp.h"
#include "lwip/ip_addr.h"
#include "netif/etharp.h"


static int gpio_flag = 0;
#if 0
static u8 time_count = 0;

static unsigned char FrameBuf[1500]=    
{        
    0x12,0x12,0x12,0x12,0x12,0x12,        
    0x22,0x22,0x22,0x22,0x22,0x22,        
    0x88,0xa4,0x0e,0x10    
};

void eth_send_test(void)
{
	int i;
	
	//gsc3280_eth_init();

    for(i=0;i<10;i++)
        gsc3280_mac_eth_tx(FrameBuf, 150);
}
#endif /* if 0 end*/
	
static void timer0_handle(void)
{
    static u32 count = 0;

    count++;

    tcp_tmr();

    if (count >= 20)
    {
        count = 0;
        etharp_tmr();
    }

    if (gpio_flag)
    {
        gpio_flag = 0;
        GPIOA_Set_Value(31, 0);
    }
    else
    {
        gpio_flag = 1;
        GPIOA_Set_Value(31, 1);
    }
}

static void timer1_handle(void)
{
    lwip_stack_input();
}

int main_loop(void)
{
    init_irq();

    GPIO_Enable();

    GPIOA_Set_Dir(31, GPIO_OUTPUT);

    lwip_stack_init();

    timer_init(TIMER1, (void *)timer1_handle);
    timer_config(TIMER1, 1000);
    timer_init(TIMER0, (void *)timer0_handle);
    timer_config(TIMER0, 250000);
    timer_start(TIMER1);
    timer_start(TIMER0);

    while (1)
    {

    }
	
	return 0;
}
