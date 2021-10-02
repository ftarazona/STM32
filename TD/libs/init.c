/* This file make some initializations before entering main. */

extern int _bss, _ebss;

/* init_bss zero out the .bss section. */
void init_bss(void)	{
	int* cur = &_bss;
	while(cur != &_ebss)	{
		*(cur++) = 0;
	}
}
