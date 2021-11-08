#ifndef RANDOM_H
#define RANDOM_H

#include "stm32l4xx.h"
#include "stm32l475xx.h"

void random_init();

uint32_t random_get();

#endif
