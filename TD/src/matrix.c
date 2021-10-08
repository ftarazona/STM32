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


}
