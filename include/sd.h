#ifndef __SD_H__
#define __SD_H__

//#define SD_BASE 0xbc00a000
#define SD_BASE 0xbc046000
#define CTRL		(SD_BASE + 0x00)
#define PWREN		(SD_BASE + 0x04)
#define CLKDIV		(SD_BASE + 0x08)
#define CLKSRC		(SD_BASE + 0x0c)
#define CLKENA		(SD_BASE + 0x10)
#define TMOUT		(SD_BASE + 0x14)
#define CTYPE		(SD_BASE + 0x18)
#define BLKSIZ		(SD_BASE + 0x1c)
#define BYTCNT		(SD_BASE + 0x20)
#define INTMASK		(SD_BASE + 0x24)
#define CMDARG		(SD_BASE + 0x28)
#define CMD		(SD_BASE + 0x2c)
#define RESP0		(SD_BASE + 0x30)
#define RESP1		(SD_BASE + 0x34)
#define RESP2		(SD_BASE + 0x38)
#define RESP3		(SD_BASE + 0x3c)
#define MINTSTS		(SD_BASE + 0x40)
#define RINTSTS		(SD_BASE + 0x44)
#define STATUS		(SD_BASE + 0x48)
#define FIFOTH		(SD_BASE + 0x4c)
#define CDETECT		(SD_BASE + 0x50)
#define WRTPRT		(SD_BASE + 0x54)
#define GPIO		(SD_BASE + 0x58)
#define TCBCNT		(SD_BASE + 0x5c)
#define TBBCNT		(SD_BASE + 0x60)
#define DEBNCE		(SD_BASE + 0x64)
#define USRID		(SD_BASE + 0x68)
#define VERID		(SD_BASE + 0x6C)
#define HCON		(SD_BASE + 0x70)
#define UHS_REG		(SD_BASE + 0x74)
#define RST		(SD_BASE + 0x78)
#define BMOD		(SD_BASE + 0x80)
#define PLDMND		(SD_BASE + 0x84)
                                       
/* for cmd register */
#define USE_IDMAC	(1 << 25)
#define EN_OD_PULLUP	(1 << 24)

#define CARD_VOL_B_M	(0xf << 20)
#define CARD_VOL_A_M	(0xf << 16)

#define EN_ATA_INT	(1 << 11)
#define SENT_AUTO_STOP	(1 << 10)
#define SEND_CCSD	(1 << 9)
#define ABORT_READ_DATA (1 << 8)	//SDIO must set
#define SEND_IRQ_RESP	(1 << 7)
#define	READ_WAIT	(1 << 6)	//for SDIO card
#define DMA_EN		(1 << 5)
#define INT_EN		(1 << 4)
#define DMA_RESET	(1 << 2)
#define FIFO_RESET	(1 << 1)
#define CTRL_RESET	(1 << 0)


#define PWR_ON		1
#define PWR_OFF		0

#define CLKDIV_LM	0xFF
#define CLKDIV0		0
#define CLKDIV1		8
#define CLKDIV2		16
#define CLKDIV3		24

#define SEL_CLKDIV0	00b
#define SEL_CLKDIV1	01b
#define	SEL_CLKDIV2	11b
#define SEL_CLKDIV3	11b

#define CLK_EN		1
#define CLK_DIS		0
#define CLK_LOW_POWER	16

#define INT_CardD	0
#define INT_RE		1
#define INT_CmdD	2
#define INT_DTO		3
#define INT_TXDR	4
#define INT_RXDR	5
#define INT_RCRC	6
#define INT_DCRC	7
#define INT_RTO		8
#define INT_DRTO	9
#define INT_HTO		10
#define INT_FRUN	11
#define INT_HLE		12
#define INT_SBE		13
#define INT_ACD		14
#define INT_EBE		15

#define INT_CardD_M	(1 << INT_CardD)
#define INT_RE_M	(1 << INT_RE)
#define INT_CmdD_M	(1 << INT_CmdD)
#define INT_DTO_M	(1 << INT_DTO)
#define INT_TXDR_M	(1 << INT_TXDR)
#define INT_RXDR_M	(1 << INT_RXDR)
#define INT_RCRC_M	(1 << INT_RCRC)
#define INT_DCRC_M	(1 << INT_DCRC)
#define INT_RTO_M	(1 << INT_RTO)
#define INT_DRTO_M	(1 << INT_DRTO)
#define INT_HTO_M	(1 << INT_HTO)
#define INT_FRUN_M	(1 << INT_FRUN)
#define INT_HLE_M	(1 << INT_HLE)
#define INT_SBE_M	(1 << INT_SBE)
#define INT_ACD_M	(1 << INT_ACD)
#define INT_EBE_M	(1 << INT_EBE)
#define INT_SDIO0_M	(1 << 16)
#define INT_SDIO1_M	(1 << 17)
#define INT_SDIO2_M	(1 << 18)
#define INT_SDIO3_M	(1 << 19)
#define INT_SDIO4_M	(1 << 20)
#define INT_SDIO5_M	(1 << 21)
#define INT_SDIO6_M	(1 << 22)
#define INT_SDIO7_M	(1 << 23)
#define INT_SDIO8_M	(1 << 24)
#define INT_SDIO9_M	(1 << 25)
#define INT_SDIO10_M	(1 << 26)
#define INT_SDIO11_M	(1 << 27)
#define INT_SDIO12_M	(1 << 28)
#define INT_SDIO13_M	(1 << 29)
#define INT_SDIO14_M	(1 << 30)
#define INT_SDIO15_M	(1 << 31)

