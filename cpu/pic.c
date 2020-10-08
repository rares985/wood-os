#include <stddef.h>
#include <stdint.h>

#include "pic.h"
#include "isr.h"
#include "io.h"


/* 
 * In protected mode, the IRQs 0 to 7 conflict with the CPU exception which are reserved by Intel up until 0x1F. 
 * (It was an IBM design mistake.) Consequently it is difficult to tell the difference between an IRQ or an software error. 
 * It is thus recommended to change the PIC's offsets (also known as remapping the PIC) so that IRQs use non-reserved vectors. 
 * A common choice is to move them to the beginning of the available range (IRQs 0..0xF -> INT 0x20..0x2F). 
 * For that, we need to set the master PIC's offset to 0x20 and the slave's to 0x28.
 */
void PIC_remap(int offset1, int offset2)
{
	unsigned char a1, a2; 
	a1 = inb(PIC1_DATA);                        /* Save the masks */
	a2 = inb(PIC2_DATA);

	outb(PIC1_CMD, ICW1_INIT | ICW1_ICW4);      /* Start init sequence (cascade mode) */
	io_wait();

	outb(PIC2_CMD, ICW1_INIT | ICW1_ICW4);
	io_wait();

	outb(PIC1_DATA, offset1);                   /* ICW2: Master PIC vector offset */
	io_wait();

	outb(PIC2_DATA, offset2);                   /* ICW2: Slave PIC vector offset */
	io_wait();

	outb(PIC1_DATA, 4);                         /* ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100) */
	io_wait();

	outb(PIC2_DATA, 2);                         /* ICW3: tell Slave PIC its cascade identity (0000 0010) */
	io_wait(); 

	outb(PIC1_DATA, ICW4_8086);
	io_wait();

	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	outb(PIC1_DATA, a1);                        /* Restore the saved masks */
	outb(PIC2_DATA, a2);
}

/* This is issued to the PIC chips at the end of an IRQ-based interrupt routine.
 * If the IRQ came from the Master PIC, it is sufficient to issue this command only to the Master PIC;
 * however if the IRQ came from the Slave PIC, it is necessary to issue the command to both PIC chips.
 */
void PIC_sendEOI(uint8_t irq)
{
    if (irq >= IRQ8)
    {
        outb(PIC2_CMD, PIC_EOI);
    }
    outb(PIC1_CMD, PIC_EOI);
}
