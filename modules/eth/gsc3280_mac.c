/*----------------------------------------------------------------------------*/
/*
**  File	: gsc3280_mac.c
**  Data	: 2012-12-30
**
**	Note	: For Sort Out <ansonn.wang@gmail.com>
**----------------------------------------------------------------------------*/

#if 0
#include <config.h>

#include <common.h>
#include <malloc.h>
#endif /* if 0 end*/
#include <stdio.h>
#include <net.h>
#if 0
#include <command.h>
#endif /* if 0 end*/
#include <asm/io.h>
#if 0
#include <asm/u-boot.h>
#endif /* if 0 end*/

#include <miiphy.h>
#include <gsc3280_mac.h>
#include <gsc3280_regs.h>


//#define FORCE_USE_10MFULL
//#define DEBUG
/*----------------------------------------------------------------------------*/
#ifdef DEBUG
#define dprintf(fmt, args...) printf(fmt, ##args)
#else
#define dprintf(fmt, args...)
#endif
/*----------------------------------------------------------------------------*/
#define MII_DEV		"gsc3280_mac_phy"

static int half_workaround = 0;
static int cur_mode = USE_RMII_MODE;

extern volatile unsigned char *NetRxPackets[PKTBUFSRX];
static void display_dma_desc_ring(volatile const gsc3280_mac_dma_des *p, 
								  int size);
/*----------------------------------------------------------------------------*/
static struct gsc3280_mac_dma_t gsc3280_mac_dma;
static volatile gsc3280_mac_dma_des *dma_tx = NULL;
static volatile gsc3280_mac_dma_des *dma_rx = NULL;
static int cur_rx = 0;
static void *rx_packets[CONFIG_DMA_RX_SIZE] = { 0 };


/*----------------------------------------------------------------------------*/
/* DMA operation
** Release and free the descriptor resources. 
*/
static void free_dma_desc_resources(void)
{
	dma_tx = NULL;
	dma_rx = NULL;
	
	return;
}



/*----------------------------------------------------------------------------*/
/* MAC Register Accessors */
static inline ulong GSC3280_MAC_READ(ulong reg)
{
	return readl(GSC3280_MAC_MAC_BASEADDR + (reg));
}

/*----------------------------------------------------------------------------*/
static inline void GSC3280_MAC_WRITE(ulong value, ulong reg)
{
	writel((value), GSC3280_MAC_MAC_BASEADDR + (reg));
}


/*----------------------------------------------------------------------------*/
static int gsc3280_mac_mii_poll_busy (void)
{
	ulong now = get_timer(0);
	while (get_timer(now) < GSC3280_MAC_MII_POLL_BUSY_DELAY) 
	{
		if (!(GSC3280_MAC_READ(MAC_MII_ADDR) & MAC_MII_ADDR_BUSY)) 
		{
			return 1;
		}
	}
	dprintf("gsc3280_mac_mii_poll_busy timeout\n");

	return 0;
}

/*----------------------------------------------------------------------------*/
/* read reg from phy
** addr: phy_addr; reg: phy_reg_num; 
*/
static int gsc3280_mac_miiphy_read(char *devname, 
								  unsigned char phy_addr, unsigned char reg, 
								  unsigned short *value)
{
	int mii_addr = 0;

	mii_addr = ((phy_addr & MAC_MII_ADDR_PHY_MASK) << MAC_MII_ADDR_PHY_SHIFT)
				| ((reg & MAC_MII_ADDR_REG_MASK) << MAC_MII_ADDR_REG_SHIFT)
				| MAC_MII_ADDR_CR_VALUE
				| MAC_MII_ADDR_BUSY;


	/* wait mac_mii idle */
	gsc3280_mac_mii_poll_busy();
	GSC3280_MAC_WRITE(mii_addr, MAC_MII_ADDR);

	gsc3280_mac_mii_poll_busy();
	/* Return read value */
	*value = GSC3280_MAC_READ(MAC_MII_DATA);

	return 0;
}

/*----------------------------------------------------------------------------*/
/* write
*/
static int gsc3280_mac_miiphy_write(char *devname, 
								   unsigned char phy_addr, unsigned char reg, 
								   unsigned short value)
{
	int mii_addr;

	mii_addr = ((phy_addr & MAC_MII_ADDR_PHY_MASK) << MAC_MII_ADDR_PHY_SHIFT)
			 | ((reg & MAC_MII_ADDR_REG_MASK) << MAC_MII_ADDR_REG_SHIFT)
			 | MAC_MII_ADDR_WRITE 
			 | MAC_MII_ADDR_CR_VALUE 
			 | MAC_MII_ADDR_BUSY;

	gsc3280_mac_mii_poll_busy();

	/* Set the MII address register to write */
	GSC3280_MAC_WRITE(value, MAC_MII_DATA);
	GSC3280_MAC_WRITE(mii_addr, MAC_MII_ADDR);

	gsc3280_mac_mii_poll_busy();

	return 0;
}

/*----------------------------------------------------------------------------*/



/*----------------------------------------------------------------------------*/
static void gsc3280_mac_dma_stop_rx(void)
{
	unsigned int value;

	value = (unsigned int)GSC3280_MAC_READ(DMA_CONTROL);
	value &= ~DMA_CONTROL_SR;
	GSC3280_MAC_WRITE(value, DMA_CONTROL);

	return;
}

