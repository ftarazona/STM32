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
#define TIMER_PERIOD 1000000

int main(void)	{
	clocks_init();
	uart_init(BAUD_RATE);
	irq_init();
//	button_init();
//	led_init();
	timer_init(TIMER_PERIOD);
	matrix_init();

	uint8_t c;
	int ret_uart_received = 0;

	while(1)	{
		ret_uart_received = uart_received(&c);
		if(ret_uart_received > 0)	{
			if(c != 0xff)	{
				update_image(c);
			}
		} else if(ret_uart_received < 0)	{
			c = 0x00;
			do	{
				ret_uart_received = uart_received(&c);
			} while(ret_uart_received < 0 || c != 0xff);
		}
	}
}
