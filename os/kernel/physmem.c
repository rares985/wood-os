/*
 * For paging to be set up, some structures have to be prepared in memory.
 * On x86 systems, the maximum addresable memory is 4GiB. The x86 architecture
 * requires that the structures which describe this memory be setup as follows:
 * CR3 Register: Must hold a 4KiB-aligned address at which the Paging Directory (PD) structure starts
 * Page Directory (PD): At the address specified in CR3, there must be an array of 1024 entries, each 4 bytes in size
 *  Each of the entries contains information about a Page Table, as explained below:
 *      Bits 31-11: PT 4KiB aligned address
 *      Bits 11-9: Available
 *      Bits 9-0: Flags
 *          G - Ignored
 *          S - Page Size (0 for 4KiB)
 *          0 - Must be 0 always
 *          A - Accessed
 *          D - Cache Disable
 *          W - Write Through
 *          U - User/Supervisor (1 or 0)
 *          R - RW/R (1 or 0)
 *          P - Present (if page is in physical memory)
 *  This means that the PD will ocupy 1024 * 4 = 4096 bytes = 4KiB.
 * Each of the Page Tables is also an array of 1024 entries each containing 4 bytes. Each PT will occupy
 * 1024 entries * 4 bytes = 4KiB. However, each PT manages 1024 pages, each of which are 4KiB in size.
 * Therefore, each PT occupies 4KiB and manages 4MiB
 *
 *  Total manageable memory = 1024 entries in the PD * 1024 entries in the PT * 4KiB (Page Size) = 4GiB.
 */
#include <stdint.h>
#include <stdio.h>
#include <physmem.h>
#include <phys.h>
#include <stddef.h>


extern void write_cr0(uint32_t value);
extern void write_cr3(uint32_t value);
extern uint32_t read_cr0(void);

uint32_t *page_directory = NULL;
uint32_t *page_table = NULL;

uint32_t get_pagedirectory_address(void)
{
    return (uint32_t)page_directory;
}

uint32_t *get_pagedir_address(void)
{
    uint32_t rem = 0;
    uint8_t *entry_count = (uint8_t*)ENTRY_COUNT_ADDR;
    mem_entry_t *mem_it = (mem_entry_t*)ENTRIES_PTR;

    if (!entry_count || *entry_count == 0)
    {
        printf("Invalid entry count pointer!");
    }
    else
    {
        for (int i = 0; i < *entry_count; i++)
        {
            if (!mem_it)
            {
                printf("Error, null pointer!");
                break;
            }

            if (MEM_TYPE_FREE == mem_it->type)
            {
                if ((mem_it->base_lo >= REAL_MODE_BOUNDARY) || (mem_it->base_hi != 0))
                {
                    printf("Setting page directory to 0x%x%x\n", mem_it->base_hi, mem_it->base_lo);
                    printf("Checking if memory is 4KB aligned...\n");
                    rem = mem_it->base_lo % PAGE_ALIGN;
                    if (rem != 0)
                    {
                        /* We must align by adding to the address - TODO take uint32_t OF into account */
                        if ((0xFFFFFFFF - (mem_it->base_lo)) < (PAGE_ALIGN - rem))
                        {
                            printf("Cannot align memory to 4KiB\n");
                        }
                        else
                        {
                            printf("Performing alignment. New address: 0x%x%x\n", mem_it->base_hi, mem_it->base_lo);
                            mem_it->base_lo += (PAGE_ALIGN - rem);
                        }
                    }
                    else
                    {
                        printf("Memory is already 4KiB aligned\n");
                    }

                    return (uint32_t*) mem_it->base_lo;
                }
            }
            mem_it += 1;
        }
    }

    return NULL;
}



void physmem_init(void)
{
    uint32_t address = 0;

    /* Get the first 4KiB aligned address which is free */
    page_directory = get_pagedir_address();

    /* Place PD address into CR3 for the processor to use it after paging is enabled */
    write_cr3((uint32_t)page_directory);

    /* We know that the PD occupies 4KiB (1024 entries of 4 bytes), and we will be placing
    * the PTs right after the PD. This means that the address of the first PT will be PD + 4096.
    */
    page_table = (uint32_t*)((uint32_t)page_directory + 4096);

    /* The PD occupies 4096 bytes.
     * The PTs (1024 PTs) each occupy 4096 bytes => PTs occupy 4MiB
     * This means that the first mappable address will be at: PD + 4KiB + 4MiB.
     * Conveniently, this is also 4KiB aligned since the PD is 4KiB aligned, remember ?
     */
    address = 0;

    /* PD set up. Each entry in the PD must contain the starting address of a PT */
    for (int i = 0; i < PD_ENTRY_COUNT; i++)
    {
        /* Set up the PD entry */
        page_directory[i] = (uint32_t) page_table;
        page_directory[i] |= 2; /* supervisor, read/write, not present */

        /* Set up the corresponding PT. Similar to the PD,
         * each PT must contain the starting address of a page
         */
        for(int j = 0; j < PT_ENTRY_COUNT; j++)
        {
            page_table[j] = (uint32_t) address;
            page_table[j] |= 3; /* supervisor, read/write, present */

            address += (PAGE_SIZE);
        }
        
        /* page_table is a uint32_t pointer, so if PAGE_SIZE was simply added
         * to it, then it would be increased by PAGE_SIZE * sizeof(uint32).
         */
        page_table = (uint32_t*)((uint32_t)page_table + PAGE_SIZE);
    }

    page_directory[0] |= 1; /* enable present bit on first page table */

    /* Tell the CPU to enable paging */
    uint32_t cr0 = read_cr0();

    cr0 |= (1 << PAGING_BIT);

    write_cr0(cr0);
}