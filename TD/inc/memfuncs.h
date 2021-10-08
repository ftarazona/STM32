#ifndef MEMFUNCS_H
#define MEMFUNCS_H

#include <stddef.h>
#include <stdint.h>

void *memset(void *src, int c, size_t n);
void *memcpy(void *dst, const void *src, size_t n);
void *memmove(void *dst, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

#endif
