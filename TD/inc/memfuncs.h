#ifndef MEMFUNCS_H
#define MEMFUNCS_H

void memset(int *src, int c, size_t n);
void memcpy(int *dst, int *src, size_t n);
void memmove(int *dst, int *src, size_t n);
int memcmp(int *s1, int *s2, size_t n);

#endif
