#ifndef STRING_H_
#define STRING_H_

#include <stddef.h>
#include <stdint.h>

int     memcmp(const void *s1, const void *s2, size_t len);
void    *memcpy(void * __restrict dest, const void* __restrict src, size_t len);
void    *memset(void *dest, uint8_t value, size_t len);
size_t  strlen(const char *str);
char *strrev(char *str);

#endif /* STRING_H_ */