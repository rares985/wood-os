#include "stdlib.h"
#include "string.h"

#include <stdint.h>
#include <stddef.h>

char *itoa(uint32_t value, char *str, int base)
{
    int i = 0;
    int remainder = 0;
    if (0 == value)
    {
        str[0] = '0';
        str[1] = '\0';
    }
    else
    {
        while (value != 0)
        {
            remainder = value % base;
            str[i] = (remainder > 9) ? (remainder - 10) + 'a' : remainder + '0';
            value = value / base;
            i += 1;
        }
        str[i] = '\0';
    }

    strrev(str);

    return str;
}