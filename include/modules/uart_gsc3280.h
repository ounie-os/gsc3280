#ifndef __UART_H_
#define __UART_H_

#include <stdio.h>
#include <def.h>
#include <string.h>
#include <sysctl.h>
#include <cpu_regs.h>
#include "interrupt.h"


#define UART0 0xbc108000
#define UART1 0xbc109000
#define UART2 0xbc10a000
#define UART3 0xbc10b000
#define UART4 0xbc10c000
#define UART5 0xbc10d000
#define UART6 0xbc10e000
#define UART7 0xbc10f000

#define ref_clk 12000000

#define UART_RX_BUFFER_LENGTH 1024
#define UART_IER_RDAIE  (1 << 0)
#define UART_IER_THREIE (1 << 1)

#define UART_IIR_RDA        (0xc4)
#define UART_IIR_TIMEOUT    (0xcc)
#define UART_IIR_THRE       (0xc2)


void uart_init(unsigned int UART, unsigned int baud);
char uart_getc(unsigned int UART);
void uart_putc(unsigned int UART,unsigned char c);
void uart_enable_irq(unsigned int UART, unsigned int tx_enable, unsigned int rx_enable);


#endif
