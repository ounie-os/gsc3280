#ifndef _EMI_APP_H_
#define _EMI_APP_H_

#include "types.h"
#include "can.h"

#define EMI_BASE_ADDR 0xbc04e000

#define EMI_CSSLR0_LOW      0x14
#define EMI_CSSLR1_LOW      0x18
#define EMI_CSSLR2_LOW      0x1c
#define EMI_SMSKR0          0x54
#define EMI_SMSKR1          0x58
#define EMI_SMSKR2          0x5c
#define EMI_CSALIAS0_LOW    0x74
#define EMI_SMTMGR_SET0     0x94
#define EMI_SMTMGR_SET1     0x98
#define EMI_SMTMGR_SET2     0x9c

#define SM_READ_PIPE(x) ((x) << 28)
#define READY_MODE(x)   ((x) << 26)
#define PAGE_SIZE(x)    ((x) << 24)
#define PAGE_MODE(x)    ((x) << 23)
#define T_PRC(x)        ((x) << 19)
#define T_BTA(x)        ((x) << 16)
#define T_WP(x)         ((x) << 10)
#define T_WR(x)         ((x) << 8)
#define T_AS(x)         ((x) << 6)
#define T_RC(x)         ((x) << 0)

#define FPGA_BASE_ADDR_0 0xbdc00000
#define FPGA_BASE_ADDR_1 0xbde00000
#define FPGA_BASE_ADDR_2 0xbdf00000

void emi_init(void);
void emi_write(u32 base, u32 offset, u8 value);
u8 emi_read(u32 base, u32 offset);
void emi_write_array(u32 base, u32 offset, u8* value, u16 count);
void emi_read_array(u32 base, u32 offset, u8* value, u16 count);
void emi_can_tx(Message const *m);
void emi_can_rx(Message *m);


#ifdef EMI_DEBUG
#define emi_debug(fmt, args...) printf(fmt, ##args)
#else
#define emi_debug(fmt, args...)
#endif


#endif
