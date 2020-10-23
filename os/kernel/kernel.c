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
    terminal_initialize();
    terminal_putchar('H');
    terminal_write("abc", 3);

    while (1) {

    };

    // isr_install();
    // irq_install();

}