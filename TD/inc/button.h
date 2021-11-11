/* button.h -- Button driver
 ***************************
 * This header declares proper functions for initializing and using
 * the built-in user button available on the STM32L475VG.
 *
 * It is possible to detect a falling trigger on the button. 
 * */

#ifndef BUTTON_H
#define BUTTON_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

void button_init(void);

/* Meant to be called from a user's program. */
int button_triggered();

/* Overwrites the default IRQ Handler for button trigger. */
void EXTI15_10_IRQHandler(void);

#endif
