/* random.h -- Random Number Generator Driver
 * ******************************************
 * This header declares proper functions for using the rnadom number
 * generator embedded.
 * */

#ifndef RANDOM_H
#define RANDOM_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

void random_init();

/* Returns a random 32-bit number different from 0.
 * If 0 is returned, the value may not be considered random. */
uint32_t random_get();

#endif
