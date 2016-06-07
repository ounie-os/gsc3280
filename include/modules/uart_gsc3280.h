#ifndef __UART_H_
#define __UART_H_

#include <stdio.h>
#include <def.h>
#include <string.h>
#include <sysctl.h>
#include <cpu_regs.h>


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

typedef void (*uart_handler_t)(char *s);


void uart_init(unsigned int UART, unsigned int baud);
void uart_request_irq(unsigned int uart_irq_index, uart_handler_t rx_hook_func);
void uart_output_rxbuf(unsigned int uart_irq_index);
void uart_puts(unsigned int UART,char *s);
char uart_getc(unsigned int UART);
void uart_putc(unsigned int UART,unsigned char c);


#endif
