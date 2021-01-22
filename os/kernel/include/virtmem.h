#ifndef _VIRTMEM_H_
#define _VIRTMEM_H_

#include <pte.h>
#include <pde.h>

typedef uint32_t virtaddr_t;

#define PAGES_PER_PTE  (1024)     /* There are 1024 pages per page table entry */
#define PTE_COUNT      (1024)     /* There are 1024 page table entries in the page directory */

/* To understand macros below, there is a need to understand how paging works.
 * In order to address the entire 4GB address space of 32-bit processor, a Page Directory (PD) and a Page Table (PT)
 * are used.
 * The PD is a structure containing 1024 entries of 4 bytes, each entry containing information about a PT entry
 * A PT entry is a structure containing 1024 entries of 4 bytes, each entry containing information about a virtual memory page (4KB)
 * 
 * Since the PD contains 1024 PT entries and each PT entry contains 1024 pages, we can deduce that using the structures we can address
 * 1024 * 1024 * 4KB = 4GB of memory.
 * 
 * In this structure, we can uniquely identify a byte via three coordinates: Page Directory Index, Page Table Index and Offset In Page.
 * Now we need a method to convert these three coordinates into  a 32-bit address. This is very convenient due to the cleverness of the structure.
 * 
 * PDI
 *  Notice that the range of the Page Directory Index is [0 - 1023], which in hex is [0 - 3FF]. In binary, 3FF uses only 10 bits so we only need 10 bits
 *  in order to represent the PDI.
 * PTI
 *  Notice that the same thing can be applied to a Page Table. Once we decided on a Page Directory, it refers to a Page Table, which in turn
 * refers 1024 Pages. Therefore the maximum PTI is also 3FF, using 10 bits
 * 
 * Offset in Page
 *  Since a page size is 4KB, this means that an offset of a byte in the page is in the range [0 - 4095], or [0 - FFF] in hex. This uses exactly 12 bits.
 * 
 * By concatenating the three previous coordinates (PDI:PTI:OIP), we arrive at a 32-bit address, the virtual address.
 * 
 * In the PT, each entry contains information about 1024 pages, which includes the physical address at which that page starts. This is very handy,
 * because we can immediately assign a physical address to a virtual address and also the same physical address can be mapped to different virtual addresses
 * in different virtual address spaces.
 * 
 * The macros below are simply bit hacks to extract various things from the virtual address 
 */
#define PD_INDEX(virtaddr)          (((virtaddr) >> 22) & 0x3FF)
#define PT_INDEX(virtaddr)          (((virtaddr) >> 12) & 0x3FF)

#define PAGE_SIZE                   (4 * 1024)
#define PTABLE_ADDR_SPACE_SIZE      (PAGES_PER_PTE * PAGE_SIZE)
#define DTABLE_ADDR_SPACE_SIZE      (PTE_COUNT * PTABLE_ADDR_SPACE_SIZE)

struct page_table_s {
    pt_entry_t m_entries[PAGES_PER_PTE];
} page_table_t;

struct page_directory_s {
    pd_entry_t m_entries[PTE_COUNT];
} page_directory_t;


#endif /* _VIRTMEM_H_ */