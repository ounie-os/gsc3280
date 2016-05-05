/*----------------------------------------------------------------------------*/
/*
**  File	: gsc3280_mac.h
**  Data	: 2012-12-30
**
**	Note	: For Sort Out <ansonn.wang@gmail.com>
**----------------------------------------------------------------------------*/


#ifndef _GSC3280_MAC_H
#define _GSC3280_MAC_H

#if 0
#include <command.h>
#endif /* if 0 end*/
#include <addrspace.h>
#include <asm/io.h>
#include <net.h>
#if 0
#include <malloc.h>
#endif /* if 0 end*/
#include <stdio.h>
#include <miiphy.h>


#define L1_CACHE_BYTES 32

/*----------------------------------------------------------------------------*/
#define CONFIG_DMA_RX_SIZE 8
#define CONFIG_DMA_TX_SIZE 1					 /* Only ever use 1 tx buffer */

#define likely(x)	__builtin_expect(!!(x), 1)
#define unlikely(x)	__builtin_expect(!!(x), 0)

/*----------------------------------------------------------------------------
 *			CORE MAC Block
 *---------------------------------------------------------------------------*/

/* GSC3280 MAC Control & Status Register (CSR) offsets */
/* GMAC Control & Status Register (CSR) offsets */
#define MAC_CONTROL				0x00000000	/* MAC Configuration */
#define MAC_FRAME_FILTER		0x00000004	/* Frame Filter */
#define MAC_HASH_HIGH			0x00000008	/* Multicast Hash Table High */
#define MAC_HASH_LOW			0x0000000c	/* Multicast Hash Table Low */
#define MAC_MII_ADDR			0x00000010	/* MII Address */
#define MAC_MII_DATA			0x00000014	/* MII Data */
#define MAC_FLOW_CONTROL		0x00000018	/* Flow Control */
#define MAC_ADDR_HIGH			0x00000040	/* MAC Address 0 High */
#define MAC_ADDR_LOW			0x00000044	/* MAC Address 0 Low */
#define MAC_AN_CONTROL			0x000000c0	/* MAC AN Control */
#define MAC_AN_STATUS			0x000000c4	/* MAC AN Status */

/* GMAC Control Register defines */
#define MAC_CONTROL_TC			0x01000000	/* Transmit Conf. in RGMII/SGMII */
#define MAC_CONTROL_WD			0x00800000	/* Disable Watchdog on Receive */
#define MAC_CONTROL_JD			0x00400000	/* Jabber disable */
#define MAC_CONTROL_BE			0x00200000	/* Frame Burst Enable */
#define MAC_CONTROL_JE			0x00100000	/* Jumbo Frame */
#define MAC_CONTROL_IFG_SHIFT	17
#define MAC_CONTROL_IFG_MASK	(0x7 << MAC_CONTROL_IFG_SHIFT) /* Inter-Frame Gap */
#define MAC_CONTROL_DCRS		0x00010000	/* Disable Carrier Sense During TX */
#define MAC_CONTROL_PS			0x00008000	/* Port Select 0:GMI, 1:MII */
#define MAC_CONTROL_FES			0x00004000	/* Speed 0:10, 1:100 */
#define MAC_CONTROL_DO			0x00002000	/* Disable RX Own */
#define MAC_CONTROL_LM			0x00001000	/* Loop-back Mode */
#define MAC_CONTROL_DM			0x00000800	/* Duplex Mode */
#define MAC_CONTROL_IPC			0x00000400	/* Checksum Offload */
#define MAC_CONTROL_DR			0x00000200	/* Disable Retry */
#define MAC_CONTROL_LUD			0x00000100	/* Link Up/Down */
#define MAC_CONTROL_ACS			0x00000080	/* Automatic Pad Stripping */
#define MAC_CONTROL_BL_SHIFT	5
#define MAC_CONTROL_BL_MASK		(0x3 << MAC_CONTROL_BL_SHIFT) /* Back-Off Limit */
#define MAC_CONTROL_DC		0x00000010	/* Deferral Check */
#define MAC_CONTROL_TE			0x00000008	/* Transmitter Enable */
#define MAC_CONTROL_RE			0x00000004	/* Receiver Enable */
#define MAC_CONTROL_PRELEN_SHIFT 0
#define MAC_CONTROL_PRELEN_MASK (0x3 << MAC_CONTROL_PRELEN_SHIFT) /* Preamble Length for Transmit Frames */
#define MAC_CORE_INIT	(MAC_CONTROL_JD | MAC_CONTROL_PS | MAC_CONTROL_ACS | MAC_CONTROL_IPC)


