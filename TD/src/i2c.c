#include "i2c.h"

void i2c_master_init(uint8_t saddr)	{
	//Enable clock for I2C
	SET_BIT(RCC->APB1ENR1, RCC_APB1ENR1_I2C1EN);

}

void i2c_send(uint8_t data, uint8_t subaddr)	{

}

void i2c_recevie(uint8_t data)	{

}
