#include "led.h"

#define WAITING_TIME 1000000

int main(void)	{
	led_init();

	while(1)	{
		led_g_on();

		for(int i = 0; i < WAITING_TIME; ++i)
			asm volatile("nop");

		led_g_off();

		for(int i = 0; i < WAITING_TIME; ++i)
			asm volatile("nop");
	}
}
