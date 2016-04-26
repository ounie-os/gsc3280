/******************************************************
 * address.h define the address space for all device.
 * all all default define is K1 address.
 * if want k0 address use K0ADDR macro.
 ******************************************************/
#ifndef _ADDRESS_H_
#define _ADDRESS_H_
/* Common Segment Base */
#define KUBASE	0x00000000
#define K1BASE	0xA0000000
#define K0BASE	0x80000000
#define K2BASE  0xC0000000

#define K1ADDR(addr) ((void*)((K1BASE) | ((u32)(addr))))

#define PHY_ADDR(addr) \
    (((unsigned int)addr >= 0x80000000 && (unsigned int)addr < 0xa0000000)? \
    (unsigned int)addr-0x80000000:(unsigned int)addr >= 0xa0000000? \
    (unsigned int)addr-0xa0000000:(unsigned int)addr) 

/******************************************************
 * define serial com port base address
 ******************************************************/
#define COM0_BASE_ADDR		0xbf004080	
#define COM1_BASE_ADDR		0xbf004090

/******************************************************
 * define LCD base address
 ******************************************************/
#define LCD_BASE_ADDR		0xbf001000

/******************************************************
 * define PCI Mem & IO base address
 ******************************************************/
#define PCI_IO_BASE_ADDR         0xBFD00000
#define PCI_MEM_BASE_ADDR        0xB0000000

/******************************************************
 * define PCI Configure Data & Address base address
 ******************************************************/
#define PCI_CONF_ADDR_REG_ADDR 	0xBF0021E0
#define PCI_CONF_DATA_REG_ADDR	0xBF0021E4

/******************************************************
 * define MAC base address
 ******************************************************/
#define MAC_BASE_ADDR		0xBF005200	

/******************************************************
 * define MAC base address
 ******************************************************/
#define AC97_BASE_ADDR		0xBF004200
#define DMA_BASE_ADDR		0xBF004280

/******************************************************
 * define I2C base address
 ******************************************************/
#define I2C_BASE_ADDR		0xBF0040D0


/******************************************************
 * define I2C base address
 ******************************************************/
#define NAND_DATA_ADDR		0xBF000040
#define NAND_COMMAND_ADDR	0xBF000010
#define NAND_ADDR_REG_ADDR	0xBF000014
#define NAND_CONFIG_REG_ADDR	0xBF00000C
#endif
