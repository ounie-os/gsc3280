#include <stdio.h>
#include "can_gsc3280.h"
#include "timer_gsc3280.h"
#include "gpio_gsc3280.h"
#include <def.h>
#include "canfestival.h"
#include "OD_0_0.h"
#include "task.h"
#include "netconfig.h"

int __init_0();


int main_loop(void)
{
    init_irq();    /* 此函数只能调一次。否则会将已经注册的中断函数覆盖掉 */

	can_init(MOD_WK, ACR, AMR, CAN_BAUDRATE);
	
	canOpen(NULL, &OD_0_0_Data);
	
    generic_timer_init(TIMER3, (void *)systick_task);    /* 定时器中断中，调用systick_task函数 */

#if 0
    timer_setup_by_ms(4, TIMER3);    /* 开启定时器，4ms中断一次 */
#endif /* if 0 end*/

    __init_0();    /* 初始化canopen */

    lwip_stack_init();
    

    while (1)
    {

    }
	
	return 0;
}
