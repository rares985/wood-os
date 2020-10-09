#include "string.h"
#include <stddef.h>

char *strrev(char *str)
{
    char aux;
    int st = 0;
    int end = strlen(str) - 1;
    while (st < end)
    {
        aux = *(str+end);
        *(str+end) = *(str+st);
        *(str+st) = aux;
        st++;
        end--;
    }
    return str;
}