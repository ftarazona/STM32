#include "button.h"

/* button_init initializes the user button and links it to an IRQ */
void button_init(void)	{
	//Initializing the pin PC13
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE13_Msk);

	//COnfiguring the line for external interrupts
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
	SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~SYSCFG_EXTICR4_EXTI13_Msk) | SYSCFG_EXTICR4_EXTI13_PC;

	//Configuring and enabling the irq
	SET_BIT(EXTI->IMR1, EXTI_IMR1_IM13);
	SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT13);
	CLEAR_BIT(EXTI->RTSR1, EXTI_RTSR1_RT13);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* The IRQHandler associated to the button toggles the green led. */
void EXTI15_10_IRQHandler(void)	{
	SET_BIT(EXTI->PR1, EXTI_PR1_PIF13);
	led_toggle();
}
