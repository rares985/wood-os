#include <physmem.h>
#include <phys.h>

/* Functions written in ASM */
extern void write_cr0(uint32_t value);
extern void write_cr3(uint32_t value);

extern uint32_t read_cr0(void);
extern uint32_t read_cr3(void);

#define MAX_PAGE_COUNT      (1024 * 1024)
#define BITMAP_MAX_SZ_BYTES (MAX_PAGE_COUNT / 8)
#define BLOCK_SIZE          (4096)

uint8_t *bitmap = NULL;
uint32_t  bitmap_size = 0;
uint8_t *first_allocable_page_address = NULL;


static int mmap_find_free(void)
{
    int index  = -1;

    /* Find free (zero) bit */
    for (uint32_t i = 0; i < bitmap_size; i++)
    {
        if (bitmap[i] != 0xFF)
        {
            for (int j = 0; j < 8; j++)
            {
                if ((bitmap[i] & (1 << j)) == 0)
                {
                   /* Bit is clear */
                    index = i * 8 + j + 1;
                    break;
                }
            }
            break;
        }
    }

    return index;
}

static void mmap_set_used(uint32_t index)
{
    uint32_t byte_index;
    uint32_t bit_index;

    byte_index = (index - 1) / 8;
    bit_index = (index - 1) % 8;

    bitmap[byte_index] |= (1 << bit_index);
}

static void mmap_set_free(uint32_t index)
{
    uint32_t byte_index;
    uint32_t bit_index;

    byte_index = (index - 1) / 8;
    bit_index = (index - 1) % 8;

    bitmap[byte_index] &= ~(1 << bit_index);
}

/* For physical memory allocation, a bitmap model will be used. Since the 32-bit address space spans
 * 4GB, there is a maximum of 1M pages to manage. In the bitmap, 1 bit is used for each page, so the maximum
 * possible size of the bitmap is (1M / 8) bytes = 128KB. We will reserve this space right after the real mode 
 * 1MB address boundary, which means that our bitmap will start at address 0x00100000 and span 128KB, up to a maximum
 * address of 0x11FFFF.
 */
void physmem_init(void)
{
    uint32_t available_memory = 0;

    /* Bitmap will start at real mode boundary */
    bitmap = (uint8_t*) REAL_MODE_BOUNDARY;

    /* Compute the actual bitmap size */
    available_memory = get_available_mem();

    /* Free memory is in bytes, and we need to find out how many pages we have to manage */
    bitmap_size = (available_memory / 1024) / BLOCK_SIZE;

    /* For each page, we are using a bit, so we divide once again by 8 to find size in bytes */
    bitmap_size /= 8;

    /* Mark all pages as "not allocated" */
    for(uint32_t i = 0; i < bitmap_size; i++)
    {
        bitmap[i] = 0x00;
    }

    first_allocable_page_address = (uint8_t*)((uint32_t) bitmap + BITMAP_MAX_SZ_BYTES);
}

void *physmem_alloc_block(void)
{
    /* Find first clear bit */
    int  index = mmap_find_free();
    void *page = NULL;

    if (-1 == index)
    {
        printf("No free physical memory left!");
    }
    else
    {
        mmap_set_used(index);
        page = (void*) first_allocable_page_address + (index * BLOCK_SIZE);
    }

    return page;
}

void physmem_free_block(void *page)
{
    uint32_t page_index = ((uint32_t)page - (uint32_t)first_allocable_page_address)/ BLOCK_SIZE;

    if (page_index > bitmap_size * 8)
    {
        printf("Invalid page index: %d (Expected <= %d)!\n", page_index, bitmap_size * 8);
    }

    mmap_set_free(page_index);
}

void physmem_enable_paging(bool enable)
{
    uint32_t cr0;

    cr0 = read_cr0();

    if (enable)
    {
        cr0 |= (1 << PAGING_BIT);
    }
    else
    {
        cr0 &= ~(1 << PAGING_BIT);
    }
    write_cr0(cr0);
}

bool physmem_is_paging_enabled(void)
{
    return ((read_cr0() & (1 << PAGING_BIT)) != 0);

}

void physmem_set_PDBR(physaddr_t addr)
{
    write_cr3((uint32_t)addr);
}

physaddr_t physmem_get_PDBR(void)
{
    return (physaddr_t)read_cr3();
}
