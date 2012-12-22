/*
 * Definitions to help bridge the gap between the Linux driver and
 * the QEMU standalone hardware model of the OpenCores Ethernet MAC.
 */
#ifndef ETHOC_COMBAT
#define ETHOC_COMBAT

#include "ethoc/hw.h"

/**
 * Address type for OpenCores Ethernet MAC registers or buffer descriptors
 *
 * The original definition can be found in the file 'include/linux/types.h'.
 */
typedef hwaddr loff_t;

/**
 * Originally this is a macro to force function inlining
 *
 * Assume inlining in the OpenCores Ethernet MAC driver changes neither the
 * caller's nor callee's computation.
*/
#ifndef __always_inline
#define __always_inline inline
#endif

#define unlikely

#endif