/* MAC Flow Control Register defines */
#define MAC_FLOW_CTRL_PT_MASK	0xffff0000	/* Pause Time Mask */
#define MAC_FLOW_CTRL_PT_SHIFT	16			/* Pause Time Shift */
#define MAC_FLOW_CTRL_TFE		(0x01 << 1)	/* Transmit Flow Control Enable */
#define MAC_FLOW_CTRL_RFE		(0x01 << 2)	/* Receive Flow Control Enable */




//#define GMAC_FLOW_CTRL_FCB_BPA	0x00000001	/* Flow Control Busy ... */
/* STMAC Flow Control Register defines */
/* GMAC Flow Control Register defines */

/* MAC Address High Register defines */
#define MAC_ADDR_HIGH_AE			(0x1 << 31)

/* MII Address defines */
#define MAC_MII_ADDR_PHY_MASK		0x0000001f	/* MII PHY Address Mask */
#define MAC_MII_ADDR_PHY_SHIFT		11		/* MII PHY Address Shift */
#define MAC_MII_ADDR_REG_MASK		0x0000001f	/* MII Register Mask */
#define MAC_MII_ADDR_REG_SHIFT		6		/* MII Register Shift */
#define MAC_MII_ADDR_CR_SHIFT		2		
#define MAC_MII_ADDR_CR_MASK		(0xf << MAC_MII_ADDR_CR_SHIFT) /* CSR Clock Range */
#define MAC_MII_ADDR_WRITE		0x00000002	/* MII Write */
#define MAC_MII_ADDR_BUSY		0x00000001	/* MII Busy */
#define MAC_MII_ADDR_CR_VALUE		(0 << MAC_MII_ADDR_CR_SHIFT) /* 150 MHz, _ONLY_ used for fpga board */

/* MAC AN Control defines */
#define MAC_AN_CONTROL_ELE				(0x1 <<	14) /* Enable External Loopback */
#define MAC_AN_CONTROL_ANE				(0x1 << 12) /* Enable Auto-Negotiation */
#define MAC_AN_CONTROL_RAN				(0x1 << 9)	/* Restart Auto-Negotiation */

/* MAC AN Status defines */
#define MAC_AN_STATUS_ANC				(0x1 << 5) /* Auto-Negotiation Complete */
#define MAC_AN_STATUS_ANA				(0x1 <<	3) /* Auto-Negotiation Ability */
#define MAC_AN_STATUS_LS				(0x1 << 2) /* Link Status, not available for MII Phy */
/*----------------------------------------------------------------------------
 *			MAC Management Counters (MMC) Block
 *---------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *			DMA Block
 *---------------------------------------------------------------------------*/

/* DMA Control & Status Register (CSR) offsets */
#define DMA_BUS_MODE			0x00001000	/* Bus Mode */
#define DMA_XMT_POLL_DEMAND		0x00001004	/* Transmit Poll Demand */
#define DMA_RCV_POLL_DEMAND		0x00001008	/* Receive Poll Demand */
#define DMA_RCV_BASE_ADDR		0x0000100c	/* Receive List Base Address */
#define DMA_TX_BASE_ADDR		0x00001010	/* Transmit List Base Address */
#define DMA_STATUS				0x00001014	/* Status Register */
#define DMA_CONTROL				0x00001018	/* Control (Operational Mode) */
#define DMA_INTR_ENA			0x0000101c	/* Interrupt Enable */
#define DMA_AHB_STATUS			0x0000102c
#define DMA_CUR_TX_DESC_ADDR	0x00001048	/* Current Host Transmit Descriptor */
#define DMA_CUR_RX_DESC_ADDR	0x0000104c	/* Current Host Receive Descriptor */
#define DMA_CUR_TX_BUF_ADDR		0x00001050	/* Current Host Transmit Buffer */
#define DMA_CUR_RX_BUF_ADDR		0x00001054	/* Current Host Receive Buffer */
#define DMA_HW_FEATURE			0x00001058	/* HW Feature */

