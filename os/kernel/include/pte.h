#ifndef _PTE_H_
#define _PTE_H_

#include <stdint.h>
#include <stdbool.h>
#include <physmem.h>

typedef enum page_pte_flags_e {
    PTE_PRESENT			=	1,		    /* 0000 0000 0000 0000 0000 0000 0000 001 */
	PTE_WRITABLE		=	2,		    /* 0000 0000 0000 0000 0000 0000 0000 010 */
	PTE_USER			=	4,		    /* 0000 0000 0000 0000 0000 0000 0000 100 */
	PTE_WRITETHOUGH		=	8,		    /* 0000 0000 0000 0000 0000 0000 0001 000 */
	PTE_NOT_CACHEABLE	=   0x10,		/* 0000 0000 0000 0000 0000 0000 0010 000 */
	PTE_ACCESSED		=	0x20,		/* 0000 0000 0000 0000 0000 0000 0100 000 */
	PTE_DIRTY			=	0x40,		/* 0000 0000 0000 0000 0000 0000 1000 000 */
	PTE_PAT			    =	0x80,		/* 0000 0000 0000 0000 0000 0001 0000 000 */
	PTE_CPU_GLOBAL		=	0x100,		/* 0000 0000 0000 0000 0000 0010 0000 000 */
	PTE_LV4_GLOBAL		=	0x200,		/* 0000 0000 0000 0000 0000 0100 0000 000 */
   	PTE_FRAME			=	0x7FFFF000 	/* 1111 1111 1111 1111 1110 0000 0000 000 */

} page_pte_flags_t;

typedef uint32_t pt_entry_t;


extern void     pte_add_attrib(pt_entry_t *entry, uint32_t attrib);
extern void     pte_del_attrib(pt_entry_t *entry, uint32_t attrib);
extern void     pte_set_frame(pt_entry_t *entry, physaddr_t addr);
extern bool     pte_is_present (pt_entry_t entry);
extern bool     pte_is_writeable(pt_entry_t entry);
extern uint32_t pte_get_pfn(pt_entry_t entry); 

#endif /* _PTE_H_ */