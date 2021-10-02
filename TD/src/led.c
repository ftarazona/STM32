#include "led.h"

/* led_init initializes PB14 in output mode */
void led_init()	{
	RCC_AHB2ENR |= RCC_GPIOBEN;	//Enables GPIOB clock
	RCC_AHB2ENR |= RCC_GPIOCEN;	//Enables GPIOC clock
	GPIOB_MODER = (GPIOB_MODER & 0xcfffffff) | GPIO_MODER14_OUTPUT; //Puts PB14 in output mode
	led(LED_OFF);
}

/* led_g_on turns LED2 on. It uses BSRR for atomicity. */
void led_g_on()	{
	GPIOB_BSRR |= GPIO_BSRR14_SET;
}

/* led_g_off turns LED2 off. It uses BSRR for atomicity. */
void led_g_off()	{
	GPIOB_BSRR |= GPIO_BSRR14_RESET;
}

void led(int state)	{
	if(state == LED_OFF)	{
		GPIOC_MODER = (GPIOC_MODER & 0xfff3ffff) | GPIO_MODER9_INPUT; //Puts PC9 in input mode (turns both LEDs off)
	} else	{
		GPIOC_MODER = (GPIOC_MODER & 0xfff3ffff) | GPIO_MODER9_OUTPUT; //Puts PC9 in output mode (one LED on)
		if(state == LED_YELLOW)	{
			GPIOC_BSRR |= GPIO_BSRR9_SET;
		} else	{
			GPIOC_BSRR |= GPIO_BSRR9_RESET;
		}
	}
}
