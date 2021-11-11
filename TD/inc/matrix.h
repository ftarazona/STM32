/* matrix.h -- LED Matrix driver
 *******************************
 * This header declares proper functions for initializing and using
 * the Arduino RGB LED Matrix Shield.
 *
 * The shield embeds a driver chip, DMF163 which is in charge of
 * generating PWM signals according to the data given.
 *
 * The driver uses TIM3 for setting the framerate independently from
 * other general purpose timers. As a consequence, TIM3 SHALL NOT BE
 * USED WHILE THE MATRIX IS USED.
 * */

#ifndef MATRIX_H
#define MATRIX_H

#include <stm32l4xx.h>
#include <stm32l475xx.h>

#include "memfuncs.h"

/* The matrix uses a timer for display */
#include "timer.h"

#define LED_MATRIX_N_ROWS 8
#define LED_MATRIX_N_COLS 8
#define LED_MATRIX_N_LEDS LED_MATRIX_N_ROWS * LED_MATRIX_N_COLS

#define LED_MATRIX_RED 		0
#define LED_MATRIX_GREEN 	1
#define LED_MATRIX_BLUE 	2

#define LED_MATRIX_INIT_DELAY	1000

//Some useful macros for setting or resetting the pins
#define SB(x)	if(x) {SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS5);} else {SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR5);}
#define LAT(x)	if(x) {SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS4);} else {SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR4);}
#define RST(x)	if(x) {SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS3);} else {SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR3);}
#define SCK(x)	if(x) {SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS1);} else {SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR1);}
#define SDA(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS4);} else {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR4);}
#define ROW0(x)	if(x) {SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS2);} else {SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR2);}
#define ROW1(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS15);} else {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR15);}
#define ROW2(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS2);} else {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR2);}
#define ROW3(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS7);} else {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR7);}
#define ROW4(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS6);} else {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR6);}
#define ROW5(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS5);} else {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);}
#define ROW6(x)	if(x) {SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0);} else {SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0);}
#define ROW7(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS3);} else {SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR3);}

#define pulse_SCK() SCK(1); SCK(0)
#define pulse_LAT() LAT(0); LAT(1)

/* rgb_color describes the state of 3-color led */
typedef struct	{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_color;

/* Initializes the matrix with a given frame rate.
 * The frame rate corresponds to the time in us between two complete
 * display. 
 *
 * To avoid flickering, at least 60 fps is recommended. */
void led_matrix_init(int frame_rate);

/* Initializes BANK0. */
void led_matrix_init_bank0(void);


/* Deactivates every row. */
void led_matrix_deactivate_rows(void);

/* Activates a given row. */
void led_matrix_activate_row(int row);

/* Sends 8 bits to the matrix.
 * byte is the byte to be sent.
 * bank is the bank to send to. */
void led_matrix_send_byte(uint8_t byte, int bank);

/* Sets a row to given RGB values. */
void led_matrix_set_row(int row, const rgb_color * val);



/* Loads the image updated up to now. */
void image_load(void);

/* Updates information about next image to display.
 *  i is the position and color of the LED :
 *   i / 3 is the position
 *   i % 3 is the color
 *  val is the value of intensity wanted. */
void image_update(int i, uint8_t val);

/* Resets the image */
void image_reset(void);

#endif
