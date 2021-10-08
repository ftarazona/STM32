#include "matrix.h"

/* matrix_init intializes every driver pin in output high speed mode. */
void matrix_init(void)	{
	//Enabling peripherals
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);

	//Configuring pins in output mode
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE5_Msk) 
						| GPIO_MODER_MODE5_1;
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE4_Msk) 
						| GPIO_MODER_MODE4_1;
	GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE3_Msk) 
						| GPIO_MODER_MODE3_1;

	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE1_Msk) 
						| GPIO_MODER_MODE1_1; 
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE4_Msk) 
						| GPIO_MODER_MODE4_1;

	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE2_Msk) 
						| GPIO_MODER_MODE2_1; 
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE15_Msk) 
						| GPIO_MODER_MODE15_1;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE2_Msk) 
						| GPIO_MODER_MODE2_1;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE7_Msk) 
						| GPIO_MODER_MODE7_1;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE6_Msk) 
						| GPIO_MODER_MODE6_1;
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE5_Msk) 
						| GPIO_MODER_MODE5_1;
	GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE0_Msk) 
						| GPIO_MODER_MODE0_1; 
	GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODE3_Msk) 
						| GPIO_MODER_MODE3_1;

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

	active_wait(N_TICKS_DELAY);
	RST(1);
}

void deactivate_rows(void)	{
	ROW0(0); ROW1(0); ROW2(0); ROW3(0); ROW4(0); ROW5(0); ROW6(0); ROW7(0); 
}

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

void send_byte(uint8_t val, int bank)	{
	for(int i = 0; i < 8; ++i)	{
		SDA(val & (1 << (8 - i)));
		pulse_SCK;
	}
}

void mat_set_row(int row, const rgb_color * val)	{
	activate_row(row);
	SB(bank);
	for(int i = 0; i < 8; ++i)	{
		send_byte(val[i].b);
		send_byte(val[i].g);
		send_byte(val[i].r);
	}
	pulse_LAT;
}

void init_bank0()	{
	SB(0);
	for(int i = 0; i < 24; ++i)	{
		send_byte(1);
	}
	pulse_LAT;
}
