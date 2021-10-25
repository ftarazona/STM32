#include "i2c.h"

void i2c_master_init(uint8_t saddr)	{
	//Enable clock for I2C
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN);

	//Setting frequency to 400kHz
	I2C1->TIMINGR |= 	(200 << I2C_TIMINGR_SCLL_Pos) |
							(200 << I2C_TIMINGR_SCLH_Pos);

	//Enabling I2C
	SET_BIT(I2C1->CR1, I2C_CR1_PE);
}

void i2c_put(uint8_t data)	{
	while(!(I2C1->ISR & I2C_ISR_TXE));

	I2C1->TXDR = data;
}

uint8_t i2c_get()	{
	while(!(I2C1->ISR & I2C_ISR_RXNE));

	return I2C1->RXDR & 255;
}
