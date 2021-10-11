#include "memfuncs.h"

#include "stm32l475xx.h"

#include "button.h"
#include "clocks.h"
#include "irq.h"
#include "led.h"
#include "matrix.h"
#include "uart.h"
#include "timer.h"

#define BAUD_RATE 2400
#define TIMER_SECOND 1000000

//const char hello[30] = "Hello world !";

int main(void)	{
	led_init();
	led_g_on();
	clocks_init();
	irq_init();
	uart_init(BAUD_RATE);
//	button_init();
	matrix_init();
	timer_init(TIMER_SECOND / 400);

	while(1)	{
		if(timer_triggered())	{
			display_image();
		}
	}
//	uart_puts(hello);
}
