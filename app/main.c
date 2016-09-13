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
#include "mb.h"
#include "emi_gsc3280.h"
#include "dma_gsc3280.h"

#define MB_BAUDRATE         115200
#define MB_SLAVE_ADDRESS    1

int main_loop(void)
{

    init_irq();
#ifdef EMI_CAN
    emi_init();
    can_emi_init();
    gpio_init();
#else
    can_init(MOD_WK, ACR, AMR, CAN_BAUDRATE);
#endif
    canOpen(NULL, &OD_0_0_Data);
    __init_0();

    while (1)
    {
        can_loop_process();
    }

#if 0
    init_irq();                                 /* 系统中断初始化。只需要调用一次 */
    
    can_init(MOD_WK, ACR, AMR, CAN_BAUDRATE);    /* 初始化can控制器 */
    canOpen(NULL, &OD_0_0_Data);
    __init_0();                                 /* 初始化canopen */

    eMBInit(MB_RTU, MB_SLAVE_ADDRESS, 0, MB_BAUDRATE, MB_PAR_NONE);    /* 初始化modbus */
    eMBEnable();

    timer_init(TIMER1, (void *)eMBPoll);
    timer_config(TIMER1, 500000);               /* 每500ms轮询一次embpoll */
    timer_start(TIMER1);
#endif /* if 0 end*/	
	return 0;
}
