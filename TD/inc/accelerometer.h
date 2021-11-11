/* accelerometer.h -- Accelerometer Driver
 * ***************************************
 * This header declares proper functions for using the LSM6DSL as an
 * accelerometer.
 *
 * The module is connected with an I2C bus.
 * */

#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#define ACCELEROMETER_I2C_ADDRESS 0xd4

#define XL_INT1_CTRL	0x0d
#define XL_CTRL1	 	0x10
#define XL_STATUS_REG	0x1e
#define XL_OUTX_L		0x28
#define XL_OUTX_H		0x29
#define XL_OUTY_L		0x2a
#define XL_OUTY_H		0x2b
#define XL_OUTZ_L		0x2c
#define XL_OUTZ_H		0x2d

#define XL_INT1_CTRL_DRDY	0x01
#define XL_STATUS_REG_XLDA	0x01

#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#define OUTX_L_XL	0x28
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#define OUTX_L_XL	0x28
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#define OUTX_L_XL	0x28
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#define OUTX_L_XL	0x28
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();
#include "i2c.h"

/* Must be preceeded by i2c_master_init. */
void accelerometer_init();

/* Gives the current orientation of the acceleration vector.
 * It takes three pointers as parameters and sets them to the
 * measured values. */
void accelerometer_get(int16_t *x, int16_t *y, int16_t *z);

#endif
