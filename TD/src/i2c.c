#include "i2c.h"

void i2c_master_init()	{
	//Enable clock for I2C
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN);

	CLEAR_BIT(I2C1->CR1, I2C_CR1_PE);

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

void i2c_send(uint8_t* data, int size)	{
	//Indicates the number of bytes to be sent
	I2C1->CR2 = (I2C1->CR2 & ~I2C_CR2_NBYTES_Msk) | (size << I2C_CR2_NBYTES_Pos);

	//An automatic STOP will be sent when NBYTES are transferred.
	SET_BIT(I2C1->CR2, I2C_CR2_AUTOEND);

	//Setting the slave address
	I2C1->CR2 = (I2C1->CR2 & ~I2C_CR2_SADD_Msk) | (data[0]);

	//Indicates the master is requesting a write transfer
	CLEAR_BIT(I2C1->CR2, I2C_CR2_RD_WRN);

	//Emitting a START signal
	SET_BIT(I2C1->CR2, ISC_CR2_START);


	for(int i = 1; i < NBYTES; ++i)	{
		while(!(I2C1->ISR & I2C_ISR_TXIS))	{
			if(I2C1->ISR & I2C_ISR_NACKF)	{ return; }
		}
		I2C1->TXDR = data[i];
	}
}

void i2c_read(uint8_t addr, uint8_t subaddr, uint8_t* data, int nbytes)	{
	CLEAR_BIT(I2C1->CR2, I2C_CR2_AUTOEND);

	//Setting the slave address
	I2C1->CR2 = (I2C1->CR2 & ~I2C_CR2_SADD_Msk) | (addr);

	//Indicates the master is requesting a write transfer
	CLEAR_BIT(I2C1->CR2, I2C_CR2_RD_WRN);

	//Emitting a START signal
	SET_BIT(I2C1->CR2, ISC_CR2_START);

	//Transmitting the subaddr
	while(!(I2C1->ISR & I2C_ISR_TXIS));
	I2C1->TXDR = subaddr;

	SET_BIT(I2C1->CR2 & ~I2C_CR2_RD_WRN);

	//Indicates the number of bytes to be sent
	I2C1->CR2 = (I2C1->CR2 & ~I2C_CR2_NBYTES_Msk) | (size << I2C_CR2_NBYTES_Pos);
	SET_BIT(I2C1->CR2, I2C_CR2_AUTOEND);

	for(int i = 0; i < nbytes; ++i)	{
		while(!(I2C1->ISR & I2C_ISR_RXNE));
		data[i] = I2C1->RXDR;
	}
}
