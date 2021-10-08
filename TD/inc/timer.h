#ifndef TIMER_H
#define TIMER_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#include "led.h"

void timer_init(int max_us);
void TIM2_IRQHandler(void);

void active_wait(int n_ticks);

#endif
