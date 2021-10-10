#include "memfuncs.h"

#include "stm32l475xx.h"

#include "button.h"
#include "clocks.h"
#include "irq.h"
#include "led.h"
#include "matrix.h"
#include "uart.h"
#include "timer.h"

#define BAUD_RATE 38400
#define TIMER_SECOND 1000000

int main(void)	{
	clocks_init();
	irq_init();
	uart_init(BAUD_RATE);
//	button_init();
//	led_init();
	matrix_init();
	timer_init(TIMER_SECOND / 1000);

	while(1)	{
		if(timer_triggered())	{
			display_image();
		}
	}
}
