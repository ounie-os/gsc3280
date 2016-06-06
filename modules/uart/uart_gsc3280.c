#include "uart_gsc3280.h"

static unsigned int freq,pll_rate,dll,ahb,apb;
static unsigned char uart3_rx_buf[UART_RX_BUFFER_LENGTH];
static unsigned char uart4_rx_buf[UART_RX_BUFFER_LENGTH];


static void uart_get_pll(void)
{
	u32 M,N,NO,OD1,OD0;
	freq=readl(SYSCTL_PLL_FREQ);
	M=freq&0x7f;
	N=(freq>>7)&0xf;
	OD1=(freq>>12)&0x1;
	OD0=(freq>>11)&0x1;
	NO=1<<(OD1*2+OD0);
	pll_rate=ref_clk*2*M/(N*NO);
	ahb=readl(SYSCTL_CLKDIV_AHB);
	apb=readl(SYSCTL_CLKDIV_APB);
}

static int uart_set_dll(unsigned int UART,unsigned int baud)
{	
	if(UART==UART0)
	{
		sysctl_mod_enable(SYSCTL_MOD_UART0);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART0);
		writel(0x1,SYSCTL_CLKDIV_UART0);
		dll=pll_rate/((ahb+1)*(apb+1)*2*8*baud);
		printf("uart0\n");
	}
	else if(UART==UART1)
	{
		sysctl_mod_enable(SYSCTL_MOD_UART1);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART1);
		writel(0x1,SYSCTL_CLKDIV_UART1);
		dll=pll_rate/((ahb+1)*(apb+1)*2*8*baud);
		printf("uart1\n");
	}
	else if(UART==UART2)
	{
		sysctl_mod_enable(SYSCTL_MOD_UART2);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART2);
		writel(0x1,SYSCTL_CLKDIV_UART2);
		dll=pll_rate/((ahb+1)*(apb+1)*2*8*baud);
		printf("uart2\n");
	}
	else if(UART==UART3)
	{
		sysctl_mod_enable(SYSCTL_MOD_UART3);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART3_1);
		writel(0x1,SYSCTL_CLKDIV_UART3);
		dll=pll_rate/((ahb+1)*2*8*baud);
		printf("uart3\n");
	}
	else if(UART==UART4)
	{
		sysctl_mod_enable(SYSCTL_MOD_UART4);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART4_1);
		writel(0x1,SYSCTL_CLKDIV_UART4);
		dll=pll_rate/((ahb+1)*2*8*baud);
		printf("uart4\n");
	}
	else if(UART==UART5)
	{
		sysctl_mod_enable(SYSCTL_MOD_UART5);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART5);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART5_TXE1);
		writel(0x1,SYSCTL_CLKDIV_UART5);
		dll=pll_rate/((ahb+1)*2*8*baud);
		printf("uart5\n");
	}
	else if(UART==UART6)
	{
		sysctl_mod_enable(SYSCTL_MOD_UART6);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART6);
		writel(0x1,SYSCTL_CLKDIV_UART6);
		dll=pll_rate/((ahb+1)*(apb+1)*2*16*baud);
	}
	else if(UART==UART7)
	{
		sysctl_mod_enable(SYSCTL_MOD_UART7);
		sysctl_iomux_enable(SYSCTL_IOMUX_UART7);
		writel(0x1,SYSCTL_CLKDIV_UART7);
		dll=pll_rate/((ahb+1)*(apb+1)*2*16*baud);
		printf("uart7\n");
	}
	else 
	{
		printf("UART select error,plese select UART from 0 to 7\n");
		return -1;
	}

	writeb(0x80,UART+LCR);
	writeb(dll&0xff,UART+DLL);
	writeb((dll>>8)&0xff,UART+DLH);
	writeb(0x3,UART+LCR);
	writeb(0x47,UART+FCR);
	return 0;
}

void uart_putc(unsigned int UART,unsigned char c)
{
	u32 timeout=1000000;
	volatile unsigned char *lsr=(volatile unsigned char*)(UART+LSR);
	unsigned char status;
	volatile unsigned char *sdata=(volatile unsigned char *)(UART);
	while(timeout--)
	{
		status=*lsr;
		if (status & 0x20)
		    break;
	}
	if(timeout)
		*sdata=c;
}

