#ifndef __SERIAL_H_
#define __SERIAL_H_

#include <types.h>
#include <stdio.h>
#include <console.h>
#include <sysctl.h>
#include <def.h>



#define GC_COM0_BASE 0xbc108000         
#define GC_COM1_BASE 0xbc109000         
#define GC_COM2_BASE 0xbc10a000         
#define GC_COM3_BASE 0xbc10b000         
#define GC_COM4_BASE 0xbc10c000         
#define GC_COM5_BASE 0xbc10d000         
#define GC_COM6_BASE 0xbc10e000         
#define GC_COM7_BASE 0xbc10f000         

#define GC_COM_DATA	0x00
#define GC_COM_IER	0x01
#define GC_COM_IIR	0x02
#define GC_COM_GC	0x02
#define GC_COM_LCR	0x03
#define GC_COM_MCR	0x04
#define GC_COM_LSR	0x05
#define GC_COM_MSR	0x06

#define ref_clk 12000000

#define UART_FOR_DEBUG 0

#define GC_COM_BASE GC_COM0_BASE

#define UART_SET(idx, value) writeb(value, GC_COM_BASE + idx)
#define UART_GET(idx) readb(GC_COM0_BASE + idx)

//#define readl(addr) *(volatile unsigned int *)(addr)
//#define writel(value,addr) *(volatile unsigned int *)(addr)=value

volatile unsigned int *sysctl_clken0=(volatile unsigned int*)(SYSCTL_MOD_CTL0);
volatile unsigned int *sysctl_clken1=(volatile unsigned int*)(SYSCTL_MOD_CTL1);
volatile unsigned int *sysctl_iomux0=(volatile unsigned int*)(SYSCTL_IOMUX_CFG0);

void serial_putc(u8 c);
void serial_puts(u8 *s);
u8 serial_getc(volatile u8 *c);
static void serial_gets(volatile u8 *buf);
static void serial_flush(u8 sel);
//static char uart_getc(void);
u32 serial_set(u32 baud);

Console console_serial = {"console_serial", (void *)serial_putc, (void *)serial_puts, serial_getc, (void *)serial_gets, (void *)serial_flush};

void init_serial(void)
{
        register_console(&console_serial);
	*sysctl_clken1=*sysctl_clken1|(1 << 4);
	*sysctl_clken0=*sysctl_clken0|(1 << (14 + UART_FOR_DEBUG));
	switch(UART_FOR_DEBUG){
		case 0:
		case 1:
		case 2:
		case 3:
			*sysctl_iomux0=*sysctl_iomux0|(1 << (3 + UART_FOR_DEBUG));
			break;
		case 4:
			*sysctl_iomux0=*sysctl_iomux0|(1 << (4 + UART_FOR_DEBUG));
			break;
		case 5:
			*sysctl_iomux0=*sysctl_iomux0|(1 << (5 + UART_FOR_DEBUG));
			*sysctl_iomux0=*sysctl_iomux0|(1 << (6 + UART_FOR_DEBUG));
			break;
		case 6:
		case 7:
			*sysctl_iomux0=*sysctl_iomux0|(1 << (7 + UART_FOR_DEBUG));
			break;
		default:
			break;
	}
}
/*
void writel(unsigned int addr,unsigned value)
{
	volatile unsigned char  *pt=(volatile unsigned char*)addr;
	*pt=value;
}*/

