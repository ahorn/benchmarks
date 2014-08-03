#ifndef _CPU_H_
#define _CPU_H_

#include <stddef.h>
#include "hwaddr.h"

/**
 * cpu_physical_memory_init:
 * @base: base address
 *
 * Setup address map for DMA.
 */
void cpu_physical_memory_init(uintptr_t base);

void cpu_physical_memory_write(hwaddr addr, const void *buf, size_t size);
void cpu_physical_memory_read(hwaddr addr, void *buf, size_t size);

#endif
