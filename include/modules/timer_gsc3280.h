#ifndef __TIMER_APP_H__
#define __TIMER_APP_H__

#include <types.h>

#define TIMER_BASE_ADDR 0xbc114000

#define TIMER_GENEGIC_CLK_DIV  0x0

#define TIMER0_CLK_DIV  0x9
#define TIMER1_CLK_DIV  0x9
#define TIMER2_CLK_DIV  0x9
#define TIMER3_CLK_DIV  0x9

#define TIMER0_TLC      0x00
#define TIMER0_TCV      0x04
#define TIMER0_TCR      0x08
#define TIMER0_TOEI     0x0c
#define TIMER0_TIS      0x10

#define TIMER1_TLC      0x14
#define TIMER1_TCV      0x18
#define TIMER1_TCR      0x1c
#define TIMER1_TOEI     0x20
#define TIMER1_TIS      0x24

#define TIMER2_TLC      0x28
#define TIMER2_TCV      0x2c
#define TIMER2_TCR      0x30
#define TIMER2_TOEI     0x34
#define TIMER2_TIS      0x38

#define TIMER3_TLC      0x3c
#define TIMER3_TCV      0x40
#define TIMER3_TCR      0x44
#define TIMER3_TOEI     0x48
#define TIMER3_TIS      0x4c

#define TIMER_TIS       0xa0
#define TIMER_TEOI      0xa4
#define TIMER_TRIS      0xa8

#define TIMER3_IRQ_BIT  (1<<3)
#define TIMER2_IRQ_BIT  (1<<2)
#define TIMER1_IRQ_BIT  (1<<1)
#define TIMER0_IRQ_BIT  (1<<0)



#define TCR_MASK        (1<<2)    /* 0允许中断，1屏蔽中断 */
#define TCR_MODE        (1<<1)    /* 0单次定时模式，1循环定时模式 */
#define TCR_EN          (1<<0)    /* 0关闭定时器，1使能定时器 */

typedef enum
{
    TIMER0 = 0,
    TIMER1,
    TIMER2,
    TIMER3
}TIMER_INDEX;

#ifdef TIMER_DEBUG
#define timer_debug(fmt, args...) printf(fmt, ##args);
#else
#define timer_debug(fmt, args...)
#endif

void timer_init(TIMER_INDEX index, void *arg);
u_int32_t timer_get_count(TIMER_INDEX index);
void timer_irq_handler(void *arg);
void timer_start(TIMER_INDEX index);
void timer_stop(TIMER_INDEX index);
void timer_enable_irq(TIMER_INDEX index);
void timer_disable_irq(TIMER_INDEX index);
void timer_set_oneshot_mode(TIMER_INDEX index);
void timer_set_cycle_mode(TIMER_INDEX index);
void timer_set_reload_count(TIMER_INDEX index, u_int32_t value);
void timer_set_reload_by_us(TIMER_INDEX index, u_int32_t period_us);
void timer_config(TIMER_INDEX index, u_int32_t period_us);


#endif
