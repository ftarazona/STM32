#include "accelerometer.h"

void accelerometer_init()	{
	/* The initialization has two parts.
	 * First the LSM6DSL is turned on, then the accelerometer is set
	 * to a proper mode. */
	uint8_t turn_on[2] = {XL_CTRL1, 0x60};
	i2c_send(ACCELEROMETER_I2C_ADDRESS, turn_on, 2);
	uint8_t set_up[2] = {XL_INT1_CTRL, XL_INT1_CTRL_DRDY};
	i2c_send(ACCELEROMETER_I2C_ADDRESS, set_up, 2);
}

void accelerometer_get(int16_t * x, int16_t * y, int16_t * z)	{
	//First we have to check wether new data is available.
	uint8_t ready = 0;
	uint8_t xl = 0; 
	uint8_t xh = 0;
	uint8_t yl = 0;
	uint8_t yh = 0;
	uint8_t zl = 0;
	uint8_t zh = 0;
	i2c_read(ACCELEROMETER_I2C_ADDRESS, XL_STATUS_REG, &ready, 1);
	if(ready & XL_STATUS_REG_XLDA)	{
		i2c_read(ACCELEROMETER_I2C_ADDRESS, XL_OUTX_L, &xl, 1);
		i2c_read(ACCELEROMETER_I2C_ADDRESS, XL_OUTX_H, &xh, 1);
		i2c_read(ACCELEROMETER_I2C_ADDRESS, XL_OUTY_L, &yl, 1);
		i2c_read(ACCELEROMETER_I2C_ADDRESS, XL_OUTY_H, &yh, 1);
		i2c_read(ACCELEROMETER_I2C_ADDRESS, XL_OUTZ_L, &zl, 1);
		i2c_read(ACCELEROMETER_I2C_ADDRESS, XL_OUTZ_H, &zh, 1);
	}
	*x = (xh << 8) + xl;
	*y = (yh << 8) + yl;
	*z = (zh << 8) + zl;
}
