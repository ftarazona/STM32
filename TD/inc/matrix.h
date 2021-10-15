#ifndef MATRIX_H
#define MATRIX_H

#include <stm32l4xx.h>
#include <stm32l475xx.h>

#include "timer.h"

#define LED_MATRIX_N_ROWS 8
#define LED_MATRIX_N_COLS 8
#define LED_MATRIX_N_LEDS LED_MATRIX_N_ROWS * LED_MATRIX_N_COLS

#define RED 0
#define GREEN 1
#define BLUE 2

#define N_TICKS_DELAY 100000

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

#define pulse_SCK SCK(1); SCK(0);
#define pulse_LAT asm volatile ("nop"); LAT(0); LAT(1);

/* rgb_color describes the state of 3-color led */
typedef struct	{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_color;

/* Initialization. MUST BE CALLED BEFORE ANY LED MATRIX MANIPULATION
 * */
void matrix_init(void);

/* Deactivates every row */
void deactivate_rows(void);
/* Activates a given row */
void activate_row(int row);

/* Sends 8 bit to the matrix. THIS FUNCTION MAY NOT BE CALLED BY 
 * USER */
void send_byte(uint8_t val, int bank);
/* Sets BANK0. THIS FUNCITON MAY NOT BE CALLED BY USER. */
void init_bank0(void);

/* sets a row to given values */
void mat_set_row(int row, const rgb_color * val);
/* displays image described by led_values array */
void display_image(void);

/* Loads the next image. */
void load_image(void);
/* Updates information about next image to display.
 *  val is the value to write. The writing follows this order :
 *  led0 r, led0 g, led0 b, led1 r, ... */
int update_image(uint8_t val);
/* Fills the remaining leds of the current image to 0 */
void set_image(void);

#endif
