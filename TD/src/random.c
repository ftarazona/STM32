#include "random.h"

void random_init()	{
	/* The RNG requires two clocks : one for peripheral registers
	 * (on bus AHB2) and one for generating the analog noise.
	 * This one has to be faster than AHB2 clock divided by 16.
	 * It has to be set on a 48MHz clock. */
	
	//Enabling peripheral clock
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);

	//Enabling a 48MHz and selecting it for analog noise.
	SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQEN);
	RCC->CCIPR = (RCC->CCIPR & ~RCC_CCIPR_CLK48SEL_Msk) | (2 << RCC_CCIPR_CLK48SEL_Pos);

	SET_BIT(RNG->CR, RNG_CR_RNGEN);
}

uint32_t random_get()	{
	if(!(RNG->SR & RNG_SR_SEIS) && !(RNG->SR & RNG_SR_CEIS))	{
		return RNG->DR;
	} else	{
		return 0;
	}
}
