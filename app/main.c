#include <stdio.h>
#include "can_gsc3280.h"
#include "timer_gsc3280.h"
#include "gpio_gsc3280.h"
#include "uart_gsc3280.h"
#include <def.h>
#include "canfestival.h"
#include "OD_0_0.h"
#include "task.h"
#include "netconfig.h"

int __init_0();

uart_handler_t uart3_hook(char *src)
{
    int i = 0;
    for(i=0;i<UART_RX_BUFFER_LENGTH;i++)
    {
        if (src[i])
            uart_putc(UART3, src[i]);
        else
            break;
    }
    uart_putc(UART3, '\n');
}

int main_loop(void)
{
    init_irq();    /* 此函数只能调一次。否则会将已经注册的中断函数覆盖掉 */

	can_init(MOD_WK, ACR, AMR, CAN_BAUDRATE);
	
	canOpen(NULL, &OD_0_0_Data);
	

    __init_0();    /* 初始化canopen */

    uart_init(UART3, 115200);
    uart_request_irq(IRQ_UART3, uart3_hook);

    while (1)
    {

    }
	
	return 0;
}
