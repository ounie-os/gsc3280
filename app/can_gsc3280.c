#include <def.h>
#include <stdio.h>
#include <sysctl.h>
#include "can_gsc3280.h"
#include <interrupt.h>
#include <OD_0_0.h>

static volatile unsigned int g_in_sending = 0;

static inline void can_enter_send(void)
{
    g_in_sending = 1;
}

static inline void can_leave_send(void)
{
    g_in_sending = 0;
}

static inline unsigned int query_can_send_status(void)
{
    return g_in_sending;
}


static inline unsigned int can_read_reg(unsigned int reg)
{
	return readl(CAN_BASE_ADDR+reg);//(*(volatile unsigned int *)(reg));
}

static inline void can_write_reg(unsigned int reg, unsigned int val)
{
	writel(val,CAN_BASE_ADDR+reg);
}


void can_irq_handler(void * arg)
{
    u32 ir;
    Message frame;

    ir = can_read_reg(REG_IR);

    if (ir & IRQ_RI)
    {
        can_rx(&frame);
        canDispatch(&OD_0_0_Data, &frame);
    }
    if (ir & IRQ_TI)
    {
        can_leave_send();    /* 表示发送完毕 */
    }
    if (ir & IRQ_DOI)
    {
        printf("recv fifo overflow...\n");
    }
    if (ir & IRQ_BEI)
    {
        printf("irq bei...\n");
    }
    if (ir & IRQ_ALI)
    {
        printf("irq ali...\n");
    }
    if (ir & IRQ_EPI)
    {
        printf("irq epi...\n");
    }
    
}

int can_irq_init(unsigned int enable_bits)
{
    int ret;
    can_write_reg(REG_IER, enable_bits);
    init_irq();
    ret = request_irq(22, can_irq_handler, (void *)0);
    if (0 != ret)
    {
        can_debug("can_irq_init fail...\n");
        return -1;
    }
    return 0;
}


void can_sys_init(void)
{
	sysctl_mod_enable(SYSCTL_MOD_CAN);//enable can module
	writel(0x1, SYSCTL_CLKDIV_CAN);//set can clk div
#ifdef USE_CAN1
	writel(readl(SYSCTL_IOMUX_CFG0) | (0x1<<16),SYSCTL_IOMUX_CFG0);//enable can1 function
	writel(readl(SYSCTL_IOMUX_CFG0) & (~(0x1<<3)),SYSCTL_IOMUX_CFG0);//disenable can1 uart0
#else 
#ifdef USE_CAN0
	writel(readl(SYSCTL_IOMUX_CFG0) | (0x1<<15),SYSCTL_IOMUX_CFG0);//enable can0 function
	writel(readl(SYSCTL_IOMUX_CFG0) & (~(0x1<<13)),SYSCTL_IOMUX_CFG0);//disenable can0 uart6
#else
    # error "You should define -DUSE_CAN0 or -DUSE_CAN1 in Makefile..."
#endif
#endif
	
	can_debug("systerm init...\n");
}

static int set_reset_mode(void)
{
	unsigned char status = can_read_reg(REG_MOD)&0xff;
	int i;

	/* disable interrupts */
	can_write_reg(REG_IER, IRQ_OFF);

	for (i = 0; i < 100; i++) {
		/* check reset bit */
		if (status & MOD_RM) {
			return 0;
		}

		can_write_reg(REG_MOD, MOD_RM);	/* reset chip */
		status = can_read_reg(REG_MOD);
	}

	return -1;
}

static void set_normal_mode(int mode)
{
	unsigned char status = can_read_reg(REG_MOD);
	int i;
	
	for (i = 0; i < 10; i++) {
		/* check reset bit */
		if ((status & MOD_RM) == 0||(status&(MOD_SM|MOD_STM|MOD_LOM))) {
			/* enable all interrupts */
			can_write_reg(REG_IER, IRQ_ALL);
			return;
		}

		/* set chip to normal mode */
		can_write_reg( REG_MOD, mode);
		udelay(10);
		status = can_read_reg(REG_MOD);
	}

}

static void bare_can_start(int mode)
{
	/* Clear error counters and error code capture */
	can_write_reg(REG_TXERR, 0x0);
	can_write_reg(REG_RXERR, 0x0);

	/* leave reset mode */
	set_normal_mode(mode);
}

