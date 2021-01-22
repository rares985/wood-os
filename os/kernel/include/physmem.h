#ifndef  __PHYSMEM__H_
#define  __PHYSMEM__H_

#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef uint32_t physaddr_t;

void        physalloc_init(void);

void        *physmem_alloc_block(void);
void        physmem_free_block(void *page);

void        physmem_enable_paging(bool enable);
bool        physmem_is_paging_enabled(void);

void        physmem_set_PDBR(physaddr_t addr);
physaddr_t  physmem_get_PDBR(void);


#endif /* __PHYSMEM__H_ */