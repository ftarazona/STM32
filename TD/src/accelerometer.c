#include "accelerometer.h"

void accelerometer_init()	{
	i2c_master_init();
	uint8_t accel_init[3] = {WADDR, 0x10, 0x60};
	i2c_send(accel_init, 3);
	uint8_t accel_int[3] = {WADDR, 0x0d, 0x01};
	i2c_send(accel_int, 3);
}

void accelerometer_get(int16_t * x, int16_t * y, int16_t * z)	{
	uint8_t ready = 0;
	i2c_read(RADDR, 0x1e, &ready, 1);
	if(ready & 0x01)	{
		uint8_t xl; 
		uint8_t xh;
		uint8_t yl;
		uint8_t yh;
		uint8_t zl;
		uint8_t zh;
		i2c_read(RADDR, 0x28, &xl, 1);
		i2c_read(RADDR, 0x29, &xh, 1);
		i2c_read(RADDR, 0x2a, &yl, 1);
		i2c_read(RADDR, 0x2b, &yh, 1);
		i2c_read(RADDR, 0x2c, &zl, 1);
		i2c_read(RADDR, 0x2d, &zh, 1);
		*x = (xh << 8) + xl;
		*y = (yh << 8) + yl;
		*z = (zh << 8) + zl;
	} else	{
		*x = 0;
		*y = 0;
	}
}