/* DMA Bus Mode Register defines */
#if 0
#define DMA_BUS_MODE_DBO		0x00100000	/* Descriptor Byte Ordering */
#define DMA_BUS_MODE_BLE		0x00000080	/* Big Endian/Little Endian */
#endif
#define DMA_BUS_MODE_MIXED_BURST	(0x00000001 << 26)
#define DMA_BUS_MODE_AAL			(0x00000001 << 25)
#define DMA_BUS_MODE_8PBL			(0x00000001 << 24)
#define DMA_BUS_MODE_FB				(0x00000001 << 16)
#define DMA_BUS_MODE_PBL_MASK		(0x3f << 8)
#define DMA_BUS_MODE_PBL_SHIFT		8
#define DMA_BUS_MODE_ATDS			(0x00000001 << 7)
#define DMA_BUS_MODE_DSL_MASK		(0x1f << 2)
#define DMA_BUS_MODE_DSL_SHIFT		(2)
#define DMA_BUS_MODE_DA				(0x00000001 << 1)
#define DMA_BUS_MODE_SFT_RESET		0x00000001	/* Software Reset */
#define DMA_BUS_MODE_DEFAULT		0x00000000

/* DMA Status Register defines */
#if 0
#define DMA_STATUS_EB_MASK		0x00380000	/* Error Bits Mask */
#define DMA_STATUS_EB_TX_ABORT	0x00080000	/* Error Bits - TX Abort */
#define DMA_STATUS_EB_RX_ABORT	0x00100000	/* Error Bits - RX Abort */
#endif
#define DMA_STATUS_TS_MASK		0x00700000	/* Transmit Process State */
#define DMA_STATUS_TS_SHIFT		20
#define DMA_STATUS_RS_MASK		0x000e0000	/* Receive Process State */
#define DMA_STATUS_RS_SHIFT		17
#define DMA_STATUS_NIS		0x00010000	/* Normal Interrupt Summary */
#define DMA_STATUS_AIS		0x00008000	/* Abnormal Interrupt Summary */
#define DMA_STATUS_ERI		0x00004000	/* Early Receive Interrupt */
#define DMA_STATUS_FBI		0x00002000	/* Fatal Bus Error Interrupt */
#define DMA_STATUS_ETI		0x00000400	/* Early Transmit Interrupt */
#define DMA_STATUS_RWT		0x00000200	/* Receive Watchdog Timeout */
#define DMA_STATUS_RPS		0x00000100	/* Receive Process Stopped */
#define DMA_STATUS_RU			0x00000080	/* Receive Buffer Unavailable */
#define DMA_STATUS_RI			0x00000040	/* Receive Interrupt */
#define DMA_STATUS_UNF		0x00000020	/* Transmit Underflow */
#define DMA_STATUS_OVF		0x00000010	/* Receive Overflow */
#define DMA_STATUS_TJT		0x00000008	/* Transmit Jabber Timeout */
#define DMA_STATUS_TU			0x00000004	/* Transmit Buffer Unavailable */
#define DMA_STATUS_TPS		0x00000002	/* Transmit Process Stopped */
#define DMA_STATUS_TI			0x00000001	/* Transmit Interrupt */

/* DMA Control (Operation Mode) Register defines */
#define DMA_CONTROL_RSF			(0x1 << 25)
#define DMA_CONTROL_TSF			(0x1 << 21)
#define DMA_CONTROL_TTC_SHIFT	14
#define DMA_CONTROL_TTC_MASK	(0x7 << DMA_CONTROL_TTC_SHIFT)
#define DMA_CONTROL_ST			(0x1 << 13)/* Start/Stop Transmission */
#define DMA_CONTROL_EFC			(0x1 << 8) /* enable hardware flow control */
#define DMA_CONTROL_FEF			(0x1 << 7) /* Forward Error Frame */
#define DMA_CONTROL_FUF			(0x1 << 6) /* Forward Undersized Good Frame */
#define DMA_CONTROL_RTC_SHIFT	3
#define DMA_CONTROL_RTC_MASK	(0x3 << DMA_CONTROL_RTC_SHIFT)
#define DMA_CONTROL_OSF			(0x << 2) /* Operate on Second Frame */
#define DMA_CONTROL_SR			0x00000002	/* Start/Stop Receive */

