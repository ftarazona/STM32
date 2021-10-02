#ifndef LED_H
#define LED_H

#define RCC_AHB2ENR	(*(volatile uint32_t *)0x4002104c)
#define GPIOB_MODER	(*(volatile uint32_t *)0x48000400)
#define GPIOB_BSRR	(*(volatile uint32_t *)0x48000418)

#define RCC_GPIOBEN				0b1 << 1
#define GPIO_MODER14_OUTPUT 	0b01 << 28
#define GPIO_BSRR14_RESET		0b1 << 30
#define GPIO_BSRR14_SET			0b1 << 14

void led_init();

#endif
