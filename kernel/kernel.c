#include "tty.h"

void kernel_main()
{
    terminal_initialize();
    terminal_write("Hello, world!", 13);
}