/* DMA Interrupt Enable Register defines */
#define DMA_INT_ENABLE_NIE		(0x1 << 16) /* Normal Interrupt Enable */
#define DMA_INT_ENABLE_AIE		(0x1 << 15) /* Abnormal Interrupt Enable */
#define DMA_INT_ENABLE_RIE		(0x1 << 6) /* Receive Interrupt Enable */
#define DMA_INT_ENALBE_TIE		(0x1 << 0) /* Transmit Interrupt Enable */

/* DMA DMA AHB or AXI Status Register definitions */
#define DMA_AHB_STATUS_AXWHSTS	0x00000001 /* AHB Master Status */

/*----------------------------------------------------------------------------
 *			MII defines
 *---------------------------------------------------------------------------*/

/* MII Register Offsets */
#define MII_BMCR			0x00		/* Basic Mode Control Register */
#define MII_BMSR			0x01		/* Basic Mode Status Register */
#define MII_PHYSID1			0x02		/* PHY Identifier #1 */
#define MII_PHYSID2			0x03		/* PHY Identifier #2 */
#define MII_ADVERTISE			0x04		/* AN Advertisement Control Register */
#define MII_LPA				0x05		/* AN Link Partner Ability Register */
//#define MII_EXPANSION			0x06		/* AN Expansion Register */
#define MII_GBCR			0x09		/* 1000BASE-T Control Register */
//#define MII_GBSR			0x0A		/* 1000BASE-T Status Register */
#define MII_ADVERTISE_PAUSE 0x0400	/* supports the pause command */

/* National Semi. DP83848C specified PHY registers */
#define MII_RBR				0x17		/* RMII and Bypass Register */
#define MII_RBR_RMII_MODE	0x20		/* 1: RMII, 0: MII */

/* Basic Mode Control Register defines */
//#define BMCR_CTST			0x0080		/* Collision Test */
#define BMCR_FULLDPLX			0x0100		/* Full Duplex */
#define BMCR_ANRESTART			0x0200		/* Auto-Negotiation Restart */
//#define BMCR_ISOLATE			0x0400		/* Disconnect from the MII */
//#define BMCR_PDOWN			0x0800		/* Power-down */
#define BMCR_ANENABLE			0x1000		/* Enable Auto-Negotiation */
#define BMCR_LOOPBACK			0x4000		/* Enable Loop-back Mode */
//#define BMCR_RESET			0x8000		/* Software Reset */
#define BMCR_SPEED1000			0x0040		/* Select 1000Mbps */
#define BMCR_SPEED100			0x2000		/* Select 100Mbps */
#define BMCR_SPEED10			0x0000		/* Select 10Mbps */
#define BMCR_SPEED_MASK			(BMCR_SPEED100|BMCR_SPEED1000)

/* Basic Mode Status Register defines */
//#define BMSR_ERCAP			0x0001		/* Extended Capabilities Registers */
//#define BMSR_JCD			0x0002		/* Jabber Detected */
#define BMSR_LSTATUS			0x0004		/* Link Status */
//#define BMSR_ANEGCAPABLE		0x0008		/* Able to do Auto-Negotiation */
#define BMSR_RFAULT			0x0010		/* Remote Fault Detected */
#define BMSR_ANEGCOMPLETE		0x0020		/* Auto-Negotiation Complete */
#define BMSR_10HALF			0x0800		/* Can do 10Mbps, Half-Duplex */
#define BMSR_10FULL			0x1000		/* Can do 10Mbps, Full-Duplex */
#define BMSR_100HALF			0x2000		/* Can do 100Mbps, Half-Duplex */
#define BMSR_100FULL			0x4000		/* Can do 100Mbps, Full-Duplex */
#define BMSR_100BASE4			0x8000		/* Can do 100Mbps, 4k Packets */

