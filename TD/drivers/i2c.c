#include "i2c.h"
#include "uart.h"

void i2c_master_init()	{
	//Enabling clock for GPIOB
	SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);

	//Configuring SCK and SDA pins
	GPIOB->MODER = (GPIOB->MODER & 0xff0fffff) | 0x00a00000;
	GPIOB->AFR[1] = (GPIOB->AFR[1] & 0xffff00ff) | 0x00004400;

	//Enable clock for I2C
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C2EN);

	//Disable I2C
	CLEAR_BIT(I2C2->CR1, I2C_CR1_PE);

	//Setting frequency to 400kHz
	I2C2->TIMINGR |= 	(200 << I2C_TIMINGR_SCLL_Pos) |
						(200 << I2C_TIMINGR_SCLH_Pos);

	//Enabling I2C
	SET_BIT(I2C2->CR1, I2C_CR1_PE);
}

void i2c_send(uint8_t addr, uint8_t* data, int size)	{
	//Indicates the number of bytes to be sent
	I2C2->CR2 = (I2C2->CR2 & ~I2C_CR2_NBYTES_Msk) | (size << I2C_CR2_NBYTES_Pos);

	//We want a hardware STOP condition to be sent.
	SET_BIT(I2C2->CR2, I2C_CR2_AUTOEND);

	//size should not be greater than 255, hence no reload needed
	CLEAR_BIT(I2C2->CR2, I2C_CR2_RELOAD);

	//Setting the slave address
	I2C2->CR2 = (I2C2->CR2 & ~I2C_CR2_SADD_Msk) | addr;

	//Indicates the master is requesting a write transfer
	CLEAR_BIT(I2C2->CR2, I2C_CR2_RD_WRN);

	//Emitting a START signal
	SET_BIT(I2C2->CR2, I2C_CR2_START);
	while(I2C2->CR2 & I2C_CR2_START);

	for(int i = 0; i < size; ++i)	{
		while(!(I2C2->ISR & I2C_ISR_TXE));
		I2C2->TXDR = data[i];
	}

	while(I2C2->CR2 & I2C_CR2_STOP);
}

void i2c_read(uint8_t addr, uint8_t subaddr, uint8_t* data, int nbytes)	{
	CLEAR_BIT(I2C2->CR2, I2C_CR2_AUTOEND);
	CLEAR_BIT(I2C2->CR2, I2C_CR2_RELOAD);

	//Setting the slave address
	I2C2->CR2 = (I2C2->CR2 & ~I2C_CR2_SADD_Msk) | (addr);
	
	//Indicates the number of bytes to be sent
	I2C2->CR2 = (I2C2->CR2 & ~I2C_CR2_NBYTES_Msk) | (1 << I2C_CR2_NBYTES_Pos);

	//Indicates the master is requesting a write transfer
	CLEAR_BIT(I2C2->CR2, I2C_CR2_RD_WRN);

	//Emitting a START signal
	SET_BIT(I2C2->CR2, I2C_CR2_START);
	while(I2C2->CR2 & I2C_CR2_START);

	//Transmitting the subaddr
	while(!(I2C2->ISR & I2C_ISR_TXE));
	I2C2->TXDR = subaddr;


	//Second transfer, we can now set the autoend
	SET_BIT(I2C2->CR2, I2C_CR2_AUTOEND);

	//Master requires a receiving transfer
	SET_BIT(I2C2->CR2, I2C_CR2_RD_WRN);

	//Setting the slave address in reading mode
	I2C2->CR2 = (I2C2->CR2 & ~I2C_CR2_SADD_Msk) | addr;

	//Indicates the number of bytes to be sent
	I2C2->CR2 = (I2C2->CR2 & ~I2C_CR2_NBYTES_Msk) | (nbytes << I2C_CR2_NBYTES_Pos);
	
	//Emitting a REPEATED START signal
	SET_BIT(I2C2->CR2, I2C_CR2_START);
	while(I2C2->CR2 & I2C_CR2_START);

	for(int i = 0; i < nbytes; ++i)	{
		while(!(I2C2->ISR & I2C_ISR_RXNE));
		data[i] = I2C2->RXDR;
	}

	while(I2C2->CR2 & I2C_CR2_STOP);
}
