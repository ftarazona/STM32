#ifndef UART_H
#define UART_H

#include <stddef.h>
#include <stdint.h>

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#define USART_CLOCK_FREQUENCY 80000000

/* Initializes the UART1 with a given baudrate. */
void uart_init(int baudrate);

/* transmits and receives a character to or from a connected machine
 * */
void uart_putchar(uint8_t c);
uint8_t uart_getchar();

/* transmits a null terminated string */
void uart_puts(const char * str);
/* receives a string of maximal size given. The reception stops
 * when '\n' or '\0' is read, or when maximum size is reached. */
void uart_gets(char * str, size_t size);

/* prints a 32-bit hexadecimal value. */
void print_hex(uint32_t n);

int uart_received(uint8_t * c);
void USART1_IRQHandler(void);

#endif
