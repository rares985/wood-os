#include "tty.h"
#include "idt.h"
#include "keyboard.h"
#include "timer.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "irq.h"

void kernel_main()
{

    init_idt();
    irq_install();
    terminal_initialize();
}