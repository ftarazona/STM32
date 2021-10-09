#include "memfuncs.h"

#include "stm32l475xx.h"

#include "button.h"
#include "clocks.h"
#include "irq.h"
#include "led.h"
#include "matrix.h"
#include "uart.h"
#include "timer.h"

#define RED 0
#define GREEN 1
#define BLUE 2

#define N_BYTES 50

int main(void)	{
	clocks_init();
//	uart_init();
//	irq_init();
//	button_init();
//	led_init();
//	timer_init(1000000);
	matrix_init();

	/*
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
	
	rgb_color leds[8];
	int row = 0;
		for(int i = 0; i < 8; ++i)	{
			leds[i].r = 255;
			leds[i].g = 0;
			leds[i].b = 0;
		}
	while(1)	{
/*	
		for(int i = 0; i < 1000000; ++i)	{
			for(int j = 0; j < 8; ++j)	{
				mat_set_row(j, leds);
				deactivate_rows();
			}
		}
		color = (color + 1) % 3;*/
		mat_set_row(row, leds);
//		deactivate_rows();
//		row = (row + 1) % 8;
	}
}
