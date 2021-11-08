#include "random.h"

void random_init()	{
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_RNGEN);
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
