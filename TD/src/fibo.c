#include "fibo.h"

#define NMAX 1000

static int fibo[NMAX];

/* fibo calculates the terms of fibonacci sequence.
   It is recursive with memoisation. */
int fibo(int n)	{
	if(n == 0 || n == 1)	{
		fibo[n] = 1;
		return 1;
	} else	{
		if(fibo[n] != 0)	{
			return fibo[n];
		} else	{
			fibo[n] = fibo(n - 1) + fibo(n - 2);
		}
	}
}
