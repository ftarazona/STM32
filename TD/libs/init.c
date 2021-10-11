#include <stddef.h>
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

/* init_data copies section .data from flash to ram */
void init_data(void)	{
#ifndef DEBUG
	memcpy(&_data, &_data_flash, 4 * (&_edata - &_data));
#endif
}

/* init_nvic copies section .nvic from flash to ram */
void init_nvic(void)	{
#ifndef DEBUG
	memcpy(&_nvic, &_nvic_flash, 4 * (&_envic - &_nvic));
#endif
}

/* The .text section is stored in RAM, but XIP is slower than executing
 * from RAM. A small section .xiptext contains preliminary code that
 * copies the section .text from flash to RAM */
__attribute__((section(".xiptext"))) void init_text(void) 	{
#ifndef DEBUG
	/* No call to memcpy, which is in RAM.
	 * We could also put memcpy in .xiptext.
	 * Made this choice so that it is faster if we want to use it then
	 * */
	for(int i = 0; i < 4 * (&_etext - &_text); ++i)	{
		*((uint8_t*)&_text + i) = *((uint8_t*)&_text_flash + i);
	}
#endif
}
