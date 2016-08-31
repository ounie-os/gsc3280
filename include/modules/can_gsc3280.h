#ifndef _CAN_APP_H_
#define _CAN_APP_H_

#include <can.h>

#define CAN_BAUDRATE (500000)

#define ACR  (0x1100)
#define AMR  (0xffffffff)

/* bare_can common registers */
#define CAN_BASE_ADDR	0xbc100000
#define REG_MOD		0x00
#define REG_CMR		0x04
#define REG_SR		0x08
#define REG_IR		0x0c
#define REG_IER		0x10
#define REG_BTR		0x14
#define REG_ALC		0x18
#define REG_ECC		0x1c
#define REG_EWLR	0x20
#define REG_RXERR	0x24
#define REG_TXERR	0x28
#define REG_RMC		0x2c

/* bare_can registers (reset mode)*/
#define REG_ACR		0x80
#define REG_AMR		0x84

/* bare_can registers (work mode)*/
#define REG_RXB1	0x80
#define REG_RXB2	0x84
#define REG_RXB3	0x88
#define REG_RXB4	0x8c
#define REG_TXB1	0x80
#define REG_TXB2	0x84
#define REG_TXB3	0x88
#define REG_TXB4	0x8c

/* mode register */
#define MOD_WK		0x00
#define MOD_RM		0x01
#define MOD_LOM		0x02
#define MOD_STM		0x04
#define MOD_AFM		0x08
#define MOD_SM		0x10

/* commands */
#define CMD_SRR		0x10
#define CMD_CDO		0x08
#define CMD_RRB		0x04
#define CMD_AT		0x02
#define CMD_TR		0x01

/* status register content */
#define SR_BS		0x80
#define SR_ES		0x40
#define SR_TS		0x20
#define SR_RS		0x10
#define SR_TCS		0x08
#define SR_TBS		0x04
#define SR_DOS		0x02
#define SR_RBS		0x01

#define SR_CRIT (SR_BS|SR_ES)

/* interrupt sources */
#define IRQ_BEI		0x80
#define IRQ_ALI		0x40
#define IRQ_EPI		0x20
#define IRQ_WUI		0x10
#define IRQ_DOI		0x08
#define IRQ_EI		0x04
#define IRQ_TI		0x02
#define IRQ_RI		0x01
/*IER*/
#define IRQ_ALL		0xFF
#define IRQ_OFF		0x00

/* ECC register */
#define ECC_SEG		0x1F
#define ECC_DIR		0x20
#define ECC_MASK	0xc0

/*TX/RX BUFFER*/
#define FI_FF		0x80
#define FI_RTR		0x40
/**
 * struct can_frame - basic CAN frame structure
 * @can_ff:  the CAN_*_FLAG flags and the data length field of the can frame, see above.
 * @can_id:  the CAN ID of the frame and CAN_*_FLAG flags, see above.
 * @data:    the CAN frame payload.
 */
struct can_frame {
	unsigned int  can_ff;  /* EFF/RTR flags,data length*/
	unsigned int  can_id;  /* 32 bit CAN_ID */
	unsigned int  data[2];
};

void can_init(int mode, int acc, int filter, int brg);
unsigned int can_rx(Message *m);
//int can_tx(int ff ,int id, unsigned int  *data,unsigned int len);
int can_tx (Message const *m);
int can_irq_init(unsigned int enable_bits);
void can_irq_process(void);


#ifdef DEBUG
#define can_debug(fmt, args...) printf(fmt, ##args);
#else
#define can_debug(fmt, args...)
#endif


#endif /* _CAN_H_ */
