#include "uart.h"

/* uart_init initializes uart1 to establish a serial communication.
   TX is on PB6, RX is on PB7, both in alternate function 7 */
void uart_init()	{
	//TX/RX initializations
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_Msk) | GPIO_MODER_MODER6_1;
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL6_Msk) | (0x7UL << GPIO_AFRL_AFSEL6_Pos);
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_Msk) | GPIO_MODER_MODER7_1;
	GPIOB->AFR[0] = (GPIOB->AFR[0] & ~GPIO_AFRL_AFSEL7_Msk) | (0x7UL << GPIO_AFRL_AFSEL7_Pos);

	//Enable clock for I/O in port B
	SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);

	//Select clock PCLK
	RCC->CCIPR &= ~RCC_CCIPR_USART1SEL_Msk;

	//Reset usart1
	SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
	CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);

	USART1->BRR = 694;

	CLEAR_BIT(USART1->CR1, USART_CR1_OVER8);	//Oversampling to 16
	USART1->CR1 &= ~(USART_CR1_M1 | USART_CR1_M0); //8-bit words
	CLEAR_BIT(USART1->CR1, USART_CR1_PCE); //No parity control
	USART1->CR2 &= ~USART_CR2_STOP_Msk;
	SET_BIT(USART1->CR1, USART_CR1_UE);
	SET_BIT(USART1->CR1, USART_CR1_TE);
	SET_BIT(USART1->CR1, USART_CR1_RE);
}

void uart_putchar(uint8_t c)	{
	while(!(USART1->ISR & USART_ISR_TXE));

	USART1->TDR = c;
}

uint8_t uart_getchar()	{
	while(!(USART1->ISR & USART_ISR_RXNE));

	return USART1->RDR;
}
