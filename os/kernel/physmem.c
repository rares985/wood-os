
#include <stdint.h>
#include <stdio.h>
#include <physmem.h>
#include <stddef.h>

extern void write_cr0(uint32_t value);
extern void write_cr3(uint32_t value);
extern uint32_t read_cr0(void);

#define ENTRY_COUNT_ADDR 0x4000
#define ENTRIES_PTR (ENTRY_COUNT_ADDR+4)
#define REAL_MODE_BOUNDARY (0x00100000)
#define PAGE_ALIGN         (0x1000)
#define PAGE_SIZE          (4096)   /* 4KiB */
#define PAGING_BIT          (31)

uint32_t *page_directory = NULL;
uint32_t *page_table = NULL;

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

    /* Page directory occupies 4KiB */
    page_directory = get_pagedir_address();

    /* Page table comes after page directory */
    page_table = (page_directory + 4096);

    /* We are mapping the first 1024 * 4KiB of memory = 4MiB */
    for (int i = 0; i < 1024; i++)
    {
        /* Set the page's attributes in the page table */
        page_table[i] = address | 3;
        address += PAGE_SIZE;
    }

    /* Fill the first entry of the page directory */
    page_directory[0] = (uint32_t) page_table;
    page_directory[0] = page_directory[0] | 3;

    /* Fill the page directory */
    for(int i = 0; i < 1024; i++)
    {
        page_directory[i] = (0 | 2); 
    }

    /* Enable paging */
    write_cr3((uint32_t)page_directory);

    uint32_t cr0 = read_cr0();

    cr0 |= (1 << PAGING_BIT);

    write_cr0(cr0);
}