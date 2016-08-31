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
#if 1
    init_irq();
    emi_init();
    GPIOA_Irq_init(GPIO_EMI_IRQ_RX, EDGE_TRIGGER, LOW_FALLING_DETECT);
    canOpen(NULL, &OD_0_0_Data);
    __init_0();
#endif /* if 0 end*/
#if 0
    emi_init();
    m2p();
    //p2m();
    //dma_check_channel();
#endif /* if 0 end*/

#if 0
    init_irq();                                 /* 系统中断初始化。只需要调用一次 */
    
    can_init(MOD_WK, ACR, AMR, CAN_BAUDRATE);    /* 初始化can控制器 */
    canOpen(NULL, &OD_0_0_Data);
    __init_0();                                 /* 初始化canopen */

#if 0
    eMBInit(MB_RTU, MB_SLAVE_ADDRESS, 0, MB_BAUDRATE, MB_PAR_NONE);    /* 初始化modbus */
    eMBEnable();

    timer_init(TIMER1, (void *)eMBPoll);
    timer_config(TIMER1, 500000);               /* 每500ms轮询一次embpoll */
    timer_start(TIMER1);
#endif /* if 0 end*/
#endif /* if 0 end*/

#if 0
    u8 w_data[1000];
    u8 r_data[1000];
    u8 i;

    emi_init();

    for(i=0;i<200;i++)
    {
        w_data[i] = i;
        r_data[i] = 0;
    }

#if 0
    w_data[0] = 0x21;
    w_data[1] = 0x03;
    w_data[2] = 0x00;
    w_data[3] = 0x2;
    w_data[4] = 0x00;
    w_data[5] = 0x81;
#endif /* if 0 end*/

    while (1)
    {
#if 0
        emi_write_array(FPGA_BASE_ADDR_1, 0, w_data, 200);
        mdelay(500);
#endif /* if 0 end*/
#if 0
        emi_read_array(FPGA_BASE_ADDR_1, 0, r_data, 200);
        mdelay(500);
#endif /* if 0 end*/
#if 0
        for (i=0;i<100;i++)
        {
            if (r_data[i] != i)
            {
                printf("i=%d, r_data = 0x%x\n", i, r_data[i]);
                break;
            }
        }
#endif /* if 0 end*/
        //memset(r_data, 0, 100);
        //mdelay(1);
    }
#endif /* if 0 end*/

    while (1);
	
	return 0;
}
