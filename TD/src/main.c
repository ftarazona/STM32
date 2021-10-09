#include "memfuncs.h"

#include "stm32l475xx.h"

#include "button.h"
#include "clocks.h"
#include "irq.h"
#include "led.h"
#include "matrix.h"
#include "uart.h"
#include "timer.h"


void display_static_image(const rgb_color * leds);

int main(void)	{
	clocks_init();
	uart_init(38400);
	irq_init();
	button_init();
	led_init();
	timer_init(1000000);
	matrix_init();

	while(1);
}

void display_static_image(const rgb_color * leds)	{
	for(int i = 0; i < 8; ++i)	{
		mat_set_row(i, leds + i * 8);
		deactivate_rows();
	}
}
