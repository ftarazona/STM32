#include "memfuncs.h"

/* memset fils n bytes from s with c */
void memset(int *s, int c, size_t n)	{
	for(int i = 0; i < n; ++i)
		*(s + i) = c;
}

/* memcpy copies memory zone from src to dest (n bytes copied) 
 * The two memory zones should not overlap. */
void memcpy(void *dst, const void *src, size_t n)	{
	for(int i = 0; i < n; ++i)
		*(dst + i) = *(src + i);
}

/* memmove does the same as memcpy but manages overlaps */
void memmove(void *dst, const void *src, size_t n)	{
	if(src + n > dst)	{	//if the src zone overlaps the beginning of dst
		for(int i = n - 1; i >= 0; --i)	{
			*(dst + i) = *(src + i);
		}
	} else	{	//The src zone may be overlapping the end of dst
		for(int i = 0; i < n; ++i)	{
			*(dst + i) = *(src + i);
		}
	}
}

int memcmp(int *s1, int *s2, size_t n)	{
	for(int i = 0; i < n; ++i)	{
		int c = *(s1 + i) - *(s2 + i);
		if(c != 0)
			return c;
	}
	return 0;
}