/*----------------------------------------------------------------------------*/
static void gsc3280_mac_dma_stop_tx(void)
{
	unsigned int value;

	value = (unsigned int)GSC3280_MAC_READ(DMA_CONTROL);
	value &= ~DMA_CONTROL_ST;
	GSC3280_MAC_WRITE(value, DMA_CONTROL);

	return;
}

/*----------------------------------------------------------------------------*/
static void gsc3280_mac_mac_disable(void)
{
	unsigned int value = (unsigned int)GSC3280_MAC_READ(MAC_CONTROL);

	dprintf("MAC RX/TX disabled\n");

	value &= ~(MAC_CONTROL_TE | MAC_CONTROL_RE);
	GSC3280_MAC_WRITE(value, MAC_CONTROL);

	return;
}

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
static int check_rx_error_summary(const gsc3280_mac_dma_des * const p)
{
	int ret = 0;	/* assume there are no errors */

	if (unlikely(p->des01.rx.error_summary)) {
		if (unlikely(p->des01.rx.descriptor_error))
			printf("RX: descriptor error\n");

		if (unlikely(p->des01.rx.crc_error)) 
			printf("RX: CRC error\n");

		if (unlikely(p->des01.rx.overflow_error)) 
			printf("RX: Overflow error\n");

		if (unlikely(p->des01.rx.late_collision))
			printf("RX: late_collision\n");

		if (unlikely(p->des01.rx.receive_watchdog))
			printf("RX: receive_watchdog error\n");

		if (unlikely(p->des01.rx.error_gmii))
			printf("RX: GMII error\n");
		
		ret = -1;
	}

	if (unlikely(p->des01.rx.length_error)) 
	{
		printf("RX: length_error error\n");
		ret = -1;
	}
	if (unlikely(p->des01.rx.dribbling) && (cur_mode == USE_MII_MODE)) {
		printf("RX: dribbling error\n");
		ret = -1;
	}
	if (unlikely(p->des01.rx.vlan_tag)) {
		printf("RX: found vlan_tag\n");
	}
	if (unlikely(p->des01.rx.ipc_csum_error)) {
		printf("RX: ipc_csum_error\n");
	}

	if (unlikely(p->des01.rx.filtering_fail)) {
		printf("RX: filtering_fail error\n");
		ret = -1;
	}

	if (ret != 0) {
		printf("%s() returning %d\n", __FUNCTION__, ret);
	}

	return ret;
}

/*----------------------------------------------------------------------------*/
static int check_tx_error_summary(const gsc3280_mac_dma_des * const p)
{
	int ret = 0;	/* assume there are no errors */

	if (unlikely(p->des01.tx.error_summary)) 
	{
		if (unlikely(p->des01.tx.loss_carrier))
			printf("TX: loss_carrier error\n");

		if (unlikely(p->des01.tx.no_carrier)) 
			printf("TX: no_carrier error\n");

		if (unlikely(p->des01.tx.late_collision))
			printf("TX: late_collision error\n");

		if (unlikely(p->des01.tx.excessive_collisions))
			printf("TX: excessive_collisions\n");

		if (unlikely(p->des01.tx.excessive_deferral))
			printf("TX: excessive_deferral\n");

		if (unlikely(p->des01.tx.underflow_error))
			printf("TX: underflow error\n");


		if (unlikely(p->des01.tx.jabber_timeout))
			printf("TX: jabber_timeout error\n");

		if (unlikely(p->des01.tx.frame_flushed))
			printf("TX: frame_flushed error\n");

		printf("TX: p->des01.u.des0 = 0x%08x", p->des01.u.des0);
		ret = -1;
	}

	if (unlikely(p->des01.tx.deferred)) 
	{
		printf("TX: deferred ");
		ret = -1;
	}

	if (unlikely(p->des01.tx.payload_error)) 
	{
		printf("TX Addr/Payload csum error\n");
		ret = -1;
	}
	if (unlikely(p->des01.tx.ip_header_error)) 
	{
		printf("TX IP header csum error\n");
		ret = -1;
	}
	if (p->des01.tx.vlan_frame) 
	{
		printf("TX: VLAN frame\n");
	}

	return ret;
}


/*----------------------------------------------------------------------------*/
/* TX, only use one buffer
*/
int gsc3280_mac_eth_tx(unsigned char *data, int len)
{
	volatile gsc3280_mac_dma_des *p = dma_tx;
	uint now = get_timer(0);
	uint status = 0;
	u32 end_ring;

	/* wait this descriptor is not buzy */
	while (p->des01.tx.own
	       && (get_timer(now) < CONFIG_GSC3280_MAC_TX_TIMEOUT)) {
		;
	}

	if (p->des01.tx.own) {
		printf("tx timeout - no desc available\n");
		return -1;
	}

	/* Make sure data is in real memory */
#if 0
	flush_cache((ulong)data, len);
#endif /* if 0 end*/
	p->des2 = (void *)PHYSADDR(data);

	/* Clean and set the TX descriptor */
	end_ring = p->des01.tx.end_ring;
	p->des01.u.des0 = p->des01.u.des1 = 0;
	p->des01.tx.interrupt = 1;				/* enable dma intrrupt */
	p->des01.tx.first_segment = 1;
	p->des01.tx.last_segment = 1;
	p->des01.tx.end_ring = end_ring;
	p->des01.tx.buffer1_size = len;
	p->des01.tx.own = 1;

	dprintf("\nTX %s(data=0x%08x, len=%d)\n", 
								__FUNCTION__, data, len);
	display_dma_desc_ring(dma_tx, CONFIG_DMA_TX_SIZE);


	/* CSR1 enables the transmit DMA to check for new descriptor */
	GSC3280_MAC_WRITE(DMA_STATUS_TI, DMA_STATUS);
	GSC3280_MAC_WRITE(1, DMA_XMT_POLL_DEMAND);

	now = get_timer(0);
	/*CONFIG_STMAC_TX_TIMEOUT*/
	while (get_timer(now) < 10) {
		status = GSC3280_MAC_READ(DMA_STATUS);
		if (status & DMA_STATUS_TI)
			break;
	}
	if (!(status & DMA_STATUS_TI)) {
		printf("tx timeout\n");
	}

	return check_tx_error_summary((gsc3280_mac_dma_des *)p);
}

