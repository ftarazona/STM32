#include "memfuncs.h"

/* memset fils n bytes from s with c */
void *memset(void *s, int c, size_t n)	{
	for(size_t i = 0; i < n; ++i)
		*((uint8_t*)s + i) = c;

	return s;
}

/* memcpy copies memory zone from src to dest (n bytes copied) 
 * The two memory zones should not overlap. */
void *memcpy(void *dst, const void *src, size_t n)	{
	for(size_t i = 0; i < n; ++i)
		*((uint8_t*)dst + i) = *((uint8_t*)src + i);

	return dst;
}

/* memmove does the same as memcpy but manages overlaps */
void *memmove(void *dst, const void *src, size_t n)	{
	if(src + n > dst)	{	//if the src zone overlaps the beginning of dst
		for(size_t i = n; i > 0; --i)	{
			*((uint8_t*)dst + i - 1) = *((uint8_t*)src + i - 1);
		}
	} else	{	//The src zone may be overlapping the end of dst
		for(size_t i = 0; i < n; ++i)	{
			*((uint8_t*)dst + i) = *((uint8_t*)src + i);
		}
	}

	return dst;
}

int memcmp(const void *s1, const void *s2, size_t n)	{
	for(size_t i = 0; i < n; ++i)	{
		uint8_t c = *((uint8_t*)s1 + i) - *((uint8_t*)s2 + i);
		if(c != 0)
			return c;
	}
	return 0;
}
