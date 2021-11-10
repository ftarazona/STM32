#include "clocks.h"
#include "button.h"
#include "irq.h"
#include "matrix.h"
#include "timer.h"
#include "i2c.h"
#include "random.h"
#include "uart.h"
#include "accelerometer.h"

#define BAUDRATE 115200
#define TIMER_FREQUENCY 1000
#define N_SAMPLES 100

#define NONE 0
#define UP 1
#define BOTTOM 2
#define RIGHT 3
#define LEFT 4

static int snake[LED_MATRIX_N_LEDS] = {0};
static int snake_head = 0;
static int fruit = 0;
static int direction = NONE;

void update_direction()	{
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;
	accelerometer_get(&x, &y, &z);
	int16_t xAbs = x > 0 ? x : -x;
	int16_t yAbs = y > 0 ? y : -y;
	if(xAbs > yAbs)	{
		direction = x < 0 ? UP : BOTTOM;
	} else	{
		direction = y < 0 ? LEFT : RIGHT;
	}
}

int next(int x)	{
	x++;
	if(x >= LED_MATRIX_N_LEDS)	{ x = 0; }
	return x;
}

void generateNewFruit()	{
	fruit = random_get() & 63;
	int stop = 0;
	while(!stop)	{
		stop = 1;
		for(int i = 0; i <= snake_head; ++i)	{
			if(fruit == snake[i])	{
				fruit++;
				fruit %= 63;
				stop = 0;
			}
		}
	}
}

int refresh()	{
	int next_head = snake[snake_head];
	int overflow = 0;

	switch(direction)	{
		case UP : 
			next_head += LED_MATRIX_N_COLS;
			if(next_head > LED_MATRIX_N_LEDS)
				overflow = 1;
			break;
		case BOTTOM :
			next_head -= LED_MATRIX_N_COLS;
			if(next_head < 0)
				overflow = 1;
			break;
		case RIGHT :
			next_head++;
			if(next_head % LED_MATRIX_N_COLS == 0)
				overflow = 1;
			break;
		case LEFT :
			if(next_head % LED_MATRIX_N_COLS == 0)
				overflow = 1;
			next_head--;
			break;
		default : break;
	}

	if(overflow)	{ return 1; }
	for(int i = 1; i <= snake_head; ++i)	{
		if(snake[i] == next_head)
			return 2;
	}
	if(snake_head == 63)	{
		return 3;
	}
	if(next_head == fruit)	{
		snake[++snake_head] = next_head;
		generateNewFruit();
	} else	{
		for(int i = 0; i < snake_head; ++i)	{
			snake[i] = snake[i + 1];
		}
		snake[snake_head] = next_head;
	}
	
	set_image();
	for(int i = 0; i < snake_head; ++i)	{
		update_image(3 * snake[i] + GREEN, 0xff);
	}
	update_image(3 * snake[snake_head] + BLUE, 0xff);
	update_image(3 * fruit + GREEN, 0xff);
	update_image(3 * fruit + RED, 0xff);
	load_image();

	return 0;
}

int main(void)	{
	clocks_init();
	button_init();
	uart_init(BAUDRATE);
	irq_init();
	matrix_init();
	random_init();
	accelerometer_init();
	timer_init(TIMER_FREQUENCY, 1, 250, 500);

	int reset = 1;
	int gameover = 0;
	while(1)	{
		if(reset)	{
			snake[0] = 27;
			for(int i = 1; i < LED_MATRIX_N_LEDS; ++i)	{
				snake[i] = 0;
				snake_head = 0;
				fruit = random_get() & 63;
				if(fruit == 27)	{ fruit = 45; }
				reset = 0;
				gameover = 0;
			}
		}
		if(timer_triggered_display())	{
			display_image();
		}
		if(timer_triggered_accelerometer() && !gameover)	{
			update_direction();
		}
		if(timer_triggered_refresh() && !gameover)	{
			int ret = refresh();
			if(ret == 3)	{
				gameover = 1;
				set_image();
				for(int i = 0; i < LED_MATRIX_N_LEDS * 3; ++i)
					update_image(i, 0xff);
				load_image();
			}
			else if(ret > 0)	{
				gameover = 1;
				set_image();
				for(int i = 0; i < LED_MATRIX_N_LEDS; ++i)
					update_image(3 * i, 0xaa);
				load_image();
			}
		}
		if(gameover && button_triggered())	{
			reset = 1;
		}
	}
}