/*----------------------------------------------------------------------------*/
void gsc3280_mac_eth_rx(void)
{
	int frame_len = 0;
	volatile gsc3280_mac_dma_des *drx;

	/* select the RX descriptor to use */
	drx = dma_rx + cur_rx;

	if ((cur_rx < 0) || (cur_rx >= CONFIG_DMA_RX_SIZE)) 
	{
		printf("%s: [dma drx = 0x%x, cur_rx=%d]\n", 
							__FUNCTION__, (unsigned int)drx, cur_rx);
		display_dma_desc_ring(dma_rx, CONFIG_DMA_RX_SIZE);
	}

	if (!(drx->des01.rx.own) && (drx->des01.rx.last_descriptor)) 
	{
		dprintf("RX descriptor ring:\n");
		display_dma_desc_ring(dma_rx, CONFIG_DMA_RX_SIZE);

		/* Check if the frame was not successfully received */
		if (check_rx_error_summary((gsc3280_mac_dma_des *)drx) < 0) 
		{
			
		} 
		else if (drx->des01.rx.first_descriptor 
							&& drx->des01.rx.last_descriptor) 
		{
			/* FL (frame length) indicates the length in byte including
			 * the CRC */
			frame_len = drx->des01.rx.frame_length;
			if ((frame_len >= 0) && (frame_len <= PKTSIZE_ALIGN)) 
			{
				const unsigned char *p = rx_packets[cur_rx];
				dprintf("\nRX[%d]:  0x%08x ", cur_rx, (unsigned int)p);
				dprintf("DA=%02x:%02x:%02x:%02x:%02x:%02x",
							p[0], p[1], p[2], p[3], p[4], p[5]);
				p += 6;
				dprintf(" SA=%02x:%02x:%02x:%02x:%02x:%02x",
							p[0], p[1], p[2], p[3], p[4], p[5]);
				p += 6;
				dprintf(" Type=%04x\n", p[0]<<8|p[1]);
#if 0
				memcpy((void*)NetRxPackets[0], rx_packets[cur_rx], frame_len);
				NetReceive(NetRxPackets[0], frame_len);
#endif /* if 0 end*/
			} 
			else 
			{
				printf("%s: Framelen %d too long\n", __FUNCTION__, frame_len);
			}

			dprintf("%s: frame received \n", __FUNCTION__);
		} 
		else 
		{
			printf("%s: very long frame received\n", __FUNCTION__);
		}

		drx->des01.rx.own = 1;
		/* advance to the next RX descriptor (for next time) */
		if (drx->des01.rx.end_ring)
			cur_rx = 0;	/* wrap, to first */
		else
			cur_rx++;	/* advance to next */

	} 
	else 
	{
		GSC3280_MAC_WRITE(1, DMA_RCV_POLL_DEMAND);	/* request input */
	}
	
	return;
}

/*----------------------------------------------------------------------------*/
void gsc3280_mac_halt(void)
{
	/* Reset the TX/RX processes */
	gsc3280_mac_dma_stop_rx();
	gsc3280_mac_dma_stop_tx();

	/* Disable the MAC core */
	gsc3280_mac_mac_disable();

	/* Free buffers */
	free_dma_desc_resources();
}

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/* Automatically gets and returns the PHY device 
*/
static u32 gsc3280_mac_phy_get_addr(void)
{
	u32 i, id;

	for (i = 0; i < 32; i++) 
	{
		unsigned short id1, id2;
		unsigned char phyaddr;

#ifdef CONFIG_PHY_DP83848C
		phyaddr = (i+1) % 32;
#elif defined(CONFIG_PHY_LAN8720A)
		phyaddr = i % 32;
#endif
		miiphy_read(MII_DEV, phyaddr, MII_PHYSID1, &id1);
		miiphy_read(MII_DEV, phyaddr, MII_PHYSID2, &id2);

		id  = (id1 << 16) | (id2);
#ifdef CONFIG_PHY_DP83848C
		if ((id & DP83848C_PHY_ID_MASK) == DP83848C_PHY_ID) 
		{
			dprintf("PHY DP8384C found (ID=0x%08x)\n", id);
			return phyaddr;
		}

#elif defined(CONFIG_PHY_LAN8720A)
		if ((id & LAN8720A_PHY_ID_MASK) == LAN8720A_PHY_ID) 
		{
			dprintf("PHY LAN8720A found (ID=0x%08x)\n", id);
			return phyaddr;
		}
#endif

		dprintf("Unable to find a known PHY (ID=0x%08x)\n", id);
	}

	return -1;
}

