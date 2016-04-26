#ifndef __HE3250_I2s__
#define __HE3250_I2s__
#define dmac_writel(value,addr)		__raw_writel((value), addr)
#define I2S_BASE      		0xbc112000
#define IER_OFFSET		0x000
#define IRER_OFFSET	 	0x004
#define ITER_OFFSET	 	0x008
#define CER_OFFSET	 	0x00C
#define CCR_OFFSET	 	0x010
#define RXFFR_OFFSET	 	0x014
#define TXFFR_OFFSET	 	0x018

#define LRBR0_OFFSET	 	0x020
#define LTHR0_OFFSET	 	0x020
#define RRBR0_OFFSET		0x024
#define RTHR0_OFFSET		0x024
#define RER0_OFFSET		0x028
#define TER0_OFFSET		0x02C
#define RCR0_OFFSET		0x030
#define TCR0_OFFSET		0x034
#define ISR0_OFFSET		0x038
#define IMR0_OFFSET		0x03C
#define ROR0_OFFSET		0x040
#define TOR0_OFFSET		0x044

#define RFCR0_OFFSET		0x048
#define TFCR0_OFFSET		0x04C
#define RFF0_OFFSET		0x050
#define TFF0_OFFSET		0x054
#define DCTRL_OFFSET		0x200

#define IER_I2SEN		0x1	/*i2s enable 0=disable 1=enable */
#define IER_I2SDIS		0x0	/*i2s disable 0=disable 1=enable */
#define CER_CLKEN		0x1	/* i2S Master Clock generation  0=disable 1=enable */
#define CER_CLKDIS		0x0	/* i2S Master Clock generation  0=disable 1=enable */

#define IRER_RXEN		0x1	/* enable reciver */
#define IRER_RXDIS		0x0	/* disable reciver */
#define ITER_TXEN		0x1	/* enable transmitter */
#define ITER_TXDIS		0x0	/* disable transmitter */

#define WLEN_0		0x000	/* data resolution for the receiver and enable LSB. Must less than or equal to the word size value  0=lgnore word length*/
#define WLEN_12		0x001	/* 1=lgnore word length*/
#define WLEN_16		0x002	/* 2=lgnore word length*/
#define WLEN_20		0x003	/* 3=lgnore word length*/
#define WLEN_24		0x004	/* 4=lgnore word length*/
#define WLEN_32		0x005	/* 5=lgnore word length*/

#define DATA_CYCLE_16				16
#define DATA_CYCLE_24				24
#define DATA_CYCLE_32				32

#define DATA_FORMAT_0				0
#define DATA_FORMAT_12				12
#define DATA_FORMAT_16				16
#define DATA_FORMAT_20				20
#define DATA_FORMAT_24				24
#define DATA_FORMAT_32				32

#define RERx_CHANNELEN		0x001	/* Receiver channel enable each channel independently set after I2S enable and receiver enable. And dependence on channels num used 0=disable 1=enable */
#define RERx_CHANNELDIS		0x000
#define TERx_CHANNELEN		0x001	/* Transmit channel enable each channel independently set after I2S enable and Transmit enable. And dependence on channels num used 0=disable 1=enable */
#define TERx_CHANNELDIS		0x000

/* values for set CCR */
#define CCR_CLK_16		0x000	/* sclk cycles for ws_out stay in master mode 00=16 cycles*/
#define CCR_CLK_24		0x008   /* 01=24 cycles */
#define CCR_CLK_32		0x010   /* 02=32 cycles */
#define CCR_CLKG_0		0x000	/* sclk gate muster greater or equal the largest sclk in mast mode 0=no gating */ 
#define CCR_CLKG_12		0x001	/*  1=12 cycles */ 
#define CCR_CLKG_16		0x002	/*  1=16 cycles */ 
#define CCR_CLKG_20		0x003	/*  1=20 cycles */ 
#define CCR_CLKG_24		0x004	/*  1=24 cycles */ 

#define RXFFR_FIFORESET		0x001	/* RESET Receiver FIFO after disabled Receiver block  1=reset*/
#define TXFFR_FIFORESET		0x001	/* RESET Transmitter FIFO after disabled Transmitter block  1=reset*/

#define RET_ERR -1
#define RET_SUC 1

#define ISRx_RXDA_MASK		0x001	/* interrupt status register. status of receive data available interrupt */
#define ISRx_RXFO_MASK		0x002   /* status of data overrun interrupt  for rx channel*/
#define ISRx_TXFE_MASK		0x010   /* status of transmit fifo empty trigger interrupt */
#define ISRx_TXFO_MASK		0x020   /* status of data overrun interrupt for tx channel fifo */
#define ISRx_RXDA_I		0x001	/* receive data available interrupt reached */
#define ISRx_RXFO_I		0x002	/* receive data available interrupt reached */
#define ISRx_TXFE_I		0x010   /* status of transmit empty trigger interrupt reached */
#define ISRx_TXFO_I		0x020   /* status of data overrun interrupt reached */
void test_channel0_tx(void);
void test_channel0_rx(void);
void set_radio_tx(void);
void set_radio_rx(void);
int test_dma_link(void);
int test_sample_dma_rx(void);
int init_codec(void);
void init_i2s(void);
int init_sysctl_i2s(void);
int i2s_set_sample_cycle(int size);
void inline reset_rx_fifos(void);
void inline reset_tx_fifos(void);
int set_channel_rx_fifo_depth(int depth);
int set_channel_tx_fifo_depth(int depth);
int flush_channel_rx_fifo();
int flush_channel_tx_fifo();
inline int i2s_channel_rx_disable();
inline int i2s_channel_tx_enable();
inline int i2s_channel_tx_enable();
void enable_i2s_dma(void);
inline void enable_trans_block(void);
inline void enable_i2s_clock(void);
int i2s_channel_set_tx_format(int format);
void enable_i2s_dma(void);
inline int i2s_channel_tx_disable();
inline void enable_i2s(void);
#endif

