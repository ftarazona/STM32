#ifndef BUTTON_H
#define BUTTON_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#include "led.h"

void button_init(void);
void EXTI1_IRQHandler(void);

#endif