void uart_puts(unsigned int UART,char *s)
{
    while(*s)
	{
		if(*s=='\n')
			uart_putc(UART,'\r');
		uart_putc(UART,*s++);
	}
}

char uart_getc(unsigned int UART)
{
	int timeout=1000000;
	volatile unsigned char *lsr=(volatile unsigned char *)(UART+LSR);
	unsigned char status;
	volatile unsigned char *rdata=(volatile unsigned char *)(UART);
	unsigned data=0;
	while (timeout--)
	{
		status=*lsr;
		if (status&0x01)
			break;
	}
	if (timeout > 0)
	{
		data=*rdata;
		return data;
	}
	else
		return 0;
}

void uart_init(unsigned int UART,unsigned int baud)
{
	uart_get_pll();
	uart_set_dll(UART, baud);	
}

void uart_enable_rx_irq(unsigned int UART)
{
    writeb(0x1, UART + IER);
}

void uart_disable_rx_irq(unsigned int UART)
{
    writeb(0x0, UART + IER);
}

static void handler_uart3(void *arg)
{
	unsigned char c=0,i=0;

    uart_handler_t func = (uart_handler_t)arg;
	
	c = uart_getc(UART3);
	while((c > 0) && (c != '\n') && (i < UART_RX_BUFFER_LENGTH - 1))
	{
		uart3_rx_buf[i] = c;
		c = uart_getc(UART3);
		i++;
	}
	uart3_rx_buf[i] = 0;

	if (NULL != func)
	{
	    func(&uart3_rx_buf[0]);
	}
	
}

static void handler_uart4(void *arg)
{
	unsigned char c=0,i=0;

	uart_handler_t func = (uart_handler_t)arg;
	
	c = uart_getc(UART4);
	while((c > 0) && (c != '\n') && (i < UART_RX_BUFFER_LENGTH - 1))
	{
		uart4_rx_buf[i] = c;
		c = uart_getc(UART4);
		i++;
	}
	uart4_rx_buf[i] = 0;
	
    if (NULL != func)
	{
	    func(&uart4_rx_buf[0]);
	}
}

void uart_request_irq(unsigned int uart_irq_index, uart_handler_t rx_hook_func)
{
    int ret = 0;
    switch (uart_irq_index)
    {
        case IRQ_UART3:
        {
            uart_enable_rx_irq(UART3);
            ret = request_irq(uart_irq_index, (void *)handler_uart3, (void *)rx_hook_func);
            if (ret < 0)
            {
                printf("request_irq uart3 fail\n");
                uart_disable_rx_irq(UART3);
            }
            break;
        }
        
        case IRQ_UART4:
        {
            uart_enable_rx_irq(UART4);
            ret = request_irq(uart_irq_index, (void *)handler_uart4, (void *)rx_hook_func);
            if (ret < 0)
            {
                printf("request_irq uart4 fail\n");
                uart_disable_rx_irq(UART4);
            }            
            break;
        }

        default:
        {
            printf("uart%d's irq not supported yet\n", (uart_irq_index - 12));
            break;
        }
    }
}

void uart_output_rxbuf(unsigned int uart_irq_index)
{
    int i = 0;
    switch (uart_irq_index)
    {
        case IRQ_UART3:
        {
            for(i=0;i<UART_RX_BUFFER_LENGTH;i++)
            {
                if (uart3_rx_buf[i])
                    uart_putc(UART3, uart3_rx_buf[i]);
                else
                    break;
            }
            uart_putc(UART3, '\n');
            break;
        }
        
        case IRQ_UART4:
        {
            for(i=0;i<UART_RX_BUFFER_LENGTH;i++)
            {
                if (uart4_rx_buf[i])
                    uart_putc(UART4, uart4_rx_buf[i]);
                else
                    break;
            }
            uart_putc(UART4, '\n');
            break;
        }

    }
}

void uart_send_string(unsigned int UART, char *src)
{
    uart_puts(UART, src);
}
