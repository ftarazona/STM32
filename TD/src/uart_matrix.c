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
	 *  uart for receiving characters
	 *   irq required
	 *  led_matrix for display
	 *   irq required
	 * */
	clocks_init();
	irq_init();
	uart_init(BAUDRATE);
	led_matrix_init(FRAMES_PER_SECOND, 10);

	/* The UART driver works by default with the led matrix when
	 * enabling the interrupt mode. */
	uart_enable_interrupt_mode();
	while(1);
}
