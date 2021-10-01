extern int _bss, _ebss;

void init_bss(void)	{
	int* cur = &_bss;
	while(cur != &_ebss)	{
		*(cur++) = 0;
	}
}