/* Auto-Negotiate Advertisement Control Register defines */
//#define ADVERTISE_SLCT		0x001f		/* Selector Bits */
//#define ADVERTISE_CSMA		0x0001		/* Only Selector Supported */
#define ADVERTISE_10HALF		0x0020		/* Try for 10Mbps Half-Duplex */
#define ADVERTISE_10FULL		0x0040		/* Try for 10Mbps Full-Duplex */
#define ADVERTISE_100HALF		0x0080		/* Try for 100Mbps Half-Duplex */
#define ADVERTISE_100FULL		0x0100		/* Try for 100Mbps Full-Duplex */
#define ADVERTISE_100BASE4		0x0200		/* Try for 100Mbps 4k Packets */
#if 0
#define ADVERTISE_RFAULT		0x2000		/* Say we can Detect Faults */
#define ADVERTISE_LPACK		0x4000		/* Ack Link Partners Response */
#define ADVERTISE_NPAGE		0x8000		/* Next Page Capable */
#define ADVERTISE_FULL (ADVERTISE_100FULL | ADVERTISE_10FULL | ADVERTISE_CSMA)
#define ADVERTISE_ALL (ADVERTISE_10HALF | ADVERTISE_10FULL | ADVERTISE_100HALF | ADVERTISE_100FULL)
#endif
/* Auto-Negotiate Link Partner Ability Register defines */
//#define LPA_SLCT			0x001f		/* Same as Advertise Selector */
//#define LPA_10HALF			0x0020		/* Can do 10Mbps Half-Duplex */
#define LPA_10FULL			0x0040		/* Can do 10Mbps Full-Duplex */
#define LPA_100HALF			0x0080		/* Can do 100Mbps Half-Duplex */
#define LPA_100FULL			0x0100		/* Can do 100Mbps Full-Duplex */

#if 0
#define LPA_100BASE4			0x0200		/* Can do 100Mbps 4k Packets */
#define LPA_RFAULT			0x2000		/* Link Partner Faulted */
#define LPA_LPACK			0x4000		/* Link Partner Acknowledged */
#define LPA_NPAGE			0x8000		/* Next Page Capable */
#define LPA_DUPLEX			(LPA_10FULL | LPA_100FULL)
#define LPA_100			(LPA_100FULL | LPA_100HALF | LPA_100BASE4)
#endif

/* 1000BASE-T Control Register defines */
#define GBCR_1000HALF			0x0100		/* Try for 1000Mbps half-duplex */
#define GBCR_1000FULL			0x0200		/* Try for 1000Mbps full-duplex */

#define CONFIG_PHY_LAN8720A

#if defined(CONFIG_PHY_LAN8720A)

#define LAN8720A_PHY_ID		0x0007c0f0u 
#define LAN8720A_PHY_ID_MASK	0xfffffff0u
#define PHY_SPEC_REG			0x12 /* PHY spec mode register */
#define PHY_ADDR_MSK			0x1f /* PHY Address Mask */
#define PHY_ADDR_SHIFT			0x0

#endif

#if defined(CONFIG_PHY_DP83848C)

/* DP83848C phy identifier values */
#define DP83848C_PHY_ID		0x20005c90u
#define DP83848C_PHY_ID_MASK	0xfffffff0u
#define PHY_CTRL_REG			0x19 /* PHY Control register */
#define PHY_ADDR_MSK			0x1f /* PHY Address Mask */
#define PHY_ADDR_SHIFT			0x0

#endif

/*----------------------------------------------------------------------------
 *			Descriptor Structure
 *---------------------------------------------------------------------------*/
/* This structure is common for both receive and transmit DMA descriptors.
 * A descriptor should not be used for storing more than one frame.
 *
 * NOTE: the 'enhanced' structures are used the GMAC, whereas
 * the 10/100 STMAC uses the older (non-enhanced) structures.
 * */
