#include "tty.h"
#include "idt.h"
#include "keyboard.h"
#include "timer.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "irq.h"
#include "isr.h"
#include "physmem.h"


void kernel_main()
{
    isr_install();
    irq_install();
    terminal_initialize();
    printf("Hello, world!\n");

    physmem_init();

    while (1) {

    };

}