#ifndef MATRIX_H
#define MATRIX_H

#include <stm32l4xx.h>
#include <stm32l475xx.h>

#include "timer.h"

#define N_TICKS_DELAY 80000000

#define SB(x)	if(x) {SET_BIT(GPIOC->BSRR, GPIOC_BSRR_BS5);} else {SET_BIT(GPIOC->BSRR, GPIOC_BSRR_BR5);}
#define LAT(x)	if(x) {SET_BIT(GPIOC->BSRR, GPIOC_BSRR_BS4);} else {SET_BIT(GPIOC->BSRR, GPIOC_BSRR_BR4);}
#define RST(x)	if(x) {SET_BIT(GPIOC->BSRR, GPIOC_BSRR_BS3);} else {SET_BIT(GPIOC->BSRR, GPIOC_BSRR_BR3);}
#define SCK(x)	if(x) {SET_BIT(GPIOB->BSRR, GPIOB_BSRR_BS1);} else {SET_BIT(GPIOB->BSRR, GPIOB_BSRR_BR1);}
#define SDA(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BS4);} else {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BR4);}
#define ROW0(x)	if(x) {SET_BIT(GPIOB->BSRR, GPIOB_BSRR_BS2);} else {SET_BIT(GPIOB->BSRR, GPIOB_BSRR_BR2);}
#define ROW1(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BS15);} else {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BR15);}
#define ROW2(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BS2);} else {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BR2);}
#define ROW3(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BS7);} else {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BR7);}
#define ROW4(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BS6);} else {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BR6);}
#define ROW5(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BS5);} else {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BR5);}
#define ROW6(x)	if(x) {SET_BIT(GPIOB->BSRR, GPIOB_BSRR_BS0);} else {SET_BIT(GPIOB->BSRR, GPIOB_BSRR_BR0);}
#define ROW7(x)	if(x) {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BS3);} else {SET_BIT(GPIOA->BSRR, GPIOA_BSRR_BR3);}

#define pulse_SCK SCK(1); asm volatile("nop"); SCK(0); asm volatile("nop");
#define pulse_LAT LAT(0); asm volatile("nop"); LAT(1); asm volatile("nop");

typedef struct	{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} rgb_color;

void matrix_init(void);
void deactivate_rows(void);
void activate_row(int row);
void send_byte(uint8_t val, int bank);
void mat_set_row(int row, const rgb_color * val);
void init_bank0();

#endif
