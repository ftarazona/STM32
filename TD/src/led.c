#include "led.h"

/* led_init initializes PB14 in output mode */
void led_init()	{
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);
	GPIOB->MODER = (GPIOB->MODER & 0xcfffffff) | GPIO_MODER_MODER14_0; //Puts PB14 in output mode
	led(LED_OFF);
}

/* led_g_on turns LED2 on. It uses BSRR for atomicity. */
void led_g_on()	{
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS14);
}

/* led_g_off turns LED2 off. It uses BSRR for atomicity. */
void led_g_off()	{
	SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR14);
}

void led(int state)	{
	if(state == LED_OFF)	{
		GPIOC->MODER = (GPIOC->MODER & 0xfff3ffff) | GPIO_MODER_MODER9; //Puts PC9 in input mode (turns both LEDs off)
	} else	{
		GPIOC->MODER = (GPIOC->MODER & 0xfff3ffff) | GPIO_MODER_MODER9_0; //Puts PC9 in output mode (one LED on)
		if(state == LED_YELLOW)	{
			SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS9);
		} else	{
			SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR9);
		}
	}
}
