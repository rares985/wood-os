#include <virtmem.h>

static pt_entry_t *virtmem_ptable_lookup(page_table_t *table, virtaddr_t addr)
{
    if (NULL != table)
    {
        return &table->m_entries[PT_INDEX(addr)];
    }
    return NULL;
}

static pd_entry_t *virtmem_pdirectory_lookup(page_directory_t *dir, virtaddr_t addr)
{
    if (NULL != table)
    {
        return &table->m_entries[PD_INDEX(addr)];
    }
    return NULL;
}

bool virtmem_alloc_page(pt_entry_t *entry)
{
    /* Allocate a physical frame */
    void *frame_ptr = physmem_alloc_block();
    if (NULL == frame_ptr)
    {
        return false;
    }

    /* Map the physical frame to the page we are creating */
    pte_set_frame(entry, (physaddr_t)frame_ptr);

    /* Frame is present now in physical memory */
    pte_add_attrib(entry, PTE_PRESENT);

    return true;
}


void virtmem_free_page(pt_entry_t *entry)
{
    void *frame_ptr = (void*)pte_get_pfn(*entry);

    /* Mark page as not allocated */
    if (NULL != frame_ptr)
    {
        physmem_free_block(frame_ptr);
    }

    /* Page no longer present in physical memory */
    pte_del_attrib(entry, PTE_PRESENT);
}