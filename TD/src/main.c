#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "stm32l475xx.h"

#define WAITING_TIME 1000000

int main(void)	{
	clocks_init();
	uart_init();

	char str[20];

	while(1)	{
		uart_gets(str, 20);
		uart_puts(str);
	}
}
