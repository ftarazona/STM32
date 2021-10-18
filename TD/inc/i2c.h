#ifndef I2C_H
#define I2C_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

void i2c_master_init(uint8_t saddr);
void i2c_send(uint8_t data, uint8_t subaddr);
uint8_t i2c_receive(uint8_t subaddr);

#endif
