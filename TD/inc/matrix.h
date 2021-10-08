#ifndef MATRIX_H
#define MATRIX_H

/* Pin functions :
 *  SB	~ PC5
 *  LAT	~ PC4
 *  RST	~ PC3
 *  SCK	~ PB1
 *  SDA	~ PA4
 *  C0	~ PB2
 *  C1	~ PA15
 *  C2	~ PA2
 *  C3	~ PA7
 *  C4	~ PA6
 *  C5	~ PA5
 *  C6	~ PB0
 *  C7	~ PA3 */
#include <stm32l4xx.h>
#include <stm32l475xx.h>


void matrix_init(void);

#endif
