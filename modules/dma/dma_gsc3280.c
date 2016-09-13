#include <asm/io.h>
#include <sysctl.h>
#include <dma_gsc3280.h>
#include <emi_gsc3280.h>

#define DMAC_BASE   0xBC042000

#define dmac_writel_hi(reg, value) \
	__raw_writel((value), (DMAC_BASE + DMAC_##reg + 4)

#define dmac_readl_hi(reg) \
	__raw_readl(DMAC_BASE + DMAC_##reg + 4)

#define dmac_writel_lo(reg, value) \
	__raw_writel((value), DMAC_BASE + DMAC_##reg)

#define dmac_readl_lo(reg) \
	__raw_readl(DMAC_BASE + DMAC_##reg)

#define dmac_chan_writel_hi(chan, reg, value) \
	__raw_writel((value), (DMAC_BASE + 0x58 * (chan) \
			       + DMAC_CHAN_##reg + 4))

#define dmac_chan_readl_hi( chan, reg) \
	__raw_readl(DMAC_BASE + 0x58 * (chan) + DMAC_CHAN_##reg + 4)

#define dmac_chan_writel_lo(chan, reg, value) \
	__raw_writel((value), DMAC_BASE + 0x58 * (chan) + DMAC_CHAN_##reg)

#define dmac_chan_readl_lo(chan, reg) \
	__raw_readl(DMAC_BASE + 0x58 * (chan) + DMAC_CHAN_##reg)

#define set_channel_bit(reg, chan) \
	dmac_writel_lo(reg, (1 << (chan)) | (1 << ((chan) + 8)))

#define clear_channel_bit(reg, chan) \
	dmac_writel_lo(reg, (0 << (chan)) | (1 << ((chan) + 8)))


#define SEND_ADDR	((volatile unsigned char *) 0xa0030000)
#define DEST_ADDR	((volatile unsigned char *) 0xa0005000)


#define dmac_readl(addr)		__raw_readl(addr)
#define dmac_writel(value,addr)		__raw_writel((value), addr)


static void  mem_init(void)
{
	volatile unsigned char * src = SEND_ADDR;
	volatile unsigned char * dst = DEST_ADDR;
	int i = 0;

	for(i = 0; i < 120; i ++)
	{
		* src = i;
		src++;
	}

	for(i = 0; i < 240; i ++)
	{
		* dst = i;
		dst++;
	}

}

/* master 2(0x1)对应内存。master 1(0x0)对应外设 */

int dma_prepare_single(int channel,unsigned char * src, unsigned char * dst, int size, int direction)
{
    unsigned long ctlhi, ctllo, cfghi, cfglo;
    unsigned long width = 2;

    cfghi = dmac_chan_readl_hi(channel,CFG);
    cfglo = dmac_chan_readl_lo(channel,CFG);

    dmac_chan_writel_hi (channel, CFG, cfghi);
    dmac_chan_writel_lo (channel, CFG, cfglo);

    dma_debug("DMA_CFG0_HI = 0x%08x\n", dmac_chan_readl_hi(channel, CFG));
    dma_debug("DMA_CFG0_LO = 0x%08x\n", dmac_chan_readl_lo(channel, CFG));

#if 1
    if (size % (1 << width))
    {
        ctlhi = (size >> width) + 1;
    }
    else
        ctlhi = (size >> width);
#endif /* if 0 end*/

    ctllo = CTLLO_DST_TT_FC (MTM);

    ctllo |= CTLLO_SRC_TR_WIDTH (width);
    ctllo |= CTLLO_DST_TR_WIDTH (width);
    ctllo |= CTLLO_SRC_MSIZE(0);
    ctllo |= CTLLO_DST_MSIZE(0);
    
    if (direction == PTM)
    {
        ctllo |= CTLLO_DMS (1);
        ctllo |= CTLLO_SMS (0);              
    }
    else if (direction == MTP)
    {
        ctllo |= CTLLO_DMS (0);
        ctllo |= CTLLO_SMS (1);    
    }

    dmac_chan_writel_lo (channel, SAR, (unsigned long)src);
    dmac_chan_writel_lo (channel, DAR, (unsigned long)dst);

    dma_debug("DMA_SAR0 = 0x%08x\n", dmac_chan_readl_lo(channel, SAR));
    dma_debug("DMA_DAR0 = 0x%08x\n", dmac_chan_readl_lo(channel, DAR));

    dmac_chan_writel_lo (channel, CTL, ctllo);
    dmac_chan_writel_hi (channel, CTL, ctlhi);

    dma_debug("DMA_CTL0_HI = 0x%08x\n", dmac_chan_readl_hi(channel, CTL));
    dma_debug("DMA_CTL0_LO = 0x%08x\n", dmac_chan_readl_lo(channel, CTL));

    set_channel_bit(CH_EN, channel);

    return 0;

}


int p2m(void)
{
	mem_init();
	dma_init();
	dma_prepare_single(0, (unsigned char *)0x1de00000, (unsigned char *)0x5000, 120, PTM);
	return 0;
}

int m2p(void)
{
	mem_init();
	dma_init();
	dma_prepare_single(0, (unsigned char *)0x5000, (unsigned char *)0x1de00000, 120, MTP);
	return 0;
}


void dma_enable(int channel)
{
    set_channel_bit(CH_EN, channel);
    return ;
}

int dma_init (void)
{
    /* Enable the DMA controller */

    dmac_writel_lo (CFG, 1);

    return 0;
}

int dma_deinit (void)
{
  /* disable the DMA controller */
  dmac_writel_lo (CFG, 0);

  return 0;
}

int dma_check_channel_busy(int channel)
{
    int reg = 0;
    reg = dmac_readl_lo(CH_EN);
    if (reg & (1<<channel))
    {
        dma_debug("channel %d busy\n", channel);
        return 1;
    }
    return 0;
}

int dma_3280_to_fpga(int size)
{
    dma_prepare_single(0, (unsigned char *)EMI_GSC3280_TX_PHYSICAL_BASE, 
                        (unsigned char *)EMI_FPGA_TX_PHYSICAL_BASE, size, MTP);
    return 0;
}

int dma_fpga_to_3280(int size)
{
    dma_prepare_single(0, (unsigned char *)EMI_FPGA_RX_PHYSICAL_BASE, 
                        (unsigned char *)EMI_GSC3280_RX_PHYSICAL_BASE, size, PTM);
    return 0;    
}
