#include <pte.h>


void pte_add_attrib(pt_entry_t *entry, uint32_t attrib)
{
    *entry |= attrib;
}

void pte_del_attrib(pt_entry_t *entry, uint32_t attrib)
{
    (*entry) &= ~(attrib);
}

void pte_set_frame(pt_entry_t *entry, physaddr_t addr)
{
    *entry = (*entry & ~(PTE_FRAME)) | addr;

}

bool pte_is_present (pt_entry_t entry)
{
    return entry & PTE_PRESENT;
}

bool pte_is_writeable(pt_entry_t entry)
{
    return entry & PTE_WRITABLE;
}

uint32_t pte_get_pfn(pt_entry_t entry)
{
    return entry & PTE_FRAME;
}