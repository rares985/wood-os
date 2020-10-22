#include "tty.h"
#include "idt.h"
#include "keyboard.h"
#include "timer.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "irq.h"
#include "isr.h"


void kernel_main()
{
    const char *debug = "DEBUGDEBUGDEBUGDEBUGDEBUG";
    // terminal_initialize();
    // terminal_writestring("Hello, world!\n");

    while (1) {

    };

    char *mem = (char*)0xB8000;
    *mem = 'X';
    // isr_install();
    // irq_install();

}