/*----------------------------------------------------------------------------*/
void gsc3280_probe_mac_sysctl(void)
{
	unsigned int reg_val = 0;
	unsigned char phyaddr = gsc3280_mac_phy_get_addr();
	unsigned short value;
	if (phyaddr < 0) 
	{
		printf("ERROR: can't find suitable PHY\n");
		return;
	}

	/* DP83848C Have auto-negotiation function */
	/* PIN<AN_EN, AN0, AN1>, determine whether use auto-negotiation */
	/* Extern PIN determine whether use MII Or RMII */
#ifdef CONFIG_PHY_DP83848C
	miiphy_read(MII_DEV, phyaddr, MII_RBR, &value);
	if (value & MII_RBR_RMII_MODE) 
#elif defined(CONFIG_PHY_LAN8720A)
	if (1) //default RMII MODE
#endif
	{
		printf("SoC use RMII\n");
		*(u32 *)(GSC3280_REGADDR_SYSCTL_MAC_CFG) = 1;
		/* disable mii io && enable rmii io */
		reg_val = *((volatile u32 *)(GSC3280_REGADDR_SYSCTL_IO_CFG0));
		reg_val &= ~(0x01 << 21);
		reg_val |= (0x01 << 22);
		*((volatile u32 *)(GSC3280_REGADDR_SYSCTL_IO_CFG0)) = reg_val;
		cur_mode = USE_RMII_MODE;
	} 
	else
	{
		printf("SoC use MII\n");
		*(u32 *)(GSC3280_REGADDR_SYSCTL_MAC_CFG) = 0;
		/* disable emi rmii && enable mii io */
		reg_val = *((volatile u32 *)(GSC3280_REGADDR_SYSCTL_IO_CFG0));
		reg_val &= ~(0x01 << 31);
		reg_val &= ~(0x01 << 22);
		reg_val |= (0x01 << 21);
		*((volatile u32 *)(GSC3280_REGADDR_SYSCTL_IO_CFG0)) = reg_val;
		cur_mode = USE_MII_MODE;
	}

	return;
}


/*----------------------------------------------------------------------------*/
static void display_dma_desc_ring(volatile const gsc3280_mac_dma_des *p, 
								  int size)
{
	int i;
	
	for (i = 0; i < size; i++)
	{
		dprintf("\t%d [0x%x]: desc0=0x%08x, desc1=0x%08x, buffer1=0x%08x\n",
								i, (unsigned int)&p[i].des01.u.des0,
								p[i].des01.u.des0, 
								p[i].des01.u.des1, 
								p[i].des2);
	}
	return;
}


/*----------------------------------------------------------------------------*/
static void init_rx_desc(volatile gsc3280_mac_dma_des * p,
								unsigned int ring_size, 
								void **buffers)
{
	int i;

	for (i = 0; i < ring_size; i++) 
	{
		p->des01.u.des0 = p->des01.u.des1 = 0;
		p->des01.rx.own = 1;
		p->des01.rx.buffer1_size = PKTSIZE_ALIGN;
		p->des01.rx.disable_ic = 1;
		if (i == ring_size - 1)
			p->des01.rx.end_ring = 1;
		p->des2 = ((void *) (PHYSADDR (buffers[i])));
		p->des3 = NULL;
		p++;
	}
	
	return;
}

/*----------------------------------------------------------------------------*/
static void init_tx_desc(volatile gsc3280_mac_dma_des * p, 
									unsigned int ring_size)
{
	int i;

	for (i = 0; i < ring_size; i++) 
	{
		p->des01.u.des0 = p->des01.u.des1 = 0;
		if (i == ring_size - 1)
			p->des01.tx.end_ring = 1;
		p->des2 = NULL;
		p->des3 = NULL;
		p++;
	}
	
	return;
}

/*----------------------------------------------------------------------------*/
/* Allocate and init the TX and RX descriptors rings.
** The driver uses the 'implicit' scheme for implementing the TX/RX DMA
** linked lists.
*/
static void init_dma_desc_rings(void)
{
	int i;

	/* Clean out uncached buffers */
#if 0
	flush_cache((unsigned long)&gsc3280_mac_dma, 
						sizeof(struct gsc3280_mac_dma_t));
#endif /* if 0 end*/

	/* use uncache address */
	dma_rx = 
		(volatile gsc3280_mac_dma_des *)P2SEGADDR(&gsc3280_mac_dma.desc_rx[0]);
	dma_tx = 
		(volatile gsc3280_mac_dma_des *)P2SEGADDR(&gsc3280_mac_dma.desc_tx[0]);
	cur_rx = 0;

	if ((dma_rx == NULL) || (dma_tx == NULL) 
						 || (((u32)dma_rx % L1_CACHE_BYTES) != 0) 
						 || (((u32)dma_tx % L1_CACHE_BYTES) != 0)) 
	{
		printf("ERROR allocating the DMA Tx/Rx desc\n");
		return;
	}

	for (i = 0; i < CONFIG_DMA_RX_SIZE; i++)
	{
		/* use uncache address */
		rx_packets[i] = (void *)P2SEGADDR(gsc3280_mac_dma.rx_buff + 
											(PKTSIZE_ALIGN * i));
	}
	/* Initialize the contents of the DMA buffers */
	init_rx_desc(dma_rx, CONFIG_DMA_RX_SIZE, rx_packets);
	init_tx_desc(dma_tx, CONFIG_DMA_TX_SIZE);

	dprintf("RX descriptor ring:\n");
	display_dma_desc_ring(dma_rx, CONFIG_DMA_RX_SIZE);
	dprintf("TX descriptor ring:\n");
	display_dma_desc_ring(dma_tx, CONFIG_DMA_TX_SIZE);

	return;
}

