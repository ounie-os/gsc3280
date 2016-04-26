#include <def.h>
#include <stdio.h>
#include <sysctl.h>
#include <interrupt.h>
#include "timer_gsc3280.h"

#define ref_clk 12000000


static inline void timer_write_reg(unsigned int reg, unsigned int val)
{
    writel(val,TIMER_BASE_ADDR + reg);
}

static inline unsigned int timer_read_reg(unsigned int reg)
{
    return readl(TIMER_BASE_ADDR + reg);
}

static int timer_irq_init(void)
{
    int ret;
    ret = request_irq(26, timer_irq_handler, (void *)0);
    if (0 != ret)
    {
        printf("timer irq init fail...\n");
        return -1;
    }

    return 0;
}

void timer_irq_handler(void *arg)
{
    unsigned int tis;
    tis = timer_read_reg(TIMER_TIS);    /* 读取是哪个定时器产生的中断 */
    timer_read_reg(TIMER_TEOI);    /* 清除所有中断标志 */
}


void generic_timer_init(TIMER_INDEX index)
{
    u32 freq;
    u32 OD1,OD0;
    u32 M,N,NO,pll_rate,dll,ahb,apb;
    freq=readl(SYSCTL_PLL_FREQ);
    M=freq&0x7f;
	N=(freq>>7)&0xf;
	OD1=(freq>>12)&0x1;
	OD0=(freq>>11)&0x1;
	NO=1<<(OD1*2+OD0);
	pll_rate=ref_clk*2*M/(N*NO);
	timer_debug("pll rate = %lu\n", pll_rate);
	
	ahb=readl(SYSCTL_CLKDIV_AHB);
	apb=readl(SYSCTL_CLKDIV_APB);
	dll=pll_rate / ((ahb + 1) * (apb + 1) * ((TIMER3_CLK_DIV + 1) << 1));    /* 定时器是偶数分频，分频系数需要乘以2 */
	timer_debug("timer clock is %lu(0x%08x)\n", dll, dll);

    switch (index)
    {
        case TIMER3:
        {
            sysctl_mod_enable(SYSCTL_MOD_TIMER3);
            writel(TIMER3_CLK_DIV, SYSCTL_CLKDIV_TIMER3);
            timer_irq_init();
            break;   
        }

        case TIMER0:
        case TIMER1:
        case TIMER2:
        default:
        {
            break;
        }
    }

}

void timer_start(TIMER_INDEX index)
{
    u_int32_t tcr;

    switch (index)
    {
        case TIMER3:
        {
            tcr = timer_read_reg(TIMER3_TCR);
            tcr |= TCR_EN;
            timer_write_reg(TIMER3_TCR, tcr);
            break;
        }
        case TIMER0:
        case TIMER1:
        case TIMER2:
        default:
        {
            break;
        }
    }
}

void timer_stop(TIMER_INDEX index)
{
    u_int32_t tcr;
    
    switch (index)
    {
        case TIMER3:
        {
            tcr = timer_read_reg(TIMER3_TCR);
            tcr &= ~TCR_EN;
            timer_write_reg(TIMER3_TCR, tcr);
            break;
        }
        case TIMER0:
        case TIMER1:
        case TIMER2:
        default:
        {
            break;
        }

    }    
}

void timer_enable_irq(TIMER_INDEX index)
{
    u_int32_t tcr;

    switch (index)
    {
        case TIMER3:
        {
            tcr = timer_read_reg(TIMER3_TCR);
            tcr &= ~TCR_MASK;
            timer_write_reg(TIMER3_TCR, tcr);
            break;
        }
        case TIMER0:
        case TIMER1:
        case TIMER2:
        default:
        {
            break;
        }

    }    
}

void timer_disable_irq(TIMER_INDEX index)
{
    u_int32_t tcr;

    switch (index)
    {
        case TIMER3:
        {
            tcr = timer_read_reg(TIMER3_TCR);
            tcr |= TCR_MASK;
            timer_write_reg(TIMER3_TCR, tcr);
            break;
        }
        case TIMER0:
        case TIMER1:
        case TIMER2:
        default:
        {
            break;
        }

    }      
}

void timer_set_oneshot_mode(TIMER_INDEX index)
{
    u_int32_t tcr;
    
    switch (index)
    {
        case TIMER3:
        {
            tcr = timer_read_reg(TIMER3_TCR);
            tcr &= ~TCR_MODE;
            timer_write_reg(TIMER3_TCR, tcr);
            break;
        }
        case TIMER0:
        case TIMER1:
        case TIMER2:
        default:
        {
            break;
        }

    }     
}

void timer_set_cycle_mode(TIMER_INDEX index)
{
    u_int32_t tcr;
    
    switch (index)
    {
        case TIMER3:
        {
            tcr = timer_read_reg(TIMER3_TCR);
            tcr |= TCR_MODE;
            timer_write_reg(TIMER3_TCR, tcr);
            break;
        }
        case TIMER0:
        case TIMER1:
        case TIMER2:
        default:
        {
            break;
        }

    }       
}

u_int32_t timer_get_count(TIMER_INDEX index)
{
    switch (index)
    {
        case TIMER3:
        {
            return timer_read_reg(TIMER3_TCV);
            break;
        }

        case TIMER0:
        case TIMER1:
        case TIMER2:
        default:
        {
            break;
        }
    }
    return 0;
}


void timer_set_reload_count(u_int32_t value)
{
    timer_write_reg(TIMER3_TLC, value);
}


