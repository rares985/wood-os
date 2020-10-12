#ifndef IDT_H_
#define IDT_H_

#include <stdint.h>

/* How every interrupt gate (handler) is defined */
struct idt_entry_s {
    uint16_t    low_offset;     /* Lower 16 bits of handler function address */
    uint16_t    selector;       /* Kernel segment selector */
    uint8_t     always0;
    /* First byte
     * Bit 7: "Interrupt is present"
     * Bits 6-5: Privilege level of caller (0=kernel..3=user)
     * Bit 4: Set to 0 for interrupt gates
     * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    uint8_t     flags; 
    uint16_t    high_offset;    /* Higher 16 bits of handler function address */
} __attribute__((packed));
typedef struct idt_entry_s idt_entry_t;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
struct idt_ptr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr_s idt_ptr_t;

#define IDT_ENTRIES     256


idt_entry_t idt_entries[IDT_ENTRIES];
idt_ptr_t   idt_ptr;


void idt_set_gate(uint8_t n, uint32_t base, uint16_t selector, uint8_t flags);

#endif /* IDT_H_ */