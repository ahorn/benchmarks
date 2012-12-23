#include "cpu.h"
#include "sys.h"

static uintptr_t base_addr;

static inline void *physical_addr(hwaddr addr)
{
    return (void *) (base_addr | (uintptr_t) addr);
}

void cpu_physical_memory_init(uintptr_t base)
{
   base_addr = base & ~0xffffffffLL;
}

void cpu_physical_memory_write(hwaddr addr, const void *buf, size_t size)
{
    memcpy(physical_addr(addr), buf, size);
}

void cpu_physical_memory_read(hwaddr addr, void *buf, size_t size)
{
    memcpy(buf, physical_addr(addr), size);
}

