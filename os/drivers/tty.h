#ifndef TTY_H_
#define TTY_H_


#include <stdint.h>
#include <stddef.h>

typedef struct tty_s {
    size_t row;
    size_t col;
    uint8_t color;
    uint16_t *buffer;
} tty_t;

void terminal_initialize(void);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_write_dec(uint32_t n);
void terminal_writestring(const char* data);

#endif /* TTY_H_ */