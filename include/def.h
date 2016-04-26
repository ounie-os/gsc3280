#ifndef __DEF_H
#define __DEF_H

#include <types.h>
//#define u32 unsigned int
//#define u16 unsigned short

#define __raw_readl readl
#define __raw_writel writel


void static inline writel(unsigned int val,unsigned long reg)
{
	*(volatile unsigned int *)reg = val;
}


static inline unsigned int readl(unsigned long reg)
{
	unsigned int ret = 0;
	ret = *(volatile unsigned int *)reg;
	return ret;
}


void static inline writew(unsigned long reg,unsigned short val)
{
    *(volatile unsigned short *)reg = val;
}


static inline unsigned short readw(unsigned long reg)
{
    unsigned short ret = 0;
    ret = *(volatile unsigned short *)reg;
    return ret;
}

void static inline writeb(unsigned char val,unsigned long reg)
{
	*(volatile unsigned char *)reg = val;
}


static inline unsigned int readb(unsigned long reg)
{
	unsigned char ret = 0;
	ret = *(volatile unsigned char *)reg;
	return ret;
}

#endif
