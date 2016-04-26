#ifndef __INTERRUPT_H
#define __INTERRUPT_H

typedef void (*irq_handler_t)(void *);
void init_irq(void);
int request_irq(unsigned int irq, irq_handler_t handler, void * args);
int derequest_irq(unsigned int irq);
#endif
