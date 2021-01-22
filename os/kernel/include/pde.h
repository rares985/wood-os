#ifndef _PDE_H_
#define _PDE_H_

#include <stdint.h>
#include <stdbool.h>
#include <physmem.h>

typedef enum page_pde_flags_e {
	PDE_PRESENT			=	1,		    /* 0000 0000 0000 0000 0000 0000 0000 001 */
	PDE_WRITABLE		=	2,		    /* 0000 0000 0000 0000 0000 0000 0000 010 */
	PDE_USER			=	4,		    /* 0000 0000 0000 0000 0000 0000 0000 100 */
	PDE_PWT			    =	8,		    /* 0000 0000 0000 0000 0000 0000 0001 000 */
	PDE_PCD			    =	0x10,		/* 0000 0000 0000 0000 0000 0000 0010 000 */
	PDE_ACCESSED		=	0x20,		/* 0000 0000 0000 0000 0000 0000 0100 000 */
	PDE_DIRTY			=	0x40,		/* 0000 0000 0000 0000 0000 0000 1000 000 */
	PDE_4MB			    =	0x80,		/* 0000 0000 0000 0000 0000 0001 0000 000 */
	PDE_CPU_GLOBAL		=	0x100,		/* 0000 0000 0000 0000 0000 0010 0000 000 */
	PDE_LV4_GLOBAL		=	0x200,		/* 0000 0000 0000 0000 0000 0100 0000 000 */
   	PDE_FRAME			=	0x7FFFF000 	/* 1111 1111 1111 1111 1110 0000 0000 000 */
} page_pde_flags_t;

typedef uint32_t pd_entry_t;

extern void		pd_entry_add_attrib (pd_entry_t* e, uint32_t attrib);
extern void		pd_entry_del_attrib (pd_entry_t* e, uint32_t attrib);
extern void		pd_entry_set_frame (pd_entry_t*, physaddr_t addr);
extern bool		pd_entry_is_present (pd_entry_t e);
extern bool		pd_entry_is_user (pd_entry_t);
extern bool		pd_entry_is_4mb (pd_entry_t);
extern bool		pd_entry_is_writable (pd_entry_t e);
extern uint32_t	pd_entry_pfn (pd_entry_t e);
extern void		pd_entry_enable_global (pd_entry_t e);

#endif /* _PDE_H_ */