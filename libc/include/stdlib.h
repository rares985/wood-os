#ifndef STDLIB_H_
#define STDLIB_H_

#include <stdint.h>

int     atoi(const char *str);
char    *itoa(uint32_t value, char *str, int base);

#endif /* STDLIB_H_ */