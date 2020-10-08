#include "isr.h"
#include "tty.h"
#include "io.h"
#include "pic.h"

#include <stdint.h>
#include <stddef.h>

#include "pic.h"

#define INTERRUPT_NO    256

isr_t interrupt_handlers[INTERRUPT_NO];


void isr_handler(registers_t regs)
{
    (void)regs;
}

void irq_handler(registers_t regs)
{
    /* Sends EOI to the PICs */
    PIC_sendEOI(regs.int_no);
    /* Call handler if it is available */
    if (interrupt_handlers[regs.int_no] != NULL)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}