/*----------------------------------------------------------------------------*/
static int gsc3280_mac_phy_negotiate(unsigned char phy_addr)
{
	unsigned long now, now1;
	unsigned short tmp, status;
	status = 0;

	miiphy_read(MII_DEV, phy_addr, MII_BMCR, &tmp);
	
#ifdef FORCE_USE_10MFULL
	tmp &= ~(0x01 << 12);
	tmp &= ~(0x01 << 13);
	tmp |= (0x01 << 8);

	miiphy_write(MII_DEV, phy_addr, MII_BMCR, tmp);
#else
	tmp |= (BMCR_ANENABLE | BMCR_ANRESTART);
	miiphy_write(MII_DEV, phy_addr, MII_BMCR, tmp);

	now = get_timer(0);
	now1 = get_timer(now);
    //while (get_timer(now) < CONFIG_GSC3280_MAC_AUTONEG_TIMEOUT)
    while (now1 < CONFIG_GSC3280_MAC_AUTONEG_TIMEOUT)
	{
		miiphy_read(MII_DEV, phy_addr, MII_BMSR, &status);
		if (status & BMSR_ANEGCOMPLETE) {
			break;
		}

		/* Restart auto-negotiation if remote fault */
		if (status & BMSR_RFAULT) 
		{
			printf("PHY remote fault detected\n");
			/* Restart auto-negotiation */
			printf("PHY restarting auto-negotiation\n");
			miiphy_write(MII_DEV, phy_addr, MII_BMCR, 
								BMCR_ANENABLE | BMCR_ANRESTART);
		}
		now1 = get_timer(now);
	}

	if (!(status & BMSR_ANEGCOMPLETE))
		printf("PHY auto-negotiate timed out\n");

	if (status & BMSR_RFAULT) 
		printf("PHY remote fault detected\n");
#endif

	return 0;
}


/*----------------------------------------------------------------------------*/
static void gsc3280_set_mac_mii_cap(int full_duplex, unsigned int speed)
{
	unsigned int flow = (unsigned int)GSC3280_MAC_READ(MAC_FLOW_CONTROL);
	unsigned int ctrl = (unsigned int)GSC3280_MAC_READ(MAC_CONTROL);

	dprintf("%s(full_duplex[%d], speed[%d])\n", 
								__FUNCTION__, full_duplex, speed);

	if (!(full_duplex)) 
	{	
		/* Half Duplex disable recv pause frame */
		flow &= ~(MAC_FLOW_CTRL_PT_MASK | MAC_FLOW_CTRL_RFE);
		/* Backpressure Activate  */
		flow |= MAC_FLOW_CTRL_TFE;
		
		ctrl &= ~MAC_CONTROL_DM;
	}
	else 
	{
		/* Full Duplex, enable rx/tx pause frame */
		flow |= MAC_FLOW_CTRL_TFE | MAC_FLOW_CTRL_RFE;
		/* max pause time */
		flow |= MAC_FLOW_CTRL_PT_MASK;

		ctrl |= MAC_CONTROL_DM;
	}

	/* support RMII interface */
	switch (speed) 
	{
		case 100:		/* 100Mbps */
			ctrl |= MAC_CONTROL_FES;
			break;
	case 10:			/* 10Mbps */
			ctrl &= ~MAC_CONTROL_FES;
			break;
	}

	GSC3280_MAC_WRITE(flow, MAC_FLOW_CONTROL);
	GSC3280_MAC_WRITE(ctrl, MAC_CONTROL);

	return;
}


/*----------------------------------------------------------------------------*/
static unsigned int gsc3280_mac_phy_check_speed(unsigned char phy_addr)
{
	unsigned short status;
	int full_duplex = 0;
	int speed = 0;

	/* Read Status register */
	miiphy_read(MII_DEV, phy_addr, MII_BMSR, &status);

	/* Check link status.  If 0, default to 100 Mbps. */
	if ((status & BMSR_LSTATUS) == 0) 
	{
		
#ifdef FORCE_USE_10MFULL
		printf("Force Use 10M Full\n");
		gsc3280_set_mac_mii_cap(1, 10);
#else
		printf("*Warning* no link detected\n");
#endif
		return 1;
	} 
	else 
	{
		unsigned short negotiated = 0;
		miiphy_read(MII_DEV, phy_addr, MII_LPA, &negotiated);

		half_workaround = 0;
		if (negotiated & LPA_100FULL) 
		{
			printf("100Mbs full duplex link detected\n");
			full_duplex = 1;
			speed = 100;
		} 
		else if (negotiated & LPA_100HALF) 
		{
			printf("100Mbs half duplex link detected\n");
			full_duplex = 0;
			speed = 100;
		} 
		else if (negotiated & LPA_10FULL) 
		{
			printf ("10Mbs full duplex link detected\n");
			full_duplex = 1;
			speed = 10;
		} 
		else 
		{
			printf ("10Mbs half duplex link detected\n");
			full_duplex = 0;
			speed = 10;
			half_workaround = 1;
		}
	}	
	gsc3280_set_mac_mii_cap(full_duplex, speed);

	return 0;
}

