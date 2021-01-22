#include "tty.h"
#include "idt.h"
#include "keyboard.h"
#include "timer.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "irq.h"
#include "isr.h"
#include <physmem.h>
#include <phys.h>


void kernel_main()
{
    isr_install();
    irq_install();
    terminal_initialize();

    // physmem_init();
    physalloc_init();

    uint32_t *page = (uint32_t*)physmem_alloc_block();

    printf("Address of first allocated page: %x\n", page);

    physmem_free_block(page);

    page = (uint32_t*)physmem_alloc_block();
    printf("Address of allocated page: %x\n", page);

    uint32_t *page2 = (uint32_t*)physmem_alloc_block();
    printf("Address of allocated page2: %x\n", page2);

    physmem_free_block(page);
    physmem_free_block(page2);

    while (1) {

    };

}