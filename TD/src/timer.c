#include "timer.h"
#include "matrix.h"

extern volatile int led_toggle_enable;

/* timer init initializes the timer TIM2 and links a IRQ */
void timer_init(int max_us)	{
	//Enabling TIM2 on APB1
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM2EN);

	//Reseting the timer
	TIM2->CNT = 0;
	TIM2->PSC = 80;
	TIM2->ARR = max_us;
	SET_BIT(TIM2->DIER, TIM_DIER_UIE);
	SET_BIT(TIM2->CR1, TIM_CR1_CEN);

	//Enabling the IRQ in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);
}

/* IRQ Handler called at every overflow of the timer. */
void TIM2_IRQHandler(void)	{
	CLEAR_BIT(TIM2->SR, TIM_SR_UIF);
	display_image();
}

/* nop loop */
void active_wait(int n_ticks)	{
	for(int i = 0; i < n_ticks; ++i)	{
		asm volatile("nop");
	}
}