/*----------------------------------------------------------------------------*/
static int gsc3280_mac_phy_init(void)
{
	unsigned char eth_phy_addr;
	unsigned short advertised_caps, value;

	dprintf("MAC P1/2: phy initialization through mii&rmii\n");
	/* Obtain the PHY's address/id */
	eth_phy_addr = gsc3280_mac_phy_get_addr();
	if (eth_phy_addr < 0)
		return -1;

	/* Now reset the PHY we just found */
#ifdef CONFIG_PHY_DP83848C
	if (miiphy_reset(MII_DEV, eth_phy_addr) < 0) 
	{
		printf("PHY reset failed!\n");
		return -1;
	}
	miiphy_read(MII_DEV, eth_phy_addr, PHY_CTRL_REG, &value);
#elif defined(CONFIG_PHY_LAN8720A)
	miiphy_read(MII_DEV, eth_phy_addr, PHY_SPEC_REG, &value);
#endif
	value = (value & PHY_ADDR_MSK) >> PHY_ADDR_SHIFT;
	if (value != eth_phy_addr) 
	{
		printf("PHY address mismatch with hardware (hw %d != %d)\n",
								value, eth_phy_addr);
	}

	/* Read the ANE Advertisement register */
	miiphy_read(MII_DEV, eth_phy_addr, MII_ADVERTISE, &advertised_caps);

	/* Copy our capabilities from MII_BMSR to MII_ADVERTISE */
	miiphy_read(MII_DEV, eth_phy_addr, MII_BMSR, &value);

	/* Set the advertised capabilities */
	if (value & BMSR_100BASE4)
		advertised_caps |= ADVERTISE_100BASE4;
	if (value & BMSR_100FULL)
		advertised_caps |= ADVERTISE_100FULL;
	if (value & BMSR_100HALF)
		advertised_caps |= ADVERTISE_100HALF;
	if (value & BMSR_10FULL)
		advertised_caps |= ADVERTISE_10FULL;
	if (value & BMSR_10HALF)
		advertised_caps |= ADVERTISE_10HALF;

	/* no use flow control */
	advertised_caps &= ~MII_ADVERTISE_PAUSE;

	/* Update our Auto-Neg Advertisement Register */
	miiphy_write(MII_DEV, eth_phy_addr, MII_ADVERTISE, advertised_caps);

	/* auto-negotiate with remote link partner */
	gsc3280_mac_phy_negotiate(eth_phy_addr);
	gsc3280_mac_phy_check_speed(eth_phy_addr);

	return 0;
}

/*----------------------------------------------------------------------------*/
static int gsc3280_mac_get_mac_addr(unsigned char *addr)
{
	unsigned int hi_addr, lo_addr;

	/* Read the MAC address from the hardware */
	hi_addr = (unsigned int)GSC3280_MAC_READ(MAC_ADDR_HIGH);
	lo_addr = (unsigned int)GSC3280_MAC_READ(MAC_ADDR_LOW);

    dprintf("hi_addr = 0x%08x, lo_addr = 0x%08x\n", hi_addr, lo_addr);

	if ((hi_addr == 0x0000FFFFUL) && (lo_addr == 0xFFFFFFFF))
		return 0;

	/* Extract the MAC address from the high and low words */
	addr[0] = lo_addr & 0xffu;
	addr[1] = (lo_addr >> 8) & 0xffu;
	addr[2] = (lo_addr >> 16) & 0xffu;
	addr[3] = (lo_addr >> 24) & 0xffu;
	addr[4] = hi_addr & 0xffu;
	addr[5] = (hi_addr >> 8) & 0xffu;

	return 1;
}


/*----------------------------------------------------------------------------*/
static void gsc3280_mac_set_mac_addr(unsigned char *Addr)
{
	unsigned long data;

	data = (Addr[5] << 8) | Addr[4] | MAC_ADDR_HIGH_AE;
	GSC3280_MAC_WRITE(data, MAC_ADDR_HIGH);
	data = (Addr[3] << 24) | (Addr[2] << 16) | (Addr[1] << 8) | Addr[0];
	GSC3280_MAC_WRITE(data, MAC_ADDR_LOW);
}


