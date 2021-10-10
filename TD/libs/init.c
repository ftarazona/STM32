#include "memfuncs.h"

/* This file make some initializations before entering main. */

extern int _bss, _ebss, _data, _edata, _data_flash;

/* init_bss zero out the .bss section. */
void init_bss(void)	{
	memset(&_bss, 0, 4 * (&_ebss - &_bss));
}

void init_data(void)	{
	memcpy(&_data, &_data_flash, 4 * (&_edata - &_data));
}
