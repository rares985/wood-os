#include <stddef.h>
#include <stdint.h>

#include "string.h"

void *memset(void *dest, uint8_t value, size_t len)
{
    uint8_t *ptr = (uint8_t*) dest;

    for(size_t i = 0; i < len; i++)
    {
        ptr[i] = value;
    }
    return dest;
}