#include "memfuncs.h"

#include "stm32l475xx.h"

#include "button.h"
#include "clocks.h"
#include "irq.h"
#include "led.h"
#include "matrix.h"
#include "uart.h"
#include "timer.h"

const char colors[8*192] =	"   
    =  b    Ä  ÿ     
  =. bL o Ä ÿÄ    
  = b  Ä ÿ     
  = b& 8 ÄL ÿb    
  = &b 8 LÄ bÿ    
  = b  Ä ÿ   
  = .b L oÄ ÿ Ä   
    =  b    Ä  ÿ  ";

void display_static_image(void);

int main(void)	{
	clocks_init();
//	uart_init();
//	irq_init();
//	button_init();
//	led_init();
//	timer_init(1000000);
	matrix_init();

	while(1)	{
		display_static_image();
	}
}

void display_static_image(void)	{
	
}
