#include "sys.h"

void *memset(void *dest, int c, size_t size)
{
     char *d = dest;
     size_t i;

     for (i = 0; i < size; i++) {
         d[i] = c;
     }
     return d;
}

void *memcpy(void *dest, const void *src, size_t size)
{
    size_t i;
    const char *s = src;
    char *d = dest;

    for (i = 0; i < size; i++) {
        d[i] = s[i];
    }
    return dest;
}

int memcmp(const uint8_t *s, const uint8_t *t, size_t size) 
{
    int i;

    for (i = 0; i < size; i++, s++, t++) {
        if (*s < *t) {
           return -1;
        } else if (*s > *t) {
           return 1;
        }
    }
    return 0;
}

