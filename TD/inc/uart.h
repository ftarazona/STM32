#ifndef UART_H
#define UART_H

#include <stdint.h>

#include "stm32l4xx.h"
#include "stm32l475xx.h"

void uart_init();
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char * str);

#endif
