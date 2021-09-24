#include <stdint.h>

uint32_t *a;
uint32_t *b;
uint32_t *c;

__attribute__((naked)) void f(void)	{
	*a += *c;
	*b += *c;
}
