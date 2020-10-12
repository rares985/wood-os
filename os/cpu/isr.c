#include "isr.h"
#include "tty.h"
#include "io.h"
#include "pic.h"
#include "stdlib.h"
#include "timer.h"
#include "keyboard.h"

#include "stdio.h"

#include <stdint.h>
#include <stddef.h>

#include "pic.h"

#define INTERRUPT_NO    256

static isr_t interrupt_handlers[INTERRUPT_NO];

void isr_handler(registers_t *regs)
{
    printf("ISR Unhandled exception: %d",regs->int_no);
    terminal_writestring("\n");
    printf("Err code = %d", regs->err_code);
    terminal_writestring("\n");
}

void irq_handler(registers_t *regs)
{
    printf("IRQ Unhandled exception: %d",regs->int_no);
    terminal_writestring("\n");
    printf("Err code = %d", regs->err_code);
    terminal_writestring("\n");
    /* Sends EOI to the PICs */
    PIC_sendEOI(regs->int_no);
    /* Call handler if it is available */
    if (interrupt_handlers[regs->int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(regs);
    }
    else
    {
        printf("Received unhandled IRQ %d", regs->int_no);
    }
}

void register_interrupt_handler(uint8_t n, isr_t handler)
{
    interrupt_handlers[n] = handler;
}