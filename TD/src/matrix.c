#include "matrix.h"

/* matrix_init intializes every driver pin in output high speed mode. */
void matrix_init(void)	{
	//Enabling peripherals' clocks
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);

	//Configuring pins in output mode
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE5_Msk) 
						| GPIO_MODER_MODE5_0;
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE4_Msk) 
						| GPIO_MODER_MODE4_0;
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3_Msk) 
						| GPIO_MODER_MODE3_0;

	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1_Msk) 
						| GPIO_MODER_MODE1_0; 
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4_Msk) 
						| GPIO_MODER_MODE4_0;

	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2_Msk) 
						| GPIO_MODER_MODE2_0; 
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_Msk) 
						| GPIO_MODER_MODE15_0;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_Msk) 
						| GPIO_MODER_MODE2_0;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7_Msk) 
						| GPIO_MODER_MODE7_0;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6_Msk) 
						| GPIO_MODER_MODE6_0;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5_Msk) 
						| GPIO_MODER_MODE5_0;
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_Msk) 
						| GPIO_MODER_MODE0_0; 
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3_Msk) 
						| GPIO_MODER_MODE3_0;

	//Configuring pins in high speed mode
	GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED5_Msk) 
						| GPIO_OSPEEDR_OSPEED5_1;
	GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED4_Msk) 
						| GPIO_OSPEEDR_OSPEED4_1;
	GPIOC->OSPEEDR = (GPIOC->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3_Msk) 
						| GPIO_OSPEEDR_OSPEED3_1;

	GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED1_Msk) 
						| GPIO_OSPEEDR_OSPEED1_1; 
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED4_Msk) 
						| GPIO_OSPEEDR_OSPEED4_1;

	GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk) 
						| GPIO_OSPEEDR_OSPEED2_1; 
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED15_Msk) 
						| GPIO_OSPEEDR_OSPEED15_1;
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED2_Msk) 
						| GPIO_OSPEEDR_OSPEED2_1;
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED7_Msk) 
						| GPIO_OSPEEDR_OSPEED7_1;
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED6_Msk) 
						| GPIO_OSPEEDR_OSPEED6_1;
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED5_Msk) 
						| GPIO_OSPEEDR_OSPEED5_1;
	GPIOB->OSPEEDR = (GPIOB->OSPEEDR & ~GPIO_OSPEEDR_OSPEED0_Msk) 
						| GPIO_OSPEEDR_OSPEED0_1; 
	GPIOA->OSPEEDR = (GPIOA->OSPEEDR & ~GPIO_OSPEEDR_OSPEED3_Msk) 
						| GPIO_OSPEEDR_OSPEED3_1;

	//Reseting the led matrix.
	RST(0);
	LAT(1);
	SB(1);
	SCK(0);
	SDA(0);
	ROW0(0);
	ROW1(0);
	ROW2(0);
	ROW3(0);
	ROW4(0);
	ROW5(0);
	ROW6(0);
	ROW7(0);

	active_wait(N_TICKS_DELAY);	//Waits about 100ms
	RST(1);
	init_bank0();	//Sets every bit in bank0 to 1.
}

/* deactivate_rows clears every row. Instead of using 8 instructions,
 * we directly write in BSRRegister */
void deactivate_rows(void)	{
	//ROW0(0); ROW1(0); ROW2(0); ROW3(0); ROW4(0); ROW5(0); ROW6(0); ROW7(0);
	GPIOB->BSRR |= 0x0005 << 16;
	GPIOA->BSRR |= 0x80ec << 16;
}

/* activate_row activates a given row */
void activate_row(int row)	{
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

/* send_byte send 8 bit to the DM163 microcontroller, following the
 * protocol. */
void send_byte(uint8_t val, int bank)	{
	SB(bank);	//Select the bank
	for(int i = 0; i < 8; ++i)	{
		SDA(val & (1 << (7 - i)));
		pulse_SCK
	}
}

/* mat_set_row transmits the information for the DM163 to set a given
 * row to the good values given. */
void mat_set_row(int row, const rgb_color * val)	{
	for(int i = 0; i < 8; ++i)	{
		send_byte(val[i].b, 1);
		send_byte(val[i].g, 1);
		send_byte(val[i].r, 1);
	}
	pulse_LAT
	activate_row(row);
}

/* init_bank0 sets every bit in BANK0 to 1. */
void init_bank0(void)	{
	for(int i = 0; i < 24; ++i)	{
		send_byte(0xff, 0);
	}
	pulse_LAT
}