#define START_CMD	(1 << 31)
#define HOLD_REG	(1 << 29)
#define VOLT_SW		(1 << 28)		//command 11 only
#define ALT_BOOT	(1 << 27)
#define DIS_BOOT	(1 << 26)
#define EX_BOOT_ACK	(1 << 25)
#define EN_BOOT		(1 << 24)
#define CCS_EX		(1 << 23)
#define PERFORM_READ	(1 << 22)
#define UP_CLK_REG	(1 << 21)
#define SEND_INIT	(1 << 15)
#define STOP_CMD	(1 << 14)
#define WAIT_DATA_CMPL	(1 << 13)
#define SEND_STOP	(1 << 12)
#define STREM_MODE	(1 << 11)		//default block mode
#define WRITE_TO_CARD	(1 << 10)		//0: READ
#define DATA_TX_EXP	(1 << 9)
#define CHK_RESP_CRC	(1 << 8)
#define RESP_LONG	(1 << 7)		//0: short
#define RESP_EX		(1 << 6)		


#define DMA_REQ		31
#define DMA_ACK		30
#define FIFO_CNT	17
#define FIFO_CNT_MASK	0x1fff		/*(29 - 17) */
#define RESP_INDEX	11
#define RESP_INDEX_MASK 0x3f		/*(16 - 11)*/
#define DATA_STATE_BUSY	10
#define DATA_BUSY	9
#define DATA_3		8
#define CMD_FSM_STATES	4
#define CMD_FSM_MASK	0xf  		/*(7 - 4) */
#define FIFO_FULL	3
#define FIFO_EMPTY	2
#define FIFO_TX_WATERMARK 1
#define FIFO_RX_WATERMARK 0


#define SD_MMC		0
#define SD		1
#define MMC_O		0
#define CARDS_NUM_M	1
#define BUS_TYPE	6
#define AHB		1
#define APB		0
#define DATA_WIDTH	7
#define DW_16BITS	0
#define DW_32BITS	1b
#define DW_64BITS	10B
#define ADD_WIDTH	10


#define SDIO_CCCR_CCCR	0x0
#define SDIO_CCCR_SD	0x01
#define SDIO_CCCR_IOEx	0x02
#define SDIO_CCCR_IORx	0x03
#define SDIO_CCCR_IENx	0x04
#define SDIO_CCCR_INTx	0x05

#define SDIO_CCCR_ABORT	0x06
#define SDIO_CCCR_IF	0x07
#define SDIO_CCCR_CAPS	0x08
#define SDIO_CCCR_CAP_SDC	0x01
#define SDIO_CCCR_CAP_SMB	0x02
#define SDIO_CCCR_CAP_SRW	0x04
#define SDIO_CCCR_CAP_BUS	0x07
#define SDIO_CCCR_CAP_SBS	0x08
#define SDIO_CCCR_CAP_S4MI	0x10
#define SDIO_CCCR_CAP_E4MI	0x20


#define SDIO_CCCR_CIS	0x09
#define SDIO_CCCR_SUSPEND	0x0c
#define SDIO_CCCR_SELx	0x0d
#define SDIO_CCCR_EXECx	0x0e
#define SDIO_CCCR_READYx	0x0f
#define SDIO_CCCR_BLKSIZE	0x10
#define SDIO_CCCR_POWER	0x12
#define SDIO_CCCR_SPEED	0x13

#define SDIO_FBR_BASE(f) ((f) * 0x100)
#define SDIO_FBR_STD_IF	0x00
#define SDIO_FBR_SUPPORTS_CSA	0x40
#define SDIO_FBR_ENABLE_CSA	0x80
#define SDIO_FBR_STD_IF_EXT	0x01
#define SDIO_FBR_POWER	0x02
#define SDIO_FBR_POWER_SPS	0x01
#define SDIO_FBR_POWER_EPS	0x02
#define SDIO_FBR_CIS	0x09
#define SDIO_FBR_CSA	0x0C
#define SDIO_FBR_CSA_DATA	0x0f
#define SDIO_FBR_BLKSIZE	0x10

test_sdmem();
#endif
