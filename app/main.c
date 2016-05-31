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
    init_irq();    /* �˺���ֻ�ܵ�һ�Ρ�����Ὣ�Ѿ�ע����жϺ������ǵ� */

	can_init(MOD_WK, ACR, AMR, CAN_BAUDRATE);
	
	canOpen(NULL, &OD_0_0_Data);
	
    generic_timer_init(TIMER3, (void *)systick_task);    /* ��ʱ���ж��У�����systick_task���� */

#if 0
    timer_setup_by_ms(4, TIMER3);    /* ������ʱ����4ms�ж�һ�� */
#endif /* if 0 end*/

    __init_0();    /* ��ʼ��canopen */

    lwip_stack_init();
    

    while (1)
    {

    }
	
	return 0;
}
