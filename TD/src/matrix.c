#include <stddef.h>
#include "matrix.h"

static rgb_color buffer1[LED_MATRIX_N_LEDS];
static rgb_color buffer2[LED_MATRIX_N_LEDS];
static rgb_color * currentBuffer = buffer1;
static rgb_color * currentImage = buffer2;

void TIM3_IRQHandler(void)	{
	static int i_row = LED_MATRIX_N_ROWS;
	CLEAR_BIT(TIM3->SR, TIM_SR_UIF);
	--i_row;
	led_matrix_set_row(i_row, currentImage + (LED_MATRIX_N_COLS * (i_row)));
	if(i_row == 0)	{ i_row = LED_MATRIX_N_ROWS; }
}

void led_matrix_init(int framerate)	{
	//Enabling peripherals' clocks
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN |
					RCC_AHB2ENR_GPIOBEN |
					RCC_AHB2ENR_GPIOCEN;

	//Configuring pins in output mode
	GPIOA->MODER = (GPIOA->MODER & 0x3ffc000f) |
					GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 |
					GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 |
					GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 |
					GPIO_MODER_MODE15_0;
	GPIOB->MODER = (GPIOB->MODER & 0xffffffc0) |
					GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 |
					GPIO_MODER_MODE2_0;
	GPIOC->MODER = (GPIOC->MODER & 0xfffff03f) |
					GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 |
					GPIO_MODER_MODE5_0;

	//Configuring pins in high speed mode
	GPIOA->OSPEEDR |= 	(3 << GPIO_OSPEEDR_OSPEED2_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED3_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED4_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED5_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED6_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED7_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED15_Pos);
	GPIOB->OSPEEDR |= 	(3 << GPIO_OSPEEDR_OSPEED0_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED1_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED2_Pos);
	GPIOC->OSPEEDR |= 	(3 << GPIO_OSPEEDR_OSPEED3_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED4_Pos) |
						(3 << GPIO_OSPEEDR_OSPEED5_Pos);

	//Reseting the led matrix.
	RST(0); LAT(1); SB(1); SCK(0); SDA(0);
	led_matrix_deactivate_rows();

	active_wait(LED_MATRIX_INIT_DELAY);	//Waits about 100ms
	RST(1);
	led_matrix_init_bank0();	//Sets every bit in bank0 to 1.

	//Setting the timer for display
	//Enabling clock for peripheral
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_TIM3EN);
	
	//Reseting the timer
	TIM3->CNT = 0;
	TIM3->PSC = 80;
	//The interrupt will display a new line.
	TIM3->ARR = 1000000 / (framerate * LED_MATRIX_N_ROWS);
	SET_BIT(TIM3->DIER, TIM_DIER_UIE);
	SET_BIT(TIM3->CR1, TIM_CR1_CEN);
	NVIC_DisableIRQ(TIM3_IRQn);
}

void led_matrix_deactivate_rows(void)	{
	/* led_matrix_deactivate_rows is equivalent to ROW0(0); ...; ROW7(0); */
	GPIOA->BSRR |= 0x80ec << 16;
	GPIOB->BSRR |= 0x0005 << 16;
}

void led_matrix_activate_row(int row)	{
	switch(row)	{
		case 0: ROW0(1); break;
		case 1: ROW1(1); break;
		case 2: ROW2(1); break;
		case 3: ROW3(1); break;
		case 4: ROW4(1); break;
		case 5: ROW5(1); break;
		case 6: ROW6(1); break;
		case 7: ROW7(1); break;
		default: break;
	}
}

void led_matrix_send_byte(uint8_t byte, int bank)	{
	SB(bank);	//Select the bank
	for(int i = 0; i < 8; ++i)	{
		SDA(byte & (1 << (7 - i))); //Byte is sent MSB first
		pulse_SCK();
	}
}

void led_matrix_set_row(int row, const rgb_color * val)	{
	/* We must think about when we call led_matrix_deactivate_rows.
	 * If called too soon, the row will be less luminous.
	 * If called too late, the last row will still light a little as
	 *  the pins are slower than the clock.
	 * As a result we place the call at the 6th iteration. */
	for(int i = 0; i < 8; ++i)	{
		if(i == 7)
			led_matrix_deactivate_rows();
		led_matrix_send_byte(val[i].b, 1);
		led_matrix_send_byte(val[i].g, 1);
		led_matrix_send_byte(val[i].r, 1);
	}
	pulse_LAT();
	led_matrix_activate_row(row);
}

void led_matrix_init_bank0(void)	{
	for(int i = 0; i < 24; ++i)	{ led_matrix_send_byte(0xff, 0); }
	pulse_LAT();
}

void image_load(void)	{
	/* When the buffer is loaded, the former image becomes a new 
	 *  buffer. As a result it is reset in memory. */
	if(currentBuffer == buffer1)	{
		currentImage = buffer1;
		currentBuffer = buffer2;
	} else	{
		currentImage = buffer2;
		currentBuffer = buffer1;
	}
	NVIC_EnableIRQ(TIM3_IRQn);	//Allowing the display
	memset(currentBuffer, 0, LED_MATRIX_N_LEDS * sizeof(rgb_color));
}

void image_update(int i, uint8_t val)	{
	switch(i % 3)	{
		case LED_MATRIX_RED		: currentBuffer[i / 3].r = val; break;
		case LED_MATRIX_GREEN	: currentBuffer[i / 3].g = val; break;
		case LED_MATRIX_BLUE	: currentBuffer[i / 3].b = val; break;
		default		: break;
	}
}

void image_reset(void)	{
	/* Reseting the image results in both buffers to be reset and the
	 * display to be stopped. */
	NVIC_DisableIRQ(TIM3_IRQn);
	memset(buffer1, 0, LED_MATRIX_N_LEDS * sizeof(rgb_color));
	memset(buffer2, 0, LED_MATRIX_N_LEDS * sizeof(rgb_color));
}
