#include "tty.h"
#include "idt.h"
#include "keyboard.h"
#include "timer.h"
#include "string.h"
#include "stdlib.h"

#define CLK_FREQ_MS 50

void kernel_main()
{

    init_idt();
    init_keyboard();
    init_timer(CLK_FREQ_MS);

    __asm__ __volatile__ ("sti");

    terminal_initialize();

}