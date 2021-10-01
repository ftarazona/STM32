#include <stdio.h>

void f()	{
	void* p = &p;
	printf("p in f : %x\n", p);
}

int main()	{
	void *p = &p;
	printf("p in main : %x\n", p);
	f();
	return 0;
}