u32 serial_set(u32 baud)
{
	u32 freq;
	u32 M,N,NO,pll_rate,dll,ahb,apb;
	freq=readl(SYSCTL_PLL_FREQ);
	M=freq&0x7f;
	N=(freq>>7)&0xf;
#if 0
	NO=(freq>>11)&0x2;
	NO=((NO==0)?1:(2<<NO));
	pll_rate=ref_clk*M/(N*NO);
#else
	u32 OD1,OD0;
	OD1=(freq>>12)&0x1;
	OD0=(freq>>11)&0x1;
	NO=1<<(OD1*2+OD0);
	pll_rate=ref_clk*2*M/(N*NO);
#endif
	writel(0x1,(SYSCTL_CLKDIV_UART0 + (UART_FOR_DEBUG << 3)));
	ahb=readl(SYSCTL_CLKDIV_AHB);
	apb=readl(SYSCTL_CLKDIV_APB);
	
	switch(UART_FOR_DEBUG){
		case 0:
		case 1:
		case 2:
			dll=pll_rate/((ahb+1)*(apb+1)*2*8*baud);
			break;
		case 3:
		case 4:
		case 5:
			dll=pll_rate/((ahb+1)*2*16*baud);
			break;
		case 6:
		case 7:
			dll=pll_rate/((ahb+1)*(apb+1)*2*16*baud);
			//dll=pll_rate/((ahb+1)*(apb+1)*16*baud);
			break;
		default:
			break;
	}

	writeb(0x80,GC_COM_BASE+LCR);
	writeb(dll&0xff,GC_COM_BASE+DLL);
	writeb((dll>>8)&0xff,GC_COM_BASE+DLH);
	writeb(0x3,GC_COM_BASE+LCR);
	writeb(0x47,GC_COM_BASE+FCR);
	return 0;
}
/*
u32 serial_transfer(volatile void *base)
{
    u32 i = 0;
    while (!(UART_GET(0x5) & 0x01));
    while (!serial_getc((u8 *)base+i++))
    {
	;	//serial_putc(((u8 *)(base))[i-1]);
    }
    return i;
}
*/
void serial_putc(u8 c)
{
	u32 timeout=1000000;
	volatile unsigned char *lsr=(volatile unsigned char*)(GC_COM_BASE+5);
	unsigned char status;
	volatile unsigned char *sdata=(volatile unsigned char *)(GC_COM_BASE);
	while(timeout--){
		status=*lsr;
		if(status&0x20)
		break;
	}
	if(timeout)
		*sdata=c;
}

void serial_puts(u8 *s)
{
    	while(*s)
	{
		if(*s=='\n')
			serial_putc('\r');
		serial_putc(*s++);
	}
}

u8 serial_getc(volatile u8 *c)
{
	int timeout=1000000;
	volatile unsigned char *lsr=(volatile unsigned char*)(GC_COM_BASE+LSR);
	volatile unsigned char status;
	volatile unsigned char *rdata=(volatile unsigned char *)(GC_COM_BASE);
	while(timeout--){
		status=*lsr;
		if(status&0x01)
		break;
	}
	if(timeout>0){
		*c=*rdata;
		return 0;
	}
	else
		return 1;
}

static void serial_gets(volatile u8 *buf)
{
    int i = 0;
    u8 timeout = 0;
    do
    {
	timeout = serial_getc(buf+i);
	if (timeout)
	    continue;
    }while(buf[i++] != '\n');
    buf[i-1] = 0;
}

static void serial_flush(u8 sel)
{
    if (sel == IN)
	UART_SET(GC_COM_GC, 0x02);
    else if (sel == OUT)
	UART_SET(GC_COM_GC, 0x04);
}
/*
static char uart_getc(void)
{
	int timeout=1000000;
	volatile unsigned char *lsr=(volatile unsigned char *)(GC_COM_BASE+LSR);
	unsigned char status;
	volatile unsigned char *rdata=(volatile unsigned char *)(GC_COM_BASE);
	unsigned data=0;
	while(timeout--)
	{
		status=*lsr;
		if(status&0x01)
			break;
	}
	if(timeout>0)
	{
		data=*rdata;
		return data;
	}
	else
		return 0;
}

static char* uart_gets(char *buf)
{
	int i=0;
	do
	{
		buf[i]=uart_getc();
		if(buf[i])
			continue;
	}while(buf[i++]!='\n');
	return buf;
}*/

void mdelay(int t);
#endif

