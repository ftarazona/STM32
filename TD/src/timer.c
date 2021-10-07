#include "timer.h"

/* timer init initializes the timer TIM2 and links a IRQ */
void timer_init(int max_us)	{
	//Enabling TIM2 on APB1
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN);

	//Reseting the timer
	TIM2->CNT = 0;
	TIM2->PSC = 80;
	TIM2->ARR = max_us << 16;
	SET_BIT(TIM2->DIER, TIM_DIER_TIE);

	//Enabling the IRQ in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(void)	{
	CLEAR_BIT(TIM2->SR, TIM_SR_TIF);
}
