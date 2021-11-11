/* uart.h -- UART Driver
 * *********************
 * This header declares proper functions for using the UART1 embedded
 * on the STM32L475VG.
 *
 * It provides the most basic functions such as getting a character,
 * putting a character.
 *
 * The UART1 has an interruption mode that is disabled by default.
 * When enabled, each character received triggers an interruption.
 * When interrupted, the program stores the character in the buffer
 * of the LED Matrix and loads the image when receiving 0xff.
 * */

#ifndef UART_H
#define UART_H

#include <stddef.h>
#include <stdint.h>

#include "stm32l4xx.h"
#include "stm32l475xx.h"

#include "matrix.h"

#define USART_CLOCK_FREQUENCY 80000000

/* Initializes the UART1 with a given baudrate. */
void uart_init(int baudrate);

/* Enables the interruption mode. led_matrix_init shall be called
 * before calling uart_enable_interrupt_mode. */
void uart_enable_interrupt_mode(void);

/* Disables the interruption mode. */
void uart_disable_interrupt_mode(void);

/* transmits and receives a character to or from a connected machine
 * */
void uart_putchar(uint8_t c);
uint8_t uart_getchar(void);

/* transmits a null terminated string */
void uart_puts(const char * str);
/* receives a string of maximal size given. The reception stops
 * when '\n' or '\0' is read, or when maximum size is reached. */
void uart_gets(char * str, size_t size);

/* prints a 32-bit hexadecimal value. */
void uart_print_hex(uint32_t n);

/* The handler is directly linked to the LED Matrix driver. */
void USART1_IRQHandler(void);

#endif
