#include "led.h"

volatile int led_toggle_enable = 1;

/* led_init initializes user leds 2 and 9.
 * User LED2 is controlled by pin PB14, LED9 by PC9.
 * First it activates the clocks for GPIOs B/C.
 * PB14 is set in output mode, LED3/4 are more complex, therefore
 *  controlled by a dedicated function. */
void led_init()	{
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);
	
	GPIOB->MODER = (GPIOB->MODER & 0xcfffffff) | GPIO_MODER_MODER14_0;
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

/* led_state returns true if user LED2 is turned on, false otherwise */
int led_on()	{
	return GPIOB->ODR & GPIO_ODR_OD14;
}

/* led_toggle turns user LED2 on or off depending on the current state.
 * */
void led_toggle()	{
	if(led_on())	{
		led_g_off();
	} else	{
		led_g_on();
	}
}

/* led puts user LED3/4 in a given state.
 * User LED3/4 are controlled by pin PC9.
 *
 * Both are off when PC9 is in input mode.
 * LED3 is on, 4 is off when PC9 is in output mode, high state.
 * LED4 is on, 3 is off when PC9 is in output mode, low state. */
void led(int state)	{
	if(state == LED_OFF)	{
		GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODER9;
	} else	{
		GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODER9_0;
		if(state == LED_YELLOW)	{
			SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS9);
		} else	{
			SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR9);
		}
	}
}
