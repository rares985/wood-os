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
    isr_install();
    irq_install();
    terminal_initialize();
    terminal_writestring("Hello, world!\n");

    while (1) {

    };


}