#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#define RADDR 0xd5
#define WADDR 0xd4

#include "i2c.h"

void accelerometer_init();
void accelerometer_get(int16_t *x, int16_t *y, int16_t *z);

#endif
