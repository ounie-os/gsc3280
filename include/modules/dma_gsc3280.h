#ifndef ___DMA_GSC3280_H__
#define ___DMA_GSC3280_H__

/***************global register*****************************/
#define DMAC_CFG		    0x398
#define DMAC_CH_EN		    0x3a0

#define DMAC_STATUS_XFER	    0x2e8
#define DMAC_STATUS_BLOCK	    0x2f0
#define DMAC_STATUS_ERROR	    0x308

#define DMAC_MASK_XFER	        0x310
#define DMAC_MASK_BLOCK     	0x318
#define DMAC_MASK_ERROR     	0x330

#define DMAC_CLEAR_XFER 	    0x338
#define DMAC_CLEAR_BLOCK	    0x340
#define DMAC_CLEAR_ERROR	    0x358
#define DMAC_CLEAR_SRCTRAN	    0x348
#define DMAC_CLEAR_DSTTRAN	    0x350

#define DMAC_CHAN_CLRTFR       0x338

#define DMAC_STATUS_INT	        0x360


/*********channel register size = 0x58***********************/
/**************n channels = n * 0x58**********************/
#define DMAC_CHAN_SAR	    0x000
#define DMAC_CHAN_DAR	    0x008
#define DMAC_CHAN_LLP	    0x010
#define DMAC_CHAN_CTL	    0x018
#define DMAC_CHAN_SSTAT	    0x020
#define DMAC_CHAN_DSTAT	    0x028
#define DMAC_CHAN_SSTATAR	0x030
#define DMAC_CHAN_DSTATAR	0x038
#define DMAC_CHAN_CFG	    0x040
#define DMAC_CHAN_SGR	    0x048
#define DMAC_CHAN_DSR	    0x050

/**********ctl lo register********************/
#define CTLLO_SCAEN(x)  (x << 18)
#define CTLLO_GATEN(x)  (x << 17)
#define CTLLO_LSEN(x)  (x << 28)
#define CTLLO_LDEN(x)  (x << 27)
#define CTLLO_DMS(x)   (x << 23)    
#define CTLLO_DMSIZE(x)   (x << 11)    
#define CTLLO_SMSIZE(x)   (x << 14)    
#define CTLLO_SMS(x)   (x << 25)    
#define CTLLO_SRC_MSIZE(x)   (x << 14)    
#define CTLLO_DST_MSIZE(x)   (x << 11)    
#define CTLLO_SRC_TR_WIDTH(x)   (x << 4)    
#define CTLLO_DST_TR_WIDTH(x)   (x << 1)    
#define CTLLO_DST_TT_FC(x)      (x << 20)    
#define MTM                     0   
#define MTP                     1
#define PTM                     2
#define PTP                     3

#define EMI_GSC3280_TX_BASE 0xa0005000
#define EMI_GSC3280_RX_BASE 0xa0005200

#define EMI_GSC3280_TX_PHYSICAL_BASE (EMI_GSC3280_TX_BASE - 0xa0000000)
#define EMI_GSC3280_RX_PHYSICAL_BASE (EMI_GSC3280_RX_BASE - 0xa0000000)

#define EMI_FPGA_TX_PHYSICAL_BASE (FPGA_BASE_ADDR_1 - 0xa0000000)
#define EMI_FPGA_RX_PHYSICAL_BASE (FPGA_BASE_ADDR_1 - 0xa0000000 + 0x200)


int dma_init(void);
void dma_enable(int channel);
int dma_deinit(void);
int p2m(void);
int m2p(void);
int dma_check_channel_busy(int channel);
int dma_3280_to_fpga(int size);
int dma_fpga_to_3280(int size);


#ifdef DEBUG
#define dma_debug(fmt, args...) printf(fmt, ##args)
#else
#define dma_debug(fmt, args...)
#endif


#endif /* ___GSC3280_DMAC_H__ */
