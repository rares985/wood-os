#include "stdlib.h"
#include "string.h"

#include <stdint.h>
#include <stddef.h>

int atoi(const char *str)
{
    int value = 0;
    int pow = 1;

    for(int i = strlen(str) - 1; i >= 0; i--)
    {
        value = (str[i] - '0') * pow + value;
        pow *= 10;
    }
    return value;
}