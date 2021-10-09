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

void test_pixels(void);

int main(void)	{
	clocks_init();
//	uart_init();
//	irq_init();
//	button_init();
//	led_init();
//	timer_init(1000000);
	matrix_init();

	test_pixels();
	while(1);
}

void test_pixels(void)	{
	rgb_color leds[8];
	int color = 0;
	int row = 0;
	while(1)	{
		for(int i = 0; i < 8; ++i)	{
			leds[i].r = color == RED ? i * 30 : 0;
			leds[i].g = color == GREEN ? i * 30 : 0;
			leds[i].b = color == BLUE ? i * 30 : 0;
		}
		for(int i = 0; i < 1000; ++i)	{
			for(int j = 0; j < 8; ++j)	{
				mat_set_row(j, leds);
				deactivate_rows();
			}
		}
		color = (color + 1) % 3;
		mat_set_row(row, leds);
	}
}
