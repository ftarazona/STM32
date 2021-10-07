#ifndef LED_H
#define LED_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

enum	{
	LED_OFF,
	LED_YELLOW,
	LED_BLUE
};

void led_init();
void led_g_on();
void led_g_off();
int led_state();
void led(int state);

#endif
