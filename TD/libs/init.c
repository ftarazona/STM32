#include "memfuncs.h"

/* This file make some initializations before entering main. */

extern int _bss, _ebss;

/* init_bss zero out the .bss section. */
void init_bss(void)	{
	memset(&_bss, 0, &_ebss - &_bss);
}
