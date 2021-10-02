#include "fibo.h"

/* fibo calculates the terms of fibonacci sequence.
   It is recursive and kind of dumb for now. */
int fibo(int n)	{
	if(n == 0 || n == 1)	{
		return 1;
	} else	{
		return fibo(n - 1) + fibo(n - 2);
	}
}
