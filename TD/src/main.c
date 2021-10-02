#include "led.h"
#include "clocks.h"
#include "stm32l475xx.h"

#define WAITING_TIME 1000000

int main(void)	{
	clocks_init();
	led_init();
	
	while(1)	{
		led(LED_OFF);
		led_g_on();

		for(int i = 0; i < WAITING_TIME; ++i)
			asm volatile("nop");

		led_g_off();
		led(LED_YELLOW);

		for(int i = 0; i < WAITING_TIME; ++i)
			asm volatile("nop");

		led(LED_BLUE);

		for(int i = 0; i < WAITING_TIME; ++i)
			asm volatile("nop");
	}
}
