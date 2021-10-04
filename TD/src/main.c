#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "stm32l475xx.h"

#define WAITING_TIME 1000000

int main(void)	{
	clocks_init();
	uart_init();

	int checksum = 0;

	while(1)	{
		for(int i = 0; i < 32; ++i)	{
			checksum += uart_getchar();
		}
		print_hex(checksum);
	}
}
