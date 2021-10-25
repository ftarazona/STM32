#ifndef I2C_H
#define I2C_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

void i2c_master_init();
void i2c_put(uint8_t data);
uint8_t i2c_get(void);
void i2c_send(uint8_t* data, int size);
void i2c_read(uint8_t addr, uint8_t subaddr, uint8_t* data, int nbytes);

#endif
