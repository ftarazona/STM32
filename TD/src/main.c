#include "memfuncs.h"

#include "stm32l475xx.h"

#include "button.h"
#include "clocks.h"
#include "irq.h"
#include "led.h"
#include "matrix.h"
#include "uart.h"
#include "timer.h"
#include "i2c.h"

#define BAUD_RATE 115200
#define TIMER_SECOND 1000000

#define RADDR 0xD5
#define WADDR 0xD4

//const char hello[30] = "Hello world !";

int main(void)	{
	led_init();
	led_g_on();
	clocks_init();
	irq_init();
	uart_init(BAUD_RATE);
//	button_init();
	matrix_init();
	i2c_master_init();
	timer_init(TIMER_SECOND / 1);

	uart_puts("UART Initialized");
	uint8_t accel_init[3] = {WADDR, 0x11, 0x60};
	i2c_send(accel_init, 3);
	uint8_t accel_int[3] = {WADDR, 0x0d, 0x02};
	i2c_send(accel_int, 3);


	uint8_t ready = 0;
	uint8_t data;
	while(1)	{
		if(timer_triggered())	{
			i2c_read(RADDR, 0x1e, &ready, 1);
			uart_puts("Reading...");
			if(ready & 0x01)	{
				uart_puts("Data available");
				i2c_read(RADDR, 0x23, &data, 1);
				print_hex(data);
			}
		}
	}
}
