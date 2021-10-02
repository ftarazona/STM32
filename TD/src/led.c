#include "led.h"

/* led_init initializes PB14 in output mode */
void led_init()	{
	RCC_AHB2ENR |= RCC_GPIOBEN;	//Enables GPIOB clock
	GPIOB_MODER |= GPIO_MODER14_OUTPUT; //Puts PB14 in output mode
}

/* led_g_on turns LED2 on. It uses BSRR for atomicity. */
void led_g_on()	{
	GPIOB_BSRR |= GPIO_BSRR14_SET;
}

/* led_g_off turns LED2 off. It uses BSRR for atomicity. */
void led_g_off()	{
	GPIOB_BSRR |= GPIO_BSRR14_RESET;
}