/*----------------------------------------------------------------------------*/
static int gsc3280_mac_get_ethaddr(void)
{
	int env_size, rom_valid, env_present = 0, reg;
	char *s = CONFIG_ETHADDR;
	char *e;
	char s_env_mac[64];
	uchar v_env_mac[6], v_rom_mac[6], *v_mac;
	char *envptr = NULL;


    for (reg = 0; reg < 6; ++reg) 
    {   /* turn string into mac value */
        v_env_mac[reg] = s ? simple_strtoul (s, &e, 16) : 0;
        if (s)
            s = (*e) ? e + 1 : e;
    }

    v_mac = &v_env_mac[0];

    gsc3280_mac_set_mac_addr(v_mac);
	dprintf("Using MAC Address %02X:%02X:%02X:%02X:%02X:%02X\n", 
								v_mac[0], v_mac[1], v_mac[2], 
								v_mac[3], v_mac[4], v_mac[5]);

#if 0
	envptr = getenv("ethaddr");
	if (envptr == NULL) 
	{	/* exit if env is bad */
		dprintf("\n*** ERROR: ethaddr is not set properly!!\n");
		return -1;
	}

	strncpy(s_env_mac, envptr, sizeof(s_env_mac));
	env_size = strlen(envptr);
	if (env_size > 0) 
	{
		env_present = 1;
		s = s_env_mac;
	}

	for (reg = 0; reg < 6; ++reg) 
	{	/* turn string into mac value */
		v_env_mac[reg] = s ? simple_strtoul (s, &e, 16) : 0;
		if (s)
			s = (*e) ? e + 1 : e;
	}
	/* get ROM mac value if any */
	rom_valid = gsc3280_mac_get_mac_addr(v_rom_mac);
	if (!env_present) 
	{	/* if NO env */
		if (rom_valid) 
		{	/* but ROM is valid */
			v_mac = v_rom_mac;
			dprintf("ROM MAC:%02X:%02X:%02X:%02X:%02X:%02X\n",
				 v_mac[0], v_mac[1], v_mac[2], v_mac[3],
				 v_mac[4], v_mac[5]);
			setenv ("ethaddr", s_env_mac);
		} 
		else 
		{	/* no env, bad ROM */
			dprintf("\n*** ERROR: ethaddr is NOT set !!\n");
			return -1;
		}
	} 

	else 
	{	/* good env, don't care ROM */
		v_mac = v_env_mac;	/* always use a good env over a ROM */
	}
	if (env_present && rom_valid) 
	{	/* if both env and ROM are good */
		if (memcmp(v_env_mac, v_rom_mac, 6) != 0) 
		{
			dprintf("\nWarning: MAC addresses don't match:\n");
			dprintf("\tHW MAC address:  "
				"%02X:%02X:%02X:%02X:%02X:%02X\n",
				v_rom_mac[0], v_rom_mac[1],
				v_rom_mac[2], v_rom_mac[3],
				v_rom_mac[4], v_rom_mac[5]);
			dprintf("\t\"ethaddr\" value: "
				"%02X:%02X:%02X:%02X:%02X:%02X\n",
				v_env_mac[0], v_env_mac[1],
				v_env_mac[2], v_env_mac[3],
				v_env_mac[4], v_env_mac[5]);
		}
	}
#endif /* if 0 end*/
	/* update global address to match env (allows env changing) */
#if 0
	memcpy (bd->bi_enetaddr, v_mac, 6);	
#endif /* if 0 end*/
	/* use old function to update default */
#if 0
	gsc3280_mac_set_mac_addr(v_mac);	
	dprintf("Using MAC Address %02X:%02X:%02X:%02X:%02X:%02X\n", 
								v_mac[0], v_mac[1], v_mac[2], 
								v_mac[3], v_mac[4], v_mac[5]);
#endif /* if 0 end*/
	
	return 0;
}

/*----------------------------------------------------------------------------*/
static void gsc3280_mac_dump_regs(void)
{
#ifdef DEBUG
	int i;
	const char fmt[] =
		"\tReg No. %2d (offset 0x%03x): 0x%08x\n";
	const char header[] =
		"\t----------------------------------------------\n"
		"\t  %s registers (base addr = 0x%8x)\n"
		"\t----------------------------------------------\n";

	dprintf(header, "MAC CORE", (unsigned int)GSC3280_MAC_MAC_BASEADDR);
	for (i = 0; i < 18; i++) {
		int offset = i * 4;
		dprintf(fmt, i, offset, GSC3280_MAC_READ(offset));
	}

	dprintf(header, "MAC DMA", (unsigned int)GSC3280_MAC_MAC_BASEADDR);
	for (i = 0; i < 9; i++) {
		int offset = i * 4;
		dprintf(fmt, i, (DMA_BUS_MODE + offset),
					GSC3280_MAC_READ(DMA_BUS_MODE + offset));
	}

	dprintf("\tSTBus bridge register (0x%08x) = 0x%08x\n",
					(unsigned int)(GSC3280_MAC_MAC_BASEADDR 
					+ STBUS_BRIDGE_OFFSET),
					GSC3280_MAC_READ(STBUS_BRIDGE_OFFSET));
#endif
}

