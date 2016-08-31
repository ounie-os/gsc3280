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

static void GPIO_irq_en(unsigned int GPIO, unsigned int status)
{
    if (0 == status)
    {
        writel((~(1<<GPIO)) & readl(GPIO_INTEN), GPIO_INTEN);
    }
    else
    {
        writel((1<<GPIO) | readl(GPIO_INTEN), GPIO_INTEN);
    }

    gpio_debug("GPIO_INTEN = 0x%08x\n", readl(GPIO_INTEN));
}

void handler_gpio(void *arg)
{
    unsigned int gpio_irq_status = 0;
    GPIO_irq_en(GPIO_EMI_IRQ_RX, 0);    /* 关闭gpio的中断 */    /* 收包 */
    //GPIO_irq_en(GPIO_EMI_IRQ_TX, 0);    /* 关闭gpio的中断 */    /* 发包 */

    gpio_irq_status = readl(GPIO_INTSTATUS);

#if 0
    if (gpio_irq_status & (1 << gpio[0]))
    {
        
    }
#endif /* if 0 end*/

    writel(1 << GPIO_EMI_IRQ_RX, GPIO_PORTA_EOI);    /* 清除中断标志 */

    can_irq_process();

    GPIO_irq_en(GPIO_EMI_IRQ_RX, 1);
    //GPIO_irq_en(GPIO_EMI_IRQ_TX, 1);
}

int GPIOA_Irq_init(unsigned int GPIO, GPIO_INT_LEVEL_TYPE level, GPIO_INT_POLARITY_TYPE polarity)
{
    int ret = 0;

    GPIO_Enable();

    writel((~(1<<GPIO)) & readl(GPIO_SWPORTA_DDR), GPIO_SWPORTA_DDR);    /* 设置为输入 */

    gpio_debug("GPIO_SWPORTA_DDR = 0x%08x\n", readl(GPIO_SWPORTA_DDR));

    if (LEVEL_TRIGGER == level)
    {
        writel((~(1<<GPIO)) & readl(GPIO_INTTYPE_LEVEL), GPIO_INTTYPE_LEVEL);    /* 0电平触发，1边沿触发 */
    }
    else
    {
        writel((1<<GPIO) | readl(GPIO_INTTYPE_LEVEL), GPIO_INTTYPE_LEVEL);
    }

    gpio_debug("GPIO_INTTYPE_LEVEL = 0x%08x\n", readl(GPIO_INTTYPE_LEVEL));

    if (LOW_FALLING_DETECT == polarity)
    {
        writel((~(1<<GPIO)) & readl(GPIO_INT_POLARITY), GPIO_INT_POLARITY);
    }
    else
    {
        writel((1<<GPIO) | readl(GPIO_INT_POLARITY), GPIO_INT_POLARITY);
    }

    gpio_debug("GPIO_INT_POLARITY = 0x%08x\n", readl(GPIO_INT_POLARITY));

    writel((~(1<<GPIO)) & readl(GPIO_INTMASK), GPIO_INTMASK);    /* 不屏蔽中断 */

    gpio_debug("GPIO_INTMASK = 0x%08x\n", readl(GPIO_INTMASK));
    
    ret = request_irq(28, handler_gpio, (void *)0);
    if (0 != ret) 
    {
        printf("handler_gpio fail\n");
        return -1;
    }

    GPIO_irq_en(GPIO, 1);

    return 0;
}
