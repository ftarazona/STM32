#include "timer.h"
#include "matrix.h"

static int timer_trigger;

void timer_init(int max_us)	{
	//Enabling TIM2 on APB1
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN);

	//Reseting the timer
	TIM2->CNT = 0;
	TIM2->PSC = 80;	//Prescaler set to tick every us
	TIM2->ARR = max_us;
	SET_BIT(TIM2->DIER, TIM_DIER_UIE);
	SET_BIT(TIM2->CR1, TIM_CR1_CEN);

	//Enabling the IRQ in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}

int timer_triggered(void)	{
	int ret = timer_trigger;
	timer_trigger = 0;
	return ret;
}

void TIM2_IRQHandler(void)	{
	/* IRQ Handler called at every overflow of the timer. */
	CLEAR_BIT(TIM2->SR, TIM_SR_UIF);
	timer_trigger = 1;
}

void active_wait(int n_ticks)	{
	for(int i = 0; i < n_ticks; ++i)	{
		asm volatile("nop");
	}
}
