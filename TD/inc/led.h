/* led.h -- LED driver
 *********************
 * This header declares proper functions for initializing and using
 * some of the built-in LEDs available on the STM32L475VG.
 *
 * It is possible to control LED2, LED3 and LED4.
 * */

#ifndef LED_H
#define LED_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

/* LED3/4 possible states */
enum	{
	LED_OFF,
	LED_YELLOW,
	LED_BLUE
};

/* Led initialization. MUST BE CALLED BEFORE ANY LED MANIPULATION */
void led_init();

/* Turns LED2 on */
void led_g_on();

/* Turns LED2 off */
void led_g_off();

/* Returns the state of LED2 */
int led_on();

/* Toggles LED2 */
void led_toggle();

/* Sets LED3/4 in state passed as parameter */
void led(int state);

#endif
