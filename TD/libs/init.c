#include "memfuncs.h"

/* This file make some initializations before entering main. */

extern int _bss, _ebss;
#ifndef DEBUG
	extern int _data, _edata, _data_flash;
	extern int _nvic, _envic, _nvic_flash;
	extern int _text, _etext, _text_flash;
#endif

/* init_bss zero out the .bss section. */
void init_bss(void)	{
	memset(&_bss, 0, 4 * (&_ebss - &_bss));
}

void init_data(void)	{
#ifndef DEBUG
	memcpy(&_data, &_data_flash, 4 * (&_edata - &_data));
#endif
}

void init_nvic(void)	{
#ifndef DEBUG
	memcpy(&_nvic, &_nvic_flash, 4 * (&_envic - &_nvic));
#endif
}

__attribute__((section(".xiptext"))) void init_text(void) 	{
#ifndef DEBUG
	memcpy(&_text, &_text_flash, 4 * (&_etext - &_text));
#endif
}
