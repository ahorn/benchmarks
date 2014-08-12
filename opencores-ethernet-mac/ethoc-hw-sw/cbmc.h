/*
 * Define _CBMC_ constant macro to generate non-deterministic values.
 */
#ifndef CBMC_H
#define CBMC_H

#include "types.h"

u8 nondet_u8(u8 value);
u16 nondet_u16(u16 value);
u32 nondet_u32(u32 value);
u64 nondet_u64(u64 value);
int nondet_int(int value);
unsigned int nondet_uint(unsigned int value);
long nondet_long(long value);
unsigned long nondet_ulong(unsigned long value);

#endif
