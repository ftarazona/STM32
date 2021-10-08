#include "memfuncs.h"

#include "stm32l475xx.h"

#include "button.h"
#include "clocks.h"
#include "irq.h"
#include "led.h"
#include "uart.h"
#include "timer.h"

#define N_BYTES 50
#define START 0x20010000

int main(void)	{
/*	clocks_init();
	uart_init();
	irq_init();
	button_init();
	led_init();
	timer_init(1000000);

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
*/

	memset((int*)0x20010000, 7, N_BYTES);
	memcpy((int*)0x20010500, (int*)0x20010000, N_BYTES);
	memset((int*)0x20010100, 0, N_BYTES);
	memmove((int*)0x20020000, (int*)0x20020200, N_BYTES);
	memset((int*)0x20010000, 0, N_BYTES);
	memset((int*)0x20020000, 1, N_BYTES);
	int cmp = memcmp((int*)0x20010000, (int*)0x20020000, N_BYTES);
	cmp *= 2;

	while(1);
}
