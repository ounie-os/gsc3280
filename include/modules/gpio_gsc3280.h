#ifndef __GPIO_H__
#define __GPIO_H__

#include "def.h"

#define GPIO_BASE 0xBC110000

#define GPIO_SWPORTA_DR 0x0 + GPIO_BASE
#define GPIO_SWPORTA_DDR 0x04 + GPIO_BASE
#define GPIO_SWPORTA_CTL 0x08 + GPIO_BASE

#define GPIO_SWPORTB_DR 0x0c + GPIO_BASE
#define GPIO_SWPORTB_DDR 0x10 + GPIO_BASE
#define GPIO_SWPORTB_CTL 0x14 + GPIO_BASE

#define GPIO_SWPORTC_DR 0x18 + GPIO_BASE
#define GPIO_SWPORTC_DDR 0x1C + GPIO_BASE
#define GPIO_SWPORTC_CTL 0x20 + GPIO_BASE

#define GPIO_EXT_PORTA 0x50 + GPIO_BASE
#define GPIO_EXT_PORTB 0x54 + GPIO_BASE
#define GPIO_EXT_PORTC 0x58 + GPIO_BASE

#define GPIO_INTMASK 0x34 + GPIO_BASE
#define GPIO_INTTYPE_LEVEL 0x38 + GPIO_BASE
#define GPIO_INT_POLARITY 0x3c + GPIO_BASE
#define GPIO_PORTA_EOI	0x4c + GPIO_BASE
#define GPIO_INTEN 0x30 + GPIO_BASE
#define GPIO_INTSTATUS 0x40 + GPIO_BASE
#define GPIO_DEBOUNCE 0x48 + GPIO_BASE
#define GPIO_RAW_INTSTATUS 0x44 + GPIO_BASE

#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

#define GPIO_EMI_IRQ_RX (24)
#define GPIO_EMI_IRQ_SYNC (25)

typedef enum
{
    LEVEL_TRIGGER = 0,
    EDGE_TRIGGER  = 1,
}GPIO_INT_LEVEL_TYPE;

typedef enum
{
    LOW_FALLING_DETECT = 0,
    HIGH_RISING_DETECT = 1,
}GPIO_INT_POLARITY_TYPE;


extern void GPIO_Enable(void);
extern void GPIO_Disable(void);

extern int GPIOA_Set_Dir(unsigned int GPIO,unsigned int Dir);
extern int GPIOB_Set_Dir(unsigned int GPIO,unsigned int Dir);
extern int GPIOC_Set_Dir(unsigned int GPIO,unsigned int Dir);

extern void GPIOA_Set_Value(unsigned int GPIO,unsigned int value);
extern void GPIOB_Set_Value(unsigned int GPIO,unsigned int value);
extern void GPIOC_Set_Value(unsigned int GPIO,unsigned int value);

extern unsigned int GPIOA_Get_Value(unsigned int GPIO);
extern unsigned int GPIOB_Get_Value(unsigned int GPIO);
extern unsigned int GPIOC_Get_Value(unsigned int GPIO);

extern void GPIO_Irq_Init(unsigned int GPIO);
extern void GPIO_Irq_Clear(unsigned int GPIO);

void gpio_init(void);

#define gpio_disable_int() \
{ \
    writel(0xffffffff, GPIO_INTMASK); \
} \

#define gpio_enable_int() \
{ \
    writel(0x0, GPIO_INTMASK); \
} \



#ifdef GPIO_DEBUG
#define gpio_debug(fmt, args...) printf(fmt, ##args)
#else
#define gpio_debug(fmt, args...)
#endif


#endif
