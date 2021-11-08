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

int snake[LED_MATRIX_N_LEDS];

int main(void)	{
	led_init();
	led_g_on();
	clocks_init();
	irq_init();
	uart_init(BAUD_RATE);
	button_init();
	matrix_init();
	i2c_master_init();
	timer_init(TIMER_SECOND / 100);

	uart_puts("UART Initialized");
	uint8_t accel_init[3] = {WADDR, 0x11, 0x60};
	i2c_send(accel_init, 3);
	uint8_t accel_int[3] = {WADDR, 0x0d, 0x02};
	i2c_send(accel_int, 3);
	uart_puts("Accelerometer initialized");

	uint8_t ready = 0;
	uint8_t xl;
	uint8_t xh;
	uint8_t yl;
	uint8_t yh;
	uint8_t zl;
	uint8_t zh;
	uint16_t x;
	uint16_t y;
	uint16_t z;
	while(1)	{
		if(timer_triggered())	{
			i2c_read(RADDR, 0x1e, &ready, 1);
			if(ready & 0x02)	{
				i2c_read(RADDR, 0x22, &xl, 1);
				i2c_read(RADDR, 0x23, &xh, 1);
				i2c_read(RADDR, 0x24, &yl, 1);
				i2c_read(RADDR, 0x25, &yh, 1);
				i2c_read(RADDR, 0x26, &zl, 1);
				i2c_read(RADDR, 0x27, &zh, 1);
				x = (xh << 8) + xl;
				y = (yh << 8) + yl;
				z = (zh << 8) + zl;
			}
		}
	}
}