typedef struct {
	/* Receive descriptor */
	union 
	{
		struct 
		{
			u32 des0;	/* RDES0 or TDES0 */
			u32 des1;	/* RDES1 or TDES1 */
		} u;	
		struct {
			/* RDES0 */
			u32 payload_csum_error:1;
			u32 crc_error:1;
			u32 dribbling:1;
			u32 error_gmii:1;
			u32 receive_watchdog:1;
			u32 frame_type:1;
			u32 late_collision:1;
			u32 ipc_csum_error:1;
			u32 last_descriptor:1;
			u32 first_descriptor:1;
			u32 vlan_tag:1;
			u32 overflow_error:1;
			u32 length_error:1;
			u32 source_filter_fail:1;
			u32 descriptor_error:1;
			u32 error_summary:1;
			u32 frame_length:14;
			u32 filtering_fail:1;
			u32 own:1;
			/* RDES1 */
			u32 buffer1_size:11;
			u32 buffer2_size:11;
			u32 reserved2:2;
			u32 second_address_chained:1;
			u32 end_ring:1;
			u32 reserved1:5;
			u32 disable_ic:1;
		} rx;		/* -- enhanced -- */
		struct {
			/* TDES0 */
			u32 deferred:1;
			u32 underflow_error:1;
			u32 excessive_deferral:1;
			u32 collision_count:4;
			u32 vlan_frame:1;
			u32 excessive_collisions:1;
			u32 late_collision:1;
			u32 no_carrier:1;
			u32 loss_carrier:1;
			u32 payload_error:1;
			u32 frame_flushed:1;
			u32 jabber_timeout:1;
			u32 error_summary:1;
			u32 ip_header_error:1;
			u32 time_stamp_status:1;
			u32 reserved1:13;
			u32 own:1;
			/* TDES1 */
			u32 buffer1_size:11;
			u32 buffer2_size:11;
			u32 time_stamp_enable:1;
			u32 disable_padding:1;
			u32 second_address_chained:1;
			u32 end_ring:1;
			u32 crc_disable:1;
			u32 checksum_insertion:2;
			u32 first_segment:1;
			u32 last_segment:1;
			u32 interrupt:1;
		} tx;		/* -- enhanced -- */
	} des01;

	void * des2;
	void * des3;
} gsc3280_mac_dma_des;


/* DMA structure */
struct gsc3280_mac_dma_t
{
	gsc3280_mac_dma_des 	desc_rx[CONFIG_DMA_RX_SIZE];
	gsc3280_mac_dma_des 	desc_tx[CONFIG_DMA_TX_SIZE];
	unsigned char 		rx_buff[CONFIG_DMA_RX_SIZE * (PKTSIZE_ALIGN)];
	unsigned char 		_dummy[L1_CACHE_BYTES];
} __attribute__ ((aligned (L1_CACHE_BYTES)));

/*----------------------------------------------------------------------------*/
/*			Miscellaneous defines
*/

#define CONFIG_SYS_MIPS_TIMER_FREQ	    (CPU_FREQ_MHZ * 1000000)
#define CFG_HZ                          CONFIG_SYS_MIPS_TIMER_FREQ
#define GSC3280_MAC_MII_POLL_BUSY_DELAY			1000
#define CONFIG_GSC3280_MAC_AUTONEG_TIMEOUT		(10000)
#define CONFIG_GSC3280_MAC_TX_TIMEOUT			(5000)

#define CONFIG_ETHADDR		"DE:AD:BE:EF:01:01"    /* Ethernet address */

/* Recommended STBus Bridge Values for GMAC */
#define STBUS_BRIDGE_OFFSET		0x00007000
#define STBUS_BRIDGE_MAGIC		0x25C608	/* from validation */



/*----------------------------------------------------------------------------*/
/* DP83848C phy identifier values 
*/
#define DP83848C_PHY_ID			0x20005c90u
#define DP83848C_PHY_ID_MASK	0xfffffff0u

/*----------------------------------------------------------------------------*/
#define USE_MII_MODE			0x5a
#define USE_RMII_MODE			0xa5

#define MAC_FRAME_FILTER_RA (0x00000001)
/*----------------------------------------------------------------------------*/

int gsc3280_mac_eth_tx(unsigned char *data, int len);
void gsc3280_mac_eth_rx(void);
int gsc3280_mac_init(void);
void gsc3280_mac_halt(void);
int gsc3280_mac_miiphy_init(void);
int gsc3280_eth_init(void);	
int gsc3280_eth_irq_init(void);
void gsc3280_promisc_mode(ulong flag);



#endif
/*----------------------------------------------------------------------------*/


