#include "accelerometer.h"
#include "button.h"
#include "clocks.h"
#include "i2c.h"
#include "irq.h"
#include "matrix.h"
#include "random.h"
#include "timer.h"
#include "uart.h"

#define BAUDRATE 115200
#define FRAMES_PER_SECOND 90
#define TIMER_PERIOD_US 400000

#define DIRECTION_NONE 0
#define DIRECTION_UP 1
#define DIRECTION_BOTTOM 2
#define DIRECTION_RIGHT 3
#define DIRECTION_LEFT 4

static int snake[LED_MATRIX_N_LEDS] = {0};
static int snake_head = 0;
static int fruit = 0;

int update_direction()	{
	/* The accelerometer measures mostly the weight force.
	 * When horizontal, this force is only on axis Z.
	 * When the card is bent, projections appear axis X and Y.
	 * We determine the most bent direction and return it. */
	int16_t x = 0;
	int16_t y = 0;
	int16_t z = 0;
	accelerometer_get(&x, &y, &z);
	int16_t xAbs = x > 0 ? x : -x;
	int16_t yAbs = y > 0 ? y : -y;
	if(xAbs > yAbs)	{
		return x < 0 ? DIRECTION_UP : DIRECTION_BOTTOM;
	} else	{
		return y < 0 ? DIRECTION_LEFT : DIRECTION_RIGHT;
	}
}

void generate_new_fruit()	{
	/* A new position for the fruit is determined.
	 * In order to avoid generating multiple positions in case of
	 * conflicts, we remember which cases are free, there are
	 * LED_MATRIX_N_LEDS - 1 - snake_head */
	int busy[LED_MATRIX_N_LEDS] = {0};
	for(int i = 0; i <= snake_head; ++i)
		busy[snake[i]] = 1;

	int shift = random_get() & (LED_MATRIX_N_LEDS - 1 - snake_head);
	int i = 0;
	while(shift > 0 || busy[i])	{
		if(!busy[i])	{
			shift--;
		}
		i++;
	}
	fruit = i;
}

int refresh_snake(int direction)	{
	//Calculating the next position of the snake's head.
	int next_head = snake[snake_head];
	int overflow = 0;
	switch(direction)	{
		case DIRECTION_UP : 
			next_head += LED_MATRIX_N_COLS;
			if(next_head > LED_MATRIX_N_LEDS)
				overflow = 1;
			break;
		case DIRECTION_BOTTOM :
			next_head -= LED_MATRIX_N_COLS;
			if(next_head < 0)
				overflow = 1;
			break;
		case DIRECTION_RIGHT :
			next_head++;
			if(next_head % LED_MATRIX_N_COLS == 0)
				overflow = 1;
			break;
		case DIRECTION_LEFT :
			if(next_head % LED_MATRIX_N_COLS == 0)
				overflow = 1;
			next_head--;
			break;
		default : break;
	}

	//Gameover condition
	if(overflow)	{ return -1; }
	for(int i = 1; i <= snake_head; ++i)	{
		if(snake[i] == next_head)
			return -1;
	}
	
	//New fruit required
	if(next_head == fruit)	{
		snake[++snake_head] = next_head;
		//Complete condition
		if(snake_head == 63)	{ return 1; }
		generate_new_fruit();
	} else	{
		for(int i = 0; i < snake_head; ++i)
			snake[i] = snake[i + 1];
		snake[snake_head] = next_head;
	}
	
	return 0;
}

void display_snake(void)	{
	/* The snake is displayed in green, its head in blue.
	 * The fruit is displayed in yellow. */
	image_reset();
	for(int i = 0; i < snake_head; ++i)	{
		image_update(3 * snake[i] + LED_MATRIX_GREEN, 0xff);
	}
	image_update(3 * snake[snake_head] + LED_MATRIX_BLUE, 0xff);
	image_update(3 * fruit + LED_MATRIX_GREEN, 0xff);
	image_update(3 * fruit + LED_MATRIX_RED, 0xff);
	image_load();
}

void fill_matrix(int color)	{
	int r = (color & 0xff0000) >> 16;
	int g = (color & 0x00ff00) >> 8;
	int b = color & 0x0000ff;
	image_reset();
	for(int i = 0; i < LED_MATRIX_N_LEDS; ++i)	{
		image_update(3 * i, r);
		image_update(3 * i + 1, g);
		image_update(3 * i + 2, b);
	}
	image_load();
}

int main(void)	{
	/* Initializations. For the snake, we need 
	 *  button for user interaction (pause, restart)
	 *   irq required
	 *  led_matrix for display
	 *   irq required
	 *  accelerometer for direction input
	 *   i2c required
	 *  random for generating fruits
	 *  timer for generating refresh
	 * */
	clocks_init();
	irq_init();
	button_init();
	led_matrix_init(FRAMES_PER_SECOND, 0x88);
	i2c_master_init();
	accelerometer_init();
	random_init();
	timer_init(TIMER_PERIOD_US);

	/* Control variables. We need
	 *  reset for restarting game
	 *  gameover when the player looses
	 *  completed when the player wins
	 *  pause when the player has required a pause
	 *  */
	int reset 		= 1;
	int gameover 	= 0;
	int completed 	= 0;
	int pause 		= 0;

	while(1)	{
		if(button_triggered())	{
			if(gameover || completed)	{ reset = 1; }
			else						{ pause = !pause; }
		}
		if(timer_triggered() && !pause && !(gameover || completed))	{
			int direction = update_direction();
			int ret_refresh_snake = refresh_snake(direction);
			if(ret_refresh_snake < 0)		{ gameover = 1; }
			else if(ret_refresh_snake > 0)	{ completed = 1; }
			display_snake();
		}
		if(reset)	{
			//Reset of the snake
			snake_head = 0;
			snake[0] = 27;
			do	{
				fruit = random_get() & 63;
			} while(fruit == snake[0]);
			display_snake();

			//Reset of control variables
			pause 		= 0;
			completed 	= 0;
			gameover 	= 0;
			reset 		= 0;
		}
		if(gameover)	{
			fill_matrix(0xff0000);
		}
		if(completed)	{
			fill_matrix(0xffffff);
		}
	}
}
