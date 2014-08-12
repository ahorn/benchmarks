/*
 * Linux-specific synonymous for C99-standard types
 */
#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

/**
 * Linux-specific bit-precise primitive data types
 *
 * According to the Kernel CodingStyle documentation, the Linux-specific
 * 'u8/u16/u32/u64' types are identical to standard types. Note that the
 * file 'include/asm-generic/int-ll64.h' defines u32 as an unsigned int.
 * Instead, we heed the LLD3 authors' advice (see p. 290) and use the
 * C99-standard types. In the future, we may reconsider this.
 *
 * @see_also: http://www.kernel.org/doc/Documentation/CodingStyle
 * @see_also: http://lwn.net/images/pdf/LDD3/ch11.pdf
 */
typedef uint8_t u8;
typedef int8_t s8;
typedef uint8_t __u8;
typedef uint16_t u16;
typedef uint16_t __u16;
typedef uint32_t u32;
typedef uint32_t __u32;
typedef uint64_t u64;
typedef uint64_t __u64;

typedef uintptr_t phys_addr_t;
typedef phys_addr_t resource_size_t;

#endif /* TYPES_H */
