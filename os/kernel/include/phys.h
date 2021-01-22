#ifndef PHYS_H_
#define PHYS_H_

#include <stdint.h>

#define REAL_MODE_BOUNDARY  (0x00100000)

/* where the entry count and entry pointers will be stored by the BIOS e820 function */
#define ENTRY_COUNT_ADDR    (0x4000)
#define ENTRIES_PTR         (ENTRY_COUNT_ADDR+4)


#define PAGING_BIT          (31)



typedef enum mem_type_e {
    MEM_TYPE_INVALID = 0,
    MEM_TYPE_FREE = 1,
    MEM_TYPE_RESERVED = 2,
    MEM_TYPE_ACPI_RECLAIMABLE = 3,
    MEM_TYPE_ACPI_NON_VOLATILE = 4,
    MEM_TYPE_BAD = 5,
    MEM_TYPE_MAX_NO
} mem_type_e;


typedef struct mem_entry_s {
    uint32_t base_lo;
    uint32_t base_hi;
    uint32_t length_lo;
    uint32_t length_hi;
    uint32_t type;
    uint32_t acpi_attr;
} mem_entry_t;


uint32_t get_available_mem(void);


#endif /* PHYS_H_ */