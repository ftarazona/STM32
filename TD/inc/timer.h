/* timer.h -- General purpose timers Driver
 * ****************************************
 * This header declares proper functions for using a general purpose
 * timer, TIM2.
 * */

#ifndef TIMER_H
#define TIMER_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#include "led.h"

void timer_init(int max_us);

int timer_triggered(void);

/* Overwrites the default IRQ Handler. */
void TIM2_IRQHandler(void);

/* Enters a nop loop for waiting a given number of ticks. */
void active_wait(int n_ticks);

#endif
