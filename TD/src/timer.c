#include "timer.h"

/* timer init initializes the timer TIM2 and links a IRQ */
void timer_init(int max_us)	{
	//Enabling TIM2 on APB1
	SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM2EN);

	//Reseting the timer
	TIM2->CNT = 0;
	TIM2->PSC = 80;
}
