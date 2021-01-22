#ifndef PHYSMEM_H_
#define PHYSMEM_H_

#define PAGE_ALIGN         (0x1000)
#define PAGE_SIZE          (4096)   /* 4KiB */
#define PAGING_BIT         (31)


#define PD_ENTRY_COUNT      (1024)
#define PD_ENTRY_SIZE       (4)
#define PD_SIZE             (PD_ENTRY_COUNT * PD_ENTRY_SIZE)

#define PT_ENTRY_COUNT      (1024)
#define PT_ENTRY_SIZE       (4)
#define PT_SIZE             (PT_ENTRY_SIZE * PT_ENTRY_COUNT)






void physmem_init(void);

uint32_t get_pagedirectory_address(void);

#endif /* PHYSMEM_H_ */