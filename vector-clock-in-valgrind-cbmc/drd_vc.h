/*
  This file is part of drd, a thread error detector.

  Copyright (C) 2006-2013 Bart Van Assche <bvanassche@acm.org>.

  This program is free software; you can redistribute it and/or
  modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation; either version 2 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
  02111-1307, USA.

  The GNU General Public License is contained in the file COPYING.
*/


#ifndef __DRD_VC_H
#define __DRD_VC_H

/* Always enable assertions */
#define ENABLE_DRD_CONSISTENCY_CHECKS

/*
 * DRD vector clock implementation:
 * - One counter per thread.
 * - A vector clock is implemented as multiple pairs of (thread id, counter).
 * - Pairs are stored in an array sorted by thread id.
 *
 * Semantics:
 * - Each time a thread performs an action that implies an ordering between
 *   intra-thread events, the counter of that thread is incremented.
 * - Vector clocks are compared by comparing all counters of all threads.
 * - When a thread synchronization action is performed that guarantees that
 *   new actions of the current thread are executed after the actions of the
 *   other thread, the vector clock of the synchronization object and the
 *   current thread are combined (by taking the component-wise maximum).
 * - A vector clock is incremented during actions such as
 *   pthread_create(), pthread_mutex_unlock(), sem_post(). (Actions where
 *   an inter-thread ordering "arrow" starts).
 */


#include "pub_tool_basics.h"     /* Addr, SizeT */
#include "drd_basics.h"          /* DrdThreadId */
#include "pub_tool_libcassert.h" /* tl_assert() */


#define VC_PREALLOCATED 8

#ifndef __GNUC__
#define __inline__  /* */
#endif

/** Vector clock element. */
typedef struct
{
   DrdThreadId threadid;
   UInt        count;
} VCElem;

typedef struct
{
   unsigned capacity; /**< number of elements allocated for array vc. */
   unsigned size;     /**< number of elements used of array vc. */
   VCElem*  vc;       /**< vector clock elements. */
   VCElem   preallocated[VC_PREALLOCATED];
} VectorClock;


extern void DRD_(vc_init)(VectorClock* const vc,
                   const VCElem* const vcelem,
                   const unsigned size);
extern void DRD_(vc_cleanup)(VectorClock* const vc);
extern void DRD_(vc_copy)(VectorClock* const new, const VectorClock* const rhs);
extern void DRD_(vc_assign)(VectorClock* const lhs, const VectorClock* const rhs);
extern void DRD_(vc_increment)(VectorClock* const vc, DrdThreadId const tid);
extern Bool DRD_(vc_lte)(const VectorClock* const vc1,
                  const VectorClock* const vc2);
extern Bool DRD_(vc_ordered)(const VectorClock* const vc1,
                      const VectorClock* const vc2);
extern void DRD_(vc_min)(VectorClock* const result,
                  const VectorClock* const rhs);
extern void DRD_(vc_combine)(VectorClock* const result,
                      const VectorClock* const rhs);
extern void DRD_(vc_check)(const VectorClock* const vc);
extern void DRD_(vc_reserve)(VectorClock* const vc, const unsigned new_capacity);

/*

 Removed print functions

*/

void DRD_(vc_test)(void);

#endif /* __DRD_VC_H */
