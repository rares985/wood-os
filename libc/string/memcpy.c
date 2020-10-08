#include <stddef.h>
#include <stdint.h>

#include "string.h"

void *memcpy(void * __restrict dest, const void* __restrict source, size_t len)
{
    unsigned char *dst = (unsigned char *) dest;
    const unsigned char *src = (const unsigned char *) source;

    for (size_t i = 0; i < len; i++)
    {
        dst[i] = src[i];
    }
    return dest;
}