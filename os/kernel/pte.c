#include <pte.h>


void pte_add_attrib(pt_entry *entry, uint32_t attrib)
{
    *entry |= attrib;
}

void pte_del_attrib(pt_entry *entry, uint32_t attrib)
{
    (*entry) &= ~(attrib);
}

void pte_set_frame(pt_entry *entry, uint32_t physaddr)
{
    *entry = (*entry & ~(PTE_FRAME)) | physaddr;

}

bool pte_is_present (pt_entry entry)
{
    return entry & PTE_PRESENT;
}

bool pte_is_writeable(pt_entry entry)
{
    return entry & PTE_WRITABLE;
}

uint32_t pt_entry_pfn(pt_entry entry);
{
    return entry & PTE_FRAME;
}