#ifndef TIMER_H
#define TIMER_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#include "led.h"

/* Initialization. MUST BE CALLED BEFORE ANY USE OF TIMER. */
void timer_init(int max_us);

int timer_triggered_display(void);
int timer_triggered_accelerometer(void);
int timer_triggered_refresh(void);

/* Overwrites the default IRQ Handler.
 * If led can be toggled, then it is toggled. */
void TIM2_IRQHandler(void);

/* Enters a nop loop for waiting a given number of ticks. */
void active_wait(int n_ticks);

#endif
