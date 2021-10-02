#include "uart.h"

/* uart_init initializes uart1 to establish a serial communication.
   TX is on PB6, RX is on PB7, both in alternate function 7 */
void uart_init()	{
	//TX/RX initializations
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	GPIOB->MODER = (GPIOB->MODER & GPIO_MODER_MODER6_Msk) | GPIO_MODER_MODER6_1;
	GPIOB->AFRL = (GPIOB->AFRL & GPIO_AFRL_AFSEL6_Msk) | (0x7UL << GPIO_AFRL_AFSEL6_Pos);
	GPIOB->MODER = (GPIOB->MODER & GPIO_MODER_MODER7_Msk) | GPIO_MODER_MODER7_1;
	GPIOB->AFRL = (GPIOB->AFRL & GPIO_AFRL_AFSEL7_Msk) | (0x7UL << GPIO_AFRL_AFSEL7_Pos);

	//Enable clock for I/O in port B
	SET_BIT(RCC->AHB2SMENR, RCC_AHB2SMENR_GPIOBSMEN);

	//Select clock PCLK
	RCC->CCIPR &= RCC_CCIPR_USART1_Msk;

	//Reset usart1
	SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);

	USART->BRR = 115200;

	CLEAR_BIT(USART->CR1, USART_CR1_OVER8);	//Oversampling to 16
	USART->CR1 &= ~(USART_CR1_M1 | USART_CR1_M0); //8-bit words
	CLEAR_BIT(USART->CR1, USART_CR1_PCE); //No parity control
	SET_BIT(USART->CR1, USART_CR1_UE);
	SET_BIT(USART->CR1, USART_CR1_TE);
	SET_BIT(USART->CR1, USART_CR1_RE);
}
