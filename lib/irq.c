#include <asm/mipsregs.h>
#include <def.h>
#include <sysctl.h>
#include <stdio.h>
#include <interrupt.h>

#define ICTL_INTEN  0
#define ICTL_INTMASK  0x8
#define ICTL_INTFORCE  0x10
#define ICTL_RAWSTATUS  0x18
#define ICTL_STATUS  0x20
#define ICTL_MASKSTATUS  0x28
struct irq_action {
	irq_handler_t handler;
	void * args;
};
unsigned long exception_handlers[32];
struct irq_action irq_actions[32];
static unsigned long ictl_base = 0xBC048000;

extern void handle_int(void);
extern void handle_reserved(void);

inline void irq_enable(unsigned int irq)
{
	if (irq >= 32)
		return;
	writel((readl(ictl_base+ICTL_INTMASK) & (~(1<<irq))),ictl_base+ICTL_INTMASK);
	writel((readl(ictl_base+ICTL_INTEN) | (1<<irq)),ictl_base+ICTL_INTEN);
}

inline void irq_disable(unsigned int irq)
{
	
	if (irq >= 32)
		return;
	writel((readl(ictl_base+ICTL_INTMASK) | (1<<irq)),ictl_base+ICTL_INTMASK);
	writel((readl(ictl_base+ICTL_INTEN) & (~(1<<irq))),ictl_base+ICTL_INTEN);
}

void handle_test(void)
{
	printf("except\n");
}
void init_irq(void)
{
	int i;
	extern char except_vec3_generic;

	memcpy(0xa0000180,&except_vec3_generic,0x80);
	memcpy(0xbfc00180,&except_vec3_generic,0x80);

	clear_c0_status(ST0_IM | ST0_BEV);
	clear_c0_cause(CAUSEF_IP);

	sysctl_mod_enable(SYSCTL_MOD_ICTL);

	writel(0, ictl_base+ICTL_INTEN);
	writel(0xffffffff, ictl_base+ICTL_INTMASK);
	writel(0, ictl_base+ICTL_INTFORCE);
	
	
	for (i=0; i<32; i++) {
		exception_handlers[i] = handle_reserved;
		irq_actions[i].handler = 0;
		irq_actions[i].args = 0;
	}
	exception_handlers[0] = handle_int;

	set_c0_status(ST0_IE | STATUSF_IP2);
	
}
void irq_dispatch(void)
{
	int i;
	unsigned int irqpending;
	irqpending = readl(ictl_base+ICTL_MASKSTATUS); 

	for (i=0; i<31; i++) {
		if (irqpending & (1<<i)) {
			if (irq_actions[i].handler != 0) {
				irq_disable(i);
				irq_actions[i].handler(irq_actions[i].args);
				irq_enable(i);
			}
			else 
				irq_disable(i);
		}
	} 
}

int request_irq(unsigned int irq, irq_handler_t handler, void * args) 
{
	if (irq >= 32)
		return -1;
	
	irq_actions[irq].handler = handler;
	irq_actions[irq].args = args;
	
	irq_enable(irq);

	return 0;
}

int derequest_irq(unsigned int irq)
{
	if (irq >= 32)
		return -1;
	irq_actions[irq].handler = 0;
        irq_actions[irq].args = 0;
	
	irq_disable(irq);
	
	return 0;
}
