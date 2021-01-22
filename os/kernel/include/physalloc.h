#ifndef PHYSALLOC_H_
#define PHYSALLOC_H_

#include <stdint.h>
#include <stdio.h>
#include <physmem.h>
#include <stddef.h>


void physalloc_init(void);
void *allocate_page(void);
void free_page(void *page);


#endif /* PHYSALLOC_H_ */