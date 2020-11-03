#include "stdio.h"
#include "string.h"
#include "tty.h"
#include "stdlib.h"
#include <limits.h>

#include <stdarg.h>

#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>



int printf(const char *format, ...)
{
    int written_bytes = 0;
    int i = 0;
    char *cptr = NULL;
    char ch = '\0';
    int intarg = 0;
    char str[10] = {0};

    va_list params;
    va_start(params, format);

    while (format[i] != '\0')
    {
        if (format[i] == '%')
        {
            switch(format[i+1])
            {
                case 's':
                    cptr = va_arg(params, char*);
                    terminal_writestring(cptr);
                    break;
                case 'c':
                    ch = (char) va_arg(params, int);
                    terminal_putchar(ch);
                    break;
                case 'd':
                    intarg = va_arg(params, int);
                    terminal_writestring(itoa(intarg, str, 10));
                    break;
                case 'x':
                    intarg = va_arg(params, int);
                    terminal_writestring(itoa(intarg, str, 16));
                    break;
                default:
                    break;
            }
            /* Jump over the next character */
                i += 1;
        }
        else
        {
            terminal_putchar(format[i]);
        }
        i += 1;
    }

    va_end(params);
    return written_bytes;
}
