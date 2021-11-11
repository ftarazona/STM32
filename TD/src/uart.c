#include "uart.h"

void uart_init(int baudrate)	{
	/* uart_init initializes uart1 to establish a serial communication.
   	TX is on PB6, RX is on PB7, both in alternate function 7 */
	
	//TX/RX initializations
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	//Selection of alternate function AF7
	GPIOB->MODER = (GPIOB->MODER & 0xffff0fff) |
					GPIO_MODER_MODE6_1 | GPIO_MODER_MODE7_1;
	GPIOB->AFR[0] = (GPIOB->AFR[0] & 0x00ffffff) |
					(0x7UL << GPIO_AFRL_AFSEL6_Pos) |
					(0x7UL << GPIO_AFRL_AFSEL7_Pos);

	//Enable clock for USART1
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);

	//Select clock PCLK
	RCC->CCIPR &= ~RCC_CCIPR_USART1SEL_Msk;

	//Reset usart1
	SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
	CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);

	//Setting baudrate
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
	NVIC_DisableIRQ(USART1_IRQn);
}

void uart_enable_interrupt_mode(void)	{ NVIC_EnableIRQ(USART1_IRQn); }

void uart_disable_interrupt_mode(void)	{ NVIC_DisableIRQ(USART1_IRQn); }

void uart_putchar(uint8_t c)	{
	/* The bit USART_ISR_TXE is set by hardware when a character is
	 * ready to be sent. */
	while(!(USART1->ISR & USART_ISR_TXE));
	USART1->TDR = c;
}

uint8_t uart_getchar()	{
	/* The bit USART_ISR_RXNE is set by hardware when a character is
	 * ready to be read. */
	while(!(USART1->ISR & USART_ISR_RXNE));
	return USART1->RDR;
}

void uart_puts(const char * str)	{
	/* uart_puts emits an entire string and jump line. */
	while(*str != '\0')	{
		uart_putchar(*str++);
	}
	uart_putchar('\r');
	uart_putchar('\n');
}

void uart_gets(char * str, size_t size)	{
	/* uart_gets receives a string of a maximum size */
	uint8_t c = 255;
	size_t i = 0;
	while(c != '\r' && c != '\n' && c != '\0' && i < size - 1)	{
		c = uart_getchar();
		*str++ = c;
		i++;
	}
	*str = '\0';
}

void uart_print_hex(uint32_t n)	{
	int r[8] = {0};
	for(int i = 0; i < 8; ++i)	{
		r[i] = n % 16;
		n = n / 16;
	}
	for(int i = 0; i < 8; ++i)	{
		if(r[7 - i] < 10)	{
			uart_putchar('0' + r[7 - i]);
		} else	{
			uart_putchar('A' + r[7 - i] - 10);
		}
	}
	uart_puts("");
}

void USART1_IRQHandler(void)	{
	/* The IRQ Handler reads a character and stores it in the right 
	 * led configuration. */
	static int i_row = 0;
	static int i_col = 0;
	static int color = 0;

	if(USART1->ISR & USART_ISR_RXNE)	{
		uint8_t character = USART1->RDR;
		if(character != 0xff && i_row < LED_MATRIX_N_ROWS)	{
			image_update((i_row * LED_MATRIX_N_COLS + (LED_MATRIX_N_COLS - i_col - 1)) * 3  + color, character);
			//Incrementing 
			color++;
			if(color >= 3)	{ color = 0; i_col++; }
			if(i_col >= LED_MATRIX_N_COLS)	{ i_col = 0; i_row++; }
		} else	{
			//In our protocol, 0xff means a new frame starts
			image_load();
			//Reseting
			i_row = 0; i_col = 0; color = 0;
		}
	} else if(USART1->ISR & USART_ISR_ORE)	{
		/* If the code does not execute fast enough in comparison to
		 * the baud rate, it is possible that an overrun occurs. */
		SET_BIT(USART1->ICR, USART_ICR_ORECF);
		CLEAR_BIT(USART1->ICR, USART_ICR_ORECF);
	}
}
