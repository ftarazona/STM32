/* irq.h -- interruption vector declaration
 * ****************************************
 * This header allows interruptions from Cortex-M4.
 * */

#ifndef IRQ_H
#define IRQ_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#define N_IRQ 98

#define MAKE_DEFAULT_HANDLER(xxx_IRQHandler) \
void __attribute__((weak)) xxx_IRQHandler(void)	{\
	__disable_irq(); while(1); }\

extern void * vector_table[N_IRQ];

void irq_init(void);

#endif
