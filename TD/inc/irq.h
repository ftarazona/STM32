#ifndef IRQ_H
#define IRQ_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#define MAKE_DEFAULT_HANDLER(xxx_IRQHandler) \
void __attribute__((weak)) xxx_IRQHandler(void)	{\
	while(1); }\

#define MAKE_DISABLE_HANDLER(xxx_IRQHandler) \
void __attribute__((weak)) xx_IRQHandler(void)	{\
	__disable_irq();	}\

#endif
