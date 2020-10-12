#include "string.h"

int memcmp(const void *s1, const void *s2, size_t len)
{
    size_t i;

    const unsigned char *a = (const unsigned char *) s1;
    const unsigned char *b = (const unsigned char *) s2;

    for(i = 0; i < len; i++)
    {
        if (a[i] < b[i])
        {
            return -1;
        }
        else if (a[i] > b[i])
        {
            return 1;
        }
    }

    return 0;
}