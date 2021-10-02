#include "led.h"

int main(void)	{
	led_init();

	while(1)	{
		led_g_on();

		for(int i = 0; i < 10000; ++i)
			asm volatile("nop");

		led_g_off();

		for(int i = 0; i < 10000; ++i)
			asm volatile("nop");
	}
}
