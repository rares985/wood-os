#include <stdint.h>
#include <stdio.h>
#include <physmem.h>
#include <phys.h>
#include <stddef.h>

#define MAX_PAGE_COUNT (1024 * 1024)
#define BITMAP_MAX_SZ_BYTES (MAX_PAGE_COUNT / 8)

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
void physalloc_init(void)
{
    uint32_t available_memory = 0;

    /* Bitmap will start at real mode boundary */
    bitmap = (uint8_t*) REAL_MODE_BOUNDARY;

    /* Compute the actual bitmap size */
    available_memory = get_available_mem();

    /* Free memory is in bytes, and we need to find out how many pages we have to manage */
    bitmap_size = (available_memory / 1024) / PAGE_SIZE;

    /* For each page, we are using a bit, so we divide once again by 8 to find size in bytes */
    bitmap_size /= 8;

    /* Mark all pages as "not allocated" */
    for(uint32_t i = 0; i < bitmap_size; i++)
    {
        bitmap[i] = 0x00;
    }

    first_allocable_page_address = (uint8_t*)((uint32_t) bitmap + BITMAP_MAX_SZ_BYTES);
}

void *allocate_page(void)
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
        page = (void*) first_allocable_page_address + (index * PAGE_SIZE);
    }

    return page;
}

void free_page(void *page)
{
    uint32_t page_index = ((uint32_t)page - (uint32_t)first_allocable_page_address)/ PAGE_SIZE;

    if (page_index > bitmap_size * 8)
    {
        printf("Invalid page index: %d (Expected <= %d)!\n", page_index, bitmap_size * 8);
    }

    mmap_set_free(page_index);
}
