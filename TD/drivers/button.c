#include "button.h"

static int button_trigger = 0;

void button_init(void)	{
	/* button_init initializes the user button and links it to an IRQ.
	 * The user button is controlled by pin PC13.
	 * The clock for GPIOC is activated,PC13 is set in input mode.
	 * The falling trigger is set to activate an external interrupt */
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE13_Msk);

	//Configuring the line for external interrupts
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
	SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~SYSCFG_EXTICR4_EXTI13_Msk) | SYSCFG_EXTICR4_EXTI13_PC;

	//Configuring and enabling the irq for falling trigger
	SET_BIT(EXTI->IMR1, EXTI_IMR1_IM13);
	SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT13);
	CLEAR_BIT(EXTI->RTSR1, EXTI_RTSR1_RT13);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
}

int button_triggered()	{
	int ret = button_trigger;
	button_trigger = 0;
	return ret;
}

void EXTI15_10_IRQHandler(void)	{
	/* The IRQ is meant to be used by main for triggering time-taking
	 * tasks. The handler simply sets a flag variable. */
	SET_BIT(EXTI->PR1, EXTI_PR1_PIF13);
	button_trigger = 1;
}
