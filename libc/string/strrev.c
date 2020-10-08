#include "string.h"
#include <stddef.h>

char *strrev(char *str)
{
    char *aux = NULL;
    int st = 0;
    int end = strlen(str);

    while (st < end)
    {
        *aux = *(str+end);
        *(str+st) = *(str+end);
        *(str+end) = *aux;

        st++;
        end--;
    }
    return str;
}