/*----------------------------------------------------------------------------*/
static int gsc3280_mac_reset_eth(void)
{
	unsigned int value;

	gsc3280_probe_mac_sysctl();

	dprintf("P1: DMA reset...\n");
	value = (unsigned int)GSC3280_MAC_READ(DMA_BUS_MODE);
	value |= DMA_BUS_MODE_SFT_RESET;
	GSC3280_MAC_WRITE(value, DMA_BUS_MODE);
	/* wait DMA Reset Complete */
	while ((GSC3280_MAC_READ(DMA_BUS_MODE) & DMA_BUS_MODE_SFT_RESET)) {
		;
	}
	dprintf("P2: DMA reset complete.\n");

	/* wait DMA AHB master FSM in idle */
	while ((GSC3280_MAC_READ(DMA_AHB_STATUS) & DMA_AHB_STATUS_AXWHSTS)) {
		;
	}
	dprintf("P3: DMA AHB mater idle.\n");


	dprintf("P4: Configure Bus Mode Register.\n");
	value = (unsigned int)GSC3280_MAC_READ(DMA_BUS_MODE);
	dprintf("default Bus Mode Register: 0x%x\n", value);	
	value |= DMA_BUS_MODE_MIXED_BURST | DMA_BUS_MODE_AAL;
	value &= ~DMA_BUS_MODE_FB;
	value |= ((16 << DMA_BUS_MODE_PBL_SHIFT) & DMA_BUS_MODE_PBL_MASK);
	value &= ~DMA_BUS_MODE_8PBL;
	value &= ~DMA_BUS_MODE_ATDS;
	value |= ((0 << DMA_BUS_MODE_DSL_SHIFT) & DMA_BUS_MODE_DSL_MASK);
	value &= ~DMA_BUS_MODE_DA;
	dprintf("DMA Bus Mode Register: 0x%x\n", value);
	GSC3280_MAC_WRITE(value, DMA_BUS_MODE);
	
	dprintf("P6: Rx/Tx ring descriptor list initialization\n");
	init_dma_desc_rings();


	dprintf("P8: Configure Tx/Rx Descriptor List Address Register\n");
	GSC3280_MAC_WRITE(PHYSADDR(dma_tx), DMA_TX_BASE_ADDR);
	GSC3280_MAC_WRITE(PHYSADDR(dma_rx), DMA_RCV_BASE_ADDR);

	dprintf("P9: Configure DMA Operation Mode Register\n");
	value = (unsigned int)GSC3280_MAC_READ(DMA_CONTROL);
	//a, set RSF and TSF
	value |= DMA_CONTROL_RSF | DMA_CONTROL_TSF;
	value &= ~DMA_CONTROL_FEF;
	//g, Disable DMA Receiving Process
	value &= ~DMA_CONTROL_SR;
	value |= (0x1 << 26);

	GSC3280_MAC_WRITE(value, DMA_CONTROL);

	dprintf("P10: Clear interrupt request\n");
	value = 0x1ffff;
	GSC3280_MAC_WRITE(value, DMA_STATUS);

	dprintf("P11: disable DMA interrupt, use polling\n");
	value = (unsigned int)GSC3280_MAC_READ(DMA_INTR_ENA);
	dprintf("default dma interrupt enable register: 0x%x\n", value);
	value = 0;
	GSC3280_MAC_WRITE(value, DMA_INTR_ENA);

	dprintf("P13: DMA Tx & Rx Enable\n");
	value = (unsigned int)GSC3280_MAC_READ(DMA_CONTROL);
	dprintf("Default Operation Mode Register: 0x%x\n", value);
	value |= DMA_CONTROL_ST | DMA_CONTROL_SR;
	GSC3280_MAC_WRITE(value, DMA_CONTROL);

	if (gsc3280_mac_phy_init() < 0) 
	{
		dprintf("ERROR: no PHY detected\n");
		return -1;
	}

	dprintf("MAC P-5: Configure MAC Address Register.\n");
	gsc3280_mac_get_ethaddr();

	dprintf("MAC P-7: Configure MAC Frame Filter Register.\n");
	value = (unsigned int)GSC3280_MAC_READ(MAC_FRAME_FILTER);
	dprintf("Default MAC Frame Filter Register: 0x%x\n", value);
	value |= MAC_FRAME_FILTER_RA;	// receive all frame.
	GSC3280_MAC_WRITE(value, MAC_FRAME_FILTER);

#if 0
	/* Set the MAC control register with our default value */
	dprintf("MAC P-10: Configure MAC Control Register.\n");
	value = (unsigned int)GSC3280_MAC_READ(MAC_CONTROL);
	value |= MAC_CONTROL_JD;
	GSC3280_MAC_WRITE(value, MAC_CONTROL);
	value = (unsigned int)GSC3280_MAC_READ(MAC_CONTROL);
	dprintf("MAC Control Register: %x\n", value);
#endif /* if 0 end*/

	dprintf("MAC P-11: Enable MAC Tx & Rx\n");
	value = (unsigned int)GSC3280_MAC_READ(MAC_CONTROL);
	value |= (MAC_CONTROL_TE | MAC_CONTROL_RE);
	GSC3280_MAC_WRITE(value, MAC_CONTROL);

	gsc3280_mac_dump_regs();

	GSC3280_MAC_WRITE(1, DMA_RCV_POLL_DEMAND);	/* request input */

	/* 
	 * FIXME: due to unknown hardware issue, a 50ms delay should be 
	 * inserted between mac initial process and sending first frame.
	 * and this delay is only neccessory in 10Mbps, half mode.
	 */
	if (half_workaround)
		udelay(50000);
	
	return 0;
}

/*----------------------------------------------------------------------------*/
/* init mac
*/
int gsc3280_mac_init(void)
{
	gsc3280_mac_reset_eth();

	return 0;
}

/*----------------------------------------------------------------------------*/
/* init phy
*/
int gsc3280_mac_miiphy_init(void)
{
    miiphy_init();
	miiphy_register((const char*)MII_DEV, gsc3280_mac_miiphy_read, 
							 gsc3280_mac_miiphy_write);

	return 0;
}

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

int gsc3280_eth_init(void)
{
    gsc3280_mac_miiphy_init();
    gsc3280_mac_init();
}



