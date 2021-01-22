#include <phys.h>
#include <stdio.h>

uint32_t get_available_mem(void)
{
    uint8_t *entry_count = (uint8_t*)ENTRY_COUNT_ADDR;
    mem_entry_t *mem_it = (mem_entry_t*)ENTRIES_PTR;
    uint32_t total_available_memory = 0;

    if (!entry_count || *entry_count == 0)
    {
        printf("Invalid entry counter pointer!");
    }
    else
    {
        for(int i = 0; i < *entry_count; i++)
        {
            if (MEM_TYPE_FREE == mem_it->type)
            {
                if (mem_it->base_lo >= REAL_MODE_BOUNDARY) 
                {
                    total_available_memory += mem_it->length_lo;
                    break;
                }
            }
            mem_it += 1;
        }
    }

    return total_available_memory;
}