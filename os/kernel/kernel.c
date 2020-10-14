#include "tty.h"
#include "idt.h"
#include "keyboard.h"
#include "timer.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "irq.h"
#include "isr.h"

uint8_t *mmap = (uint8_t*)0x8000;

void kernel_main()
{
    terminal_initialize();
    terminal_writestring("Hello, world!\n");


    isr_install();
    irq_install();

    printf("%d", *(uint32_t*)mmap);
}