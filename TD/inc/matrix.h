#ifndef MATRIX_H
#define MATRIX_H

/* Pin functions :
 *  SB	~ PC5
 *  LAT	~ PC4
 *  RST	~ PC3
 *  SCK	~ PB1
 *  SDA	~ PA4
 *  C0	~ PB2
 *  C1	~ PA15
 *  C2	~ PA2
 *  C3	~ PA7
 *  C4	~ PA6
 *  C5	~ PA5
 *  C6	~ PB0
 *  C7	~ PA3 */
#include <stm32l4xx.h>
#include <stm32l475xx.h>

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
void matrix_init(void);

#endif
