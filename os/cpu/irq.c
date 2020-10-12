#include "irq.h"
#include "timer.h"
#include "keyboard.h"

#define CLK_FREQ_MS 50

void irq_install(void)
{
    __asm__ __volatile__ ("sti");
    init_timer(CLK_FREQ_MS);
    init_keyboard();
}