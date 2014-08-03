#ifndef SYS_H
#define SYS_H

#include <stddef.h>
#include <stdint.h>

void *memset(void *dest, int c, size_t size);
void *memcpy(void *dest, const void* src, size_t size);
int memcmp_unint8(const uint8_t *s, const uint8_t *t, size_t size);

#endif
