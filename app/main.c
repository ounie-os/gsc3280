#include <stdio.h>
#include "can_gsc3280.h"
#include "timer_gsc3280.h"
#include <def.h>
#include "canfestival.h"
#include "OD_0_0.h"

int __init_0();



int main_loop(void)
{
    init_irq();    /* 此函数只能调一次。否则会将已经注册的中断函数覆盖掉 */

	can_init(MOD_WK, ACR, AMR, CAN_BAUDRATE);
	
	canOpen(NULL, &OD_0_0_Data);
	
    generic_timer_init(TIMER3);

    __init_0();
    

    while (1)
    {

    }
	
	return 0;
}
