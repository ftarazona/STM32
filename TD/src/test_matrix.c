#include "accelerometer.h"
#include "button.h"
#include "clocks.h"
#include "i2c.h"
#include "irq.h"
#include "matrix.h"
#include "random.h"
#include "timer.h"
#include "uart.h"

#define BAUDRATE 38400
#define FRAMES_PER_SECOND 90

int main(void)	{
	/* Initializations. For the uart-controlled matrix, we need 
	 *  led_matrix for display
	 *   irq required
	 * */
	clocks_init();
	irq_init();
	led_matrix_init(FRAMES_PER_SECOND, 0xff);

	for(int i = 0; i < LED_MATRIX_N_LEDS * 3; ++i)	{
		image_update(i, 0xff);
	}
	image_load();
	while(1);
}
