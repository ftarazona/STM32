#include "fibo.h"

#define NMAX 1000

static int mem_fibo[NMAX];

/* fibo calculates the terms of fibonacci sequence.
   It is recursive with memoisation. */
int fibo(int n)	{
	if(n == 0 || n == 1)	{
		mem_fibo[n] = 1;
		return 1;
	} else	{
		if(mem_fibo[n] != 0)	{
			return mem_fibo[n];
		} else	{
			mem_fibo[n] = fibo(n - 1) + fibo(n - 2);
			return mem_fibo[n];
		}
	}
}
