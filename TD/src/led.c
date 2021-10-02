#include "led.h"

/* led_init initializes PB14 in output mode */
void led_init()	{
	RCC_AHB2ENR |= RCC_GPIOBEN;	//Enables GPIOB clock
	GPIOB_MODER |= GPIO_MODER14_OUTPUT; //Puts PB14 in output mode
}
