#ifndef __TIMER_APP_H__
#define __TIMER_APP_H__

#include <types.h>

#define TIMER_BASE_ADDR 0xbc114000
#define TIMER3_CLK_DIV  0x9

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

#ifdef DEBUG
#define timer_debug(fmt, args...) printf(fmt, ##args);
#else
#define timer_debug(fmt, args...)
#endif

typedef void (*rt_handler_t)();


void generic_timer_init(TIMER_INDEX index, void *arg);
u_int32_t timer_get_count(TIMER_INDEX index);
void timer_irq_handler(void *arg);
void timer_start(TIMER_INDEX index);
void timer_stop(TIMER_INDEX index);
void timer_enable_irq(TIMER_INDEX index);
void timer_disable_irq(TIMER_INDEX index);
void timer_set_oneshot_mode(TIMER_INDEX index);
void timer_set_cycle_mode(TIMER_INDEX index);
void timer_set_reload_count(u_int32_t value, TIMER_INDEX index);
void timer_set_reload_by_ms(u_int32_t period_ms, TIMER_INDEX index);
void timer_setup_by_ms(u_int32_t period_ms, TIMER_INDEX index);





#endif
