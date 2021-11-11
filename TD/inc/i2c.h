/* i2c.h -- I2C2 Driver
 * ********************
 * This header declares proper functions for using the I2C2.
 * This is meant to be used in order to communication with the LSM6DSL
 * module.
 * */

#ifndef I2C_H
#define I2C_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

void i2c_master_init();

/* Sends data on the I2C bus. */
void i2c_send(uint8_t addr, uint8_t* data, int size);

/* Reads data from the I2C bus from a subaddress of the module */
void i2c_read(uint8_t addr, uint8_t subaddr, uint8_t* data, int nbytes);

#endif
