#include <pde.h>


void pd_entry_add_attrib (pd_entry_t *entry, uint32_t attrib)
{
    *entry |= attrib;
}

void pd_entry_del_attrib (pd_entry_t *entry, uint32_t attrib)
{
    *entry &= ~(attrib);
}

void pd_entry_set_frame (pd_entry_t *entry, physaddr_t addr)
{
    *entry = (*entry & (PDE_FRAME)) | addr;
}

bool pd_entry_is_present (pd_entry_t entry)
{
    return entry & PDE_PRESENT;
}

bool pd_entry_is_user (pd_entry_t entry)
{
    return entry & PDE_USER;
}

bool pd_entry_is_4mb (pd_entry_t entry)
{
    return entry & PDE_4MB;
}

bool pd_entry_is_writable (pd_entry_t entry)
{
    return entry & PDE_WRITABLE;
}

uint32_t pd_entry_pfn (pd_entry_t entry)
{
    return entry & PDE_FRAME;
}

void pd_entry_enable_global (pd_entry_t entry)
{
    (void)entry;
}
