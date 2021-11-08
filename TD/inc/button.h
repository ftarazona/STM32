#ifndef BUTTON_H
#define BUTTON_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#include "led.h"

/* Initialization. MUST BE CALLED BEFORE ANY BUTTON MANIPULATION */
void button_init(void);

int button_triggered();

/* Overwrites the default IRQ Handler for button trigger.
 * Enables the led toggle. */
void EXTI15_10_IRQHandler(void);

#endif
