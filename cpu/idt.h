#ifndef IDT_H_
#define IDT_H_

#include <stddef.h>
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
    uint16_t    high_offset; /* Higher 16 bits of handler function address */
} __attribute__((packed));
typedef struct idt_entry_s idt_entry_t;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
struct idt_ptr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr_s idt_ptr_t;


void init_idt(void);

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();
extern void irq16();
extern void irq17();


#endif /* IDT_H_ */