#define CONFIG_CAN_CLK_HZ  27800000
static int bare_can_setbrg(int baudr)
{
	int fxtal = CONFIG_CAN_CLK_HZ;
	int tscl, btr;
	unsigned char brp; // 0~63 +1
	unsigned char sjw = 2; // 0~3 +1
	unsigned char sam = 0; // 0~1
	unsigned char tseg2 = 3; // 0~7 +1
	unsigned char tseg1 = 3; // 0~15 +1

	if(!(baudr==500000||baudr==1000000)){
		baudr = 500000;
		can_debug("baudr is error,default set baudr to 500000.\n");
	}

	//calculation
	tscl = (1+tseg1+tseg2)*baudr;
	brp = (fxtal>>1)/tscl + 1;

	//set register
	btr = ((~(sam << 15)) & ((tseg2 -1) << 12)) | ((tseg1 -1) << 8) | ((sjw - 1) << 6) | (brp - 1);

	can_write_reg(REG_BTR, btr);

	return 0;
}

static void bare_can_setfilter(int acc, int filter)
{
	/* set acceptance filter (accept all) */
	can_write_reg( REG_ACR, acc);
	can_write_reg( REG_AMR, filter);
}

void can_init(int mode, int acc, int filter, int brg)
{
	int ret;

	can_sys_init();

	ret = set_reset_mode();
	if(ret < 0){
		can_debug("init fault!\n");
		return;
	}

	if(acc!=-1)	
		bare_can_setfilter(acc, filter);
	if(brg!=-1)
		bare_can_setbrg(brg);//250k

	bare_can_start(mode);

	//can_irq_init(IRQ_RI | IRQ_TI | IRQ_DOI);
	can_irq_init(IRQ_ALL);
}


/*
 * transmit a CAN message
 */
static int bare_start_tx(struct can_frame *cf)
{
	unsigned char dlc;
	unsigned int id;
	
	dlc = cf->can_ff;
	id = cf->can_id;

	can_write_reg(REG_TXB1, dlc);
    can_write_reg(REG_TXB2, id<<21);

	if (dlc)
	{
		can_write_reg(REG_TXB3, cf->data[0]);
		can_write_reg(REG_TXB4, cf->data[1]);
	}
	
	can_write_reg(REG_CMR, CMD_TR);
	
	return 0;
}

static unsigned int bare_can_rx(Message* m)
{
	unsigned char ff;
	unsigned int id;
	unsigned char dlc;
	unsigned int data[2];

	ff  = can_read_reg(REG_RXB1);
	dlc = ff & 0x0f;

	m->len = dlc;
	
	/* standard frame format (SFF) */
	id = (can_read_reg(REG_RXB2)) >> 21;

	m->cob_id = id & 0x7ff;

	if(dlc)
	{
		data[0] = can_read_reg(REG_RXB3);
		data[1] = can_read_reg(REG_RXB4);
		memcpy(m->data, &data[0], 8);
	}
    can_debug(">>>can recv<<<\n");
    can_debug("id = %x, len = %d, ", m->cob_id, m->len);
    can_debug("data = %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\n", 
            m->data[0],m->data[1],m->data[2],m->data[3],
            m->data[4],m->data[5],m->data[6],m->data[7]);

	/* release receive buffer */
	can_write_reg(REG_CMR, CMD_RRB);

	return 0;
}


int can_tx (Message const *m)
{
	struct can_frame cf;
	unsigned int timeout = 0xffff;
	
	cf.can_ff = m->len;
	cf.can_id = m->cob_id & 0x7ff;

	memcpy(&cf.data[0], (void *)m->data, 8);

    do
    {
	    if (0 == query_can_send_status())    /* 表示可以发送了 */
	    {
	        break;
	    }
	} while (timeout--);

	can_enter_send();    /* 置位，表示正在发送 */

	can_debug(">>>can send<<<\n");
    can_debug("id = %x, len = %d, ", cf.can_id, cf.can_ff);
    can_debug("data = %02x,%02x,%02x,%02x,%02x,%02x,%02x,%02x\n", 
            m->data[0],m->data[1],m->data[2],m->data[3],
            m->data[4],m->data[5],m->data[6],m->data[7]);	

	bare_start_tx(&cf);

	return 0;
}

unsigned int can_rx(Message *m)
{
#if 0
	do{
		if(can_read_reg(REG_SR)&0x1){
			return bare_can_rx(m);
		}
	}while(1);
#endif /* if 0 end*/

    bare_can_rx(m);
    
	return 0;
}

