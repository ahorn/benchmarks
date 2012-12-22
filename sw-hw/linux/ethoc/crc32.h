#ifndef _LINUX_CRC32_H
#define _LINUX_CRC32_H

#include "bitrev.h"

/* ... */

static inline u32  crc32_le(u32 crc, unsigned char const *p, size_t len)
{
	/* ... */
}

/*
 * Helpers for hash table generation of ethernet nics:
 *
 * Ethernet sends the least significant bit of a byte first, thus crc32_le
 * is used. The output of crc32_le is bit reversed [most significant bit
 * is in bit nr 0], thus it must be reversed before use. Except for
 * nics that bit swap the result internally...
 */
#define ether_crc(length, data)    bitrev32(crc32_le(~0, data, length))

#endif /* _LINUX_CRC32_H */
