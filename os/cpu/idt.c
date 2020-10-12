#include "idt.h"

#include <stdint.h>

void idt_set_gate(uint8_t n, uint32_t base, uint16_t selector, uint8_t flags)
{
    idt_entries[n].low_offset   = (uint16_t)(base & 0xFFFF);
    idt_entries[n].high_offset  = (uint16_t)((base >> 16) & 0xFFFF);
    idt_entries[n].selector     = selector;
    idt_entries[n].flags        = flags;
    idt_entries[n].always0      = 0x00;
}