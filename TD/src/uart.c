#include "uart.h"
#include "matrix.h"

/* uart_init initializes uart1 to establish a serial communication.
   TX is on PB6, RX is on PB7, both in alternate function 7 */
void uart_init(int baudrate)	{
	//TX/RX initializations
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	//Selection of alternate function AF7
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_Msk) | GPIO_MODER_MODER6_1;
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6_Msk) | (0x7UL << GPIO_AFRL_AFSEL6_Pos);
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_Msk) | GPIO_MODER_MODER7_1;
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7_Msk) | (0x7UL << GPIO_AFRL_AFSEL7_Pos);

	//Enable clock for USART1
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);

	//Select clock PCLK
	RCC->CCIPR &= ~RCC_CCIPR_USART1SEL_Msk;

	//Reset usart1
	SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
	CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);

	USART1->BRR = USART_CLOCK_FREQUENCY / baudrate;

	CLEAR_BIT(USART1->CR1, USART_CR1_OVER8);	//Oversampling to 16
	USART1->CR1 &= ~(USART_CR1_M1 | USART_CR1_M0); //8-bit words
	CLEAR_BIT(USART1->CR1, USART_CR1_PCE); //No parity control
	USART1->CR2 &= ~USART_CR2_STOP_Msk;	//1 stop bit
	SET_BIT(USART1->CR1, USART_CR1_UE);	//Enabling UART
	SET_BIT(USART1->CR1, USART_CR1_TE);	//Enabling transmissions
	SET_BIT(USART1->CR1, USART_CR1_RE);	//Enabling receptions

	//Enable interrupts for reception
	SET_BIT(USART1->CR1, USART_CR1_RXNEIE);
}

/* uart_putchar transmits a character. */
void uart_putchar(uint8_t c)	{
	while(!(USART1->ISR & USART_ISR_TXE));

	USART1->TDR = c;
}

/* uart_getchar waits until a character is received and catches it. */
uint8_t uart_getchar()	{
	while(!(USART1->ISR & USART_ISR_RXNE));

	return USART1->RDR;
}

/* uart_puts emits an entire string and jump line. */
void uart_puts(const char * str)	{
	while(*str != '\0')	{
		uart_putchar(*str++);
	}
	uart_putchar('\r');
	uart_putchar('\n');
}

/* uart_gets receives a string of a maximum size */
void uart_gets(char * str, size_t size)	{
	uint8_t c = 255;
	size_t i = 0;
	while(c != '\r' && c != '\n' && c != '\0' && i < size - 1)	{
		c = uart_getchar();
		*str++ = c;
		i++;
	}
	*str = '\0';
}

/* print_hex prints emits characters so that a number is eventually
   written */
void print_hex(uint32_t n)	{
	if(n == 0)	{
		return;
	}
	int q = n / 16;
	int r = n % 16;
	print_hex(q);
	if(r < 10)	{
		uart_putchar('0' + r);
	} else	{
		uart_putchar('A' + r - 10);
	}
}

/* The IRQ Handler reads a character and stores it in the right led
 * configuration. */
void USART1_IRQHandler(void)	{
	/* iByte remembers how many bytes are already read in the current
	 * frame. */
	static int iByte = 0;
	uint8_t c = uart_getchar();

	if(c != 0xff)	{	//The read byte is a led configuration info
		int iLed = iByte / 3;
		int iColor = iByte % 3;
		iByte++;
		if(iLed >= LED_MATRIX_N_LEDS)	{
			/* In this case the frame is too long. The byte is dropped
			 * in order to avoid a memory overflow. */
			return;
		}
		switch(iByte)	{
			case 0: led_values[iLed].r = c; break;
			case 1: led_values[iLed].g = c; break;
			case 2: led_values[iLed].b = c; break;
			default: break;
		}
	} else	{	//End of frame
		iByte++;
		if(iByte < 3 * LED_MATRIX_N_LEDS)	{
			/* In this case the frame is incomplete. The frame is
			 * completed by zeros */

		}
	}
}
