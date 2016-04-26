#include <def.h>
#include <sysctl.h>
#include "gpio_gsc3280.h"


void GPIO_Enable(void)
{
    sysctl_mod_enable(SYSCTL_MOD_GPIO);
}


void GPIO_Disable(void)
{
    sysctl_mod_disable(SYSCTL_MOD_GPIO);
}

/*--------------------------------------------------------------------------*/ 
int GPIOA_Set_Dir(unsigned int GPIO,unsigned int Dir){
	writel((~(0x1<<GPIO)) & readl(GPIO_SWPORTA_CTL),GPIO_SWPORTA_CTL);
	if(GPIO_OUTPUT == Dir)
		writel((0x1<<GPIO) | readl(GPIO_SWPORTA_DDR), GPIO_SWPORTA_DDR);
	else if(GPIO_INPUT == Dir)
		writel((~(0x1<<GPIO)) & readl(GPIO_SWPORTA_DDR), GPIO_SWPORTA_DDR);
	else
		return -1;
	return 0;
}

int GPIOB_Set_Dir(unsigned int GPIO,unsigned int Dir){
	writel((~(0x1<<GPIO)) & readl(GPIO_SWPORTB_CTL),GPIO_SWPORTB_CTL);
	if(GPIO_OUTPUT == Dir)
		writel((0x1<<GPIO) | readl(GPIO_SWPORTB_DDR), GPIO_SWPORTB_DDR);
	else if(GPIO_INPUT == Dir)
		writel((~(0x1<<GPIO)) & readl(GPIO_SWPORTB_DDR), GPIO_SWPORTB_DDR);
	else
		return -1;
	return 0;
}

int GPIOC_Set_Dir(unsigned int GPIO,unsigned int Dir){
	writel((~(0x1<<GPIO)) & readl(GPIO_SWPORTC_CTL),GPIO_SWPORTC_CTL);
	if(GPIO_OUTPUT == Dir)
		writel((0x1<<GPIO) | readl(GPIO_SWPORTC_DDR), GPIO_SWPORTC_DDR);
	else if(GPIO_INPUT == Dir)
		writel((~(0x1<<GPIO)) & readl(GPIO_SWPORTC_DDR), GPIO_SWPORTC_DDR);
	else
		return -1;
	return 0;
}
/*--------------------------------------------------------------------------*/ 
void GPIOA_Set_Value(unsigned int GPIO,unsigned int value)
{	
	if(value>0)
		writel((0x1<<GPIO) | readl(GPIO_EXT_PORTA), GPIO_SWPORTA_DR);
	else
		writel((~(0x1<<GPIO)) & readl(GPIO_EXT_PORTA), GPIO_SWPORTA_DR);
}

void GPIOB_Set_Value(unsigned int GPIO,unsigned int value)
{	
	if(value>0)
		writel((0x1<<GPIO) | readl(GPIO_EXT_PORTB), GPIO_SWPORTB_DR);
	else
		writel((~(0x1<<GPIO)) & readl(GPIO_EXT_PORTB), GPIO_SWPORTB_DR);
}

void GPIOC_Set_Value(unsigned int GPIO,unsigned int value)
{	
	if(value>0)
		writel((0x1<<GPIO) | readl(GPIO_EXT_PORTC), GPIO_SWPORTC_DR);
	else
		writel((~(0x1<<GPIO)) & readl(GPIO_EXT_PORTC), GPIO_SWPORTC_DR);
}

/*--------------------------------------------------------------------------*/
unsigned int GPIOA_Get_Value(unsigned int GPIO)
{
	return ((0x1<<GPIO) & readl(GPIO_EXT_PORTA)) >> GPIO;
}

unsigned int GPIOB_Get_Value(unsigned int GPIO)
{
	return ((0x1<<GPIO) & readl(GPIO_EXT_PORTB)) >> GPIO;
}

unsigned int GPIOC_Get_Value(unsigned int GPIO)
{
	return ((0x1<<GPIO) & readl(GPIO_EXT_PORTC)) >> GPIO;
}

/*--------------------------------------------------------------------------*/
void GPIO_Irq_Init(unsigned int GPIO)
{	
	writel((~(1<<GPIO)) & readl(GPIO_SWPORTA_DDR),GPIO_SWPORTA_DDR);
	writel((~(1<<GPIO)) & readl(GPIO_INTTYPE_LEVEL),GPIO_INTTYPE_LEVEL);
	writel((~(1<<GPIO)) & readl(GPIO_INT_POLARITY),GPIO_INT_POLARITY);
	writel((~(1<<GPIO)) & readl(GPIO_INTMASK),GPIO_INTMASK);
	writel((1<<GPIO) | readl(GPIO_INTEN),GPIO_INTEN);
}

void GPIO_Irq_Clear(unsigned int GPIO){
	writel((~(1<<GPIO)) & readl(GPIO_INTEN),GPIO_INTEN);
	writel((1<<GPIO) | readl(GPIO_PORTA_EOI),GPIO_PORTA_EOI);
}
