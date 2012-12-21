/* Copyright (C) 2008, 2009 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Under Section 7 of GPL version 3, you are granted additional
permissions described in the GCC Runtime Library Exception, version
3.1, as published by the Free Software Foundation.

You should have received a copy of the GNU General Public License and
a copy of the GCC Runtime Library Exception along with this program;
see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
<http://www.gnu.org/licenses/>.  */

/*
 * ISO C Standard:  7.18  Integer types  <stdint.h>
 */

#ifndef _GCC_STDINT_H
#define _GCC_STDINT_H

#define     INT8_MAX   0x7f
#define     INT8_MIN   (-INT8_MAX - 1)
#define     UINT8_MAX   (__CONCAT(INT8_MAX, U) * 2U + 1U)
#define     INT16_MAX   0x7fff
#define     INT16_MIN   (-INT16_MAX - 1)
#define     UINT16_MAX   (__CONCAT(INT16_MAX, U) * 2U + 1U)
#define     INT32_MAX   0x7fffffffL
#define     INT32_MIN   (-INT32_MAX - 1L)
#define     UINT32_MAX   (__CONCAT(INT32_MAX, U) * 2UL + 1UL)
#define     INT64_MAX   0x7fffffffffffffffLL
#define     INT64_MIN   (-INT64_MAX - 1LL)
#define     UINT64_MAX   (__CONCAT(INT64_MAX, U) * 2ULL + 1ULL)

#endif /* _GCC_STDINT_H */
