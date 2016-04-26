#ifndef _IO_H_
#define _IO_H_

#define readb(addr) (*(volatile unsigned char *)(addr))
#define readw(addr) ((*(volatile unsigned short *)(addr)))
#define readl(addr) ((*(volatile unsigned int *)(addr)))
#define __raw_readb readb
#define __raw_readw readw
#define __raw_readl readl

#define writeb(b,addr) (*(volatile unsigned char *)(addr)) = ((unsigned char)(b))
#define writew(b,addr) (*(volatile unsigned short *)(addr)) = ((unsigned short)(b))
#define writel(b,addr) (*(volatile unsigned int *)(addr)) = ((unsigned int)(b))
#define __raw_writeb writeb
#define __raw_writew writew
#define __raw_writel writel

//#define memset_io(a,b,c)	memset((void *)(a),(b),(c))
//#define memcpy_fromio(a,b,c)	memcpy((a),(void *)(b),(c))
//#define memcpy_toio(a,b,c)	memcpy((void *)(a),(b),(c))
#endif//_IO_H_

