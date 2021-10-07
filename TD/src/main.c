#include "led.h"
#include "button.h"
#include "clocks.h"
#include "irq.h"
#include "uart.h"
#include "stm32l475xx.h"

#define N_BYTES 500

int main(void)	{
	clocks_init();
	uart_init();
	irq_init();
	button_init();
	led_init();

	led_g_on();
	int32_t checksum = 0;

	while(1)	{
		for(int i = 0; i < N_BYTES; ++i)	{
			checksum += uart_getchar();
		}
		print_hex(checksum);
		uart_putchar('\r');
		uart_putchar('\n');
	}

	while(1);
}
