#include <asm/mipsregs.h>

#define CONFIG_SYS_HZ	1000
static unsigned long timestamp;

/* how many counter cycles in a jiffy */
#if 0
#define CYCLES_PER_JIFFY	(CPU_FREQ_MHZ*1000000 + CONFIG_SYS_HZ / 2) / CONFIG_SYS_HZ    /* 2ms */
#endif /* if 0 end*/

/* 此处除以2的原因是cp0计数器每隔2个时钟周期才加1 */
/* 按照250MHz的频率计算，计数器1秒钟计数125000000次。即8ns累加一次 */
#define CYCLES_PER_JIFFY	(((CPU_FREQ_MHZ * 1000000) / CONFIG_SYS_HZ) / 2)    /* 1ms */


/*
 * timer without interrupts
 */

#if 0
int timer_init(void)
{
	/* Set up the timer for the first expiration. */
	timestamp = 0;
	write_c0_compare(read_c0_count() + CYCLES_PER_JIFFY);

	return 0;
}
#endif /* if 0 end*/

void reset_timer(void)
{
	timestamp = 0;
	write_c0_compare(read_c0_count() + CYCLES_PER_JIFFY);
}

unsigned long get_timer(unsigned long base)
{
	unsigned int count;
	unsigned int expirelo = read_c0_compare();

	/* Check to see if we have missed any timestamps. */
	count = read_c0_count();
	while ((count - expirelo) < 0x7fffffff) {
		expirelo += CYCLES_PER_JIFFY;
		timestamp++;
	}
	write_c0_compare(expirelo);

	return (timestamp - base);
}

void set_timer(unsigned long t)
{
	timestamp = t;
	write_c0_compare(read_c0_count() + CYCLES_PER_JIFFY);
}

void __udelay(unsigned long usec)
{
	unsigned int tmo;

	tmo = read_c0_count() + (usec * CPU_FREQ_MHZ)/2;
	while ((tmo - read_c0_count()) < 0x7fffffff)
		/*NOP*/;
}

/*
 * This function is derived from PowerPC code (read timebase as long long).
 * On MIPS it just returns the timer value.
 */
unsigned long long get_ticks(void)
{
	return get_timer(0);
}

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On MIPS it returns the number of timer ticks per second.
 */
unsigned long get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}
