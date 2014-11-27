/** @brief Unit-test for DRD's vector clock implementation. */


#include <assert.h>

#ifdef _CONCRETE_EXECUTION_
#include <string.h> // memcpy
#endif

#include <stdlib.h> // malloc, free
#include "drd_vc.h" // DRD_(vc_reserve) is static


/* Replacements for Valgrind core functionality. */

void* VG_(malloc)(const HChar* cc, SizeT nbytes)
{ return malloc(nbytes); }
void* VG_(realloc)(const HChar* cc, void* p, SizeT size)
{ return realloc(p, size); }
void  VG_(free)(void* p)
{ return free(p); }

#ifndef _CONCRETE_EXECUTION_
void *memcpy(void *dest, const void *src, SizeT size)
{
    SizeT i;
    const char *s = src;
    char *d = dest;

    for (i = 0; i < size; i++)
    {
        d[i] = s[i];
    }
    return dest;
}
#endif

void* VG_(memcpy)(void *d, const void *s, SizeT sz)
{ return memcpy(d, s, sz); }

/* Actual unit test */

#ifdef _TEST_1_
static void vc_unittest(void)
{
  VectorClock vc1;
  VCElem vc1elem[] = { { 3, 7 }, { 5, 8 }, };
  VectorClock vc2;
  VCElem vc2elem[] = { { 1, 4 }, { 3, 9 }, };
  VectorClock vc3;
  VCElem vc4elem[] = { { 1, 3 }, { 2, 1 }, };
  VectorClock vc4;
  VCElem vc5elem[] = { { 1, 4 }, };
  VectorClock vc5;

  DRD_(vc_init)(&vc1, vc1elem, sizeof(vc1elem)/sizeof(vc1elem[0]));
  DRD_(vc_init)(&vc2, vc2elem, sizeof(vc2elem)/sizeof(vc2elem[0]));
  DRD_(vc_init)(&vc3, 0, 0);
  DRD_(vc_init)(&vc4, vc4elem, sizeof(vc4elem)/sizeof(vc4elem[0]));
  DRD_(vc_init)(&vc5, vc5elem, sizeof(vc5elem)/sizeof(vc5elem[0]));

  /*

   Assertions are inferred from the file "drd/tests/unit_vc.stderr.exp":

     vc1: [ 3: 7, 5: 8 ]
     vc2: [ 1: 4, 3: 9 ]
     vc_lte(vc1, vc2) = 0, vc_lte(vc1, vc3) = 1, vc_lte(vc2, vc3) = 1
     vc_lte([ 1: 3, 2: 1 ], [ 1: 4 ]) = 0 sw 0

  */

  DRD_(vc_combine)(&vc3, &vc1);

  assert(vc3.vc[0].threadid == 3);
  assert(vc3.vc[0].count == 7);

  assert(vc3.vc[1].threadid == 5);
  assert(vc3.vc[1].count == 8);

  DRD_(vc_combine)(&vc3, &vc2);

  assert(vc3.vc[0].threadid == 1);
  assert(vc3.vc[0].count == 4);

  assert(vc3.vc[1].threadid == 3);
  assert(vc3.vc[1].count == 9);

  assert(vc3.vc[2].threadid == 5);
  assert(vc3.vc[2].count == 8);

  Bool a = DRD_(vc_lte)(&vc1, &vc2);
  assert(a == 0);

  Bool b = DRD_(vc_lte)(&vc1, &vc3);
  assert(b == 1);

  Bool c = DRD_(vc_lte)(&vc2, &vc3);
  assert(c == 1);

  Bool d = DRD_(vc_lte)(&vc4, &vc5);
  assert(d == 0);

  Bool e = DRD_(vc_lte)(&vc5, &vc4);

#ifdef _SANITY_CHECK_
  // we expect this assertion to fail
  assert(e == 1);
#else
  // we expect this assertion to pass
  assert(e == 0);
#endif

#ifdef _CONCRETE_EXECUTION_
  int i;
  for (i = 0; i < 64; i++)
    DRD_(vc_reserve)(&vc1, i);
  for (i = 64; i > 0; i--)
    DRD_(vc_reserve)(&vc1, i);

  DRD_(vc_cleanup)(&vc1);
  DRD_(vc_cleanup)(&vc2);
  DRD_(vc_cleanup)(&vc3);
#endif
}
#endif

#ifdef _TEST_2_
static void vc_reflexivity(void)
{
  VectorClock vc1;
  VCElem vc1elem[] = { { 3, 7 }, { 5, 8 }, };
  VectorClock vc2;
  VCElem vc2elem[] = { { 1, 4 }, { 3, 9 }, };
  VectorClock vc3;
  VCElem vc4elem[] = { { 1, 3 }, { 2, 1 }, };
  VectorClock vc4;
  VCElem vc5elem[] = { { 1, 4 }, };
  VectorClock vc5;

  DRD_(vc_init)(&vc1, vc1elem, sizeof(vc1elem)/sizeof(vc1elem[0]));
  DRD_(vc_init)(&vc2, vc2elem, sizeof(vc2elem)/sizeof(vc2elem[0]));
  DRD_(vc_init)(&vc3, 0, 0);
  DRD_(vc_init)(&vc4, vc4elem, sizeof(vc4elem)/sizeof(vc4elem[0]));
  DRD_(vc_init)(&vc5, vc5elem, sizeof(vc5elem)/sizeof(vc5elem[0]));

  DRD_(vc_combine)(&vc3, &vc1);

  assert(vc3.vc[0].threadid == 3);
  assert(vc3.vc[0].count == 7);

  assert(vc3.vc[1].threadid == 5);
  assert(vc3.vc[1].count == 8);

  assert(DRD_(vc_lte)(&vc1, &vc1) == 1);
  assert(DRD_(vc_lte)(&vc1, &vc3) == 1);
  assert(DRD_(vc_lte)(&vc2, &vc2) == 1);
  assert(DRD_(vc_lte)(&vc3, &vc3) == 1);
  assert(DRD_(vc_lte)(&vc4, &vc4) == 1);
  assert(DRD_(vc_lte)(&vc5, &vc5) == 1);
}
#endif

// Explicit loop unrolling
#define VC_PRE(vcelem, size)                                               \
  if (1 < size) __CPROVER_assume(vcelem[0].threadid < vcelem[1].threadid); \
  if (2 < size) __CPROVER_assume(vcelem[1].threadid < vcelem[2].threadid); \
  if (3 < size) __CPROVER_assume(vcelem[2].threadid < vcelem[3].threadid); \
  if (4 < size) __CPROVER_assume(vcelem[3].threadid < vcelem[4].threadid); \
  if (5 < size) __CPROVER_assume(vcelem[4].threadid < vcelem[5].threadid); \
  if (6 < size) __CPROVER_assume(vcelem[5].threadid < vcelem[6].threadid); \
  if (7 < size) __CPROVER_assume(vcelem[6].threadid < vcelem[7].threadid); \

#ifdef _CBMC_VC_1_
static void vc_reflexivity_cbmc(void)
{
  unsigned size;
  __CPROVER_assume(size <= VC_PREALLOCATED);

  VectorClock vc1;
  VCElem vc1elem[size];

  VC_PRE(vc1elem, size)

  DRD_(vc_init)(&vc1, vc1elem, size);
  assert(DRD_(vc_lte)(&vc1, &vc1) == 1);
}
#endif

#ifdef _CBMC_VC_2_
static void vc_transitivity_cbmc(void)
{
  unsigned size1, size2, size3;
  __CPROVER_assume(size1 <= VC_PREALLOCATED);
  __CPROVER_assume(size2 <= VC_PREALLOCATED);
  __CPROVER_assume(size3 <= VC_PREALLOCATED);

  VectorClock vc1;
  VCElem vc1elem[size1];

  VectorClock vc2;
  VCElem vc2elem[size2];

  VectorClock vc3;
  VCElem vc3elem[size3];

  VC_PRE(vc1elem, size1)
  VC_PRE(vc2elem, size2)
  VC_PRE(vc3elem, size3)

  DRD_(vc_init)(&vc1, vc1elem, size1);
  DRD_(vc_init)(&vc2, vc2elem, size2);
  DRD_(vc_init)(&vc3, vc3elem, size3);

  __CPROVER_assume(DRD_(vc_lte)(&vc1, &vc2) == 1);
  __CPROVER_assume(DRD_(vc_lte)(&vc2, &vc3) == 1);

  assert(DRD_(vc_lte)(&vc1, &vc3) == 1);
}
#endif

#ifdef _CBMC_VC_3_
static void vc_antisymmetry_cbmc(void)
{
  unsigned size1, size2, size3;
  __CPROVER_assume(size1 <= VC_PREALLOCATED);
  __CPROVER_assume(size2 <= VC_PREALLOCATED);

  VectorClock vc1;
  VCElem vc1elem[size1];

  VectorClock vc2;
  VCElem vc2elem[size2];

  VC_PRE(vc1elem, size1)
  VC_PRE(vc2elem, size2)

  DRD_(vc_init)(&vc1, vc1elem, size1);
  DRD_(vc_init)(&vc2, vc2elem, size2);

  __CPROVER_assume(DRD_(vc_lte)(&vc1, &vc2) == 1);
  __CPROVER_assume(DRD_(vc_lte)(&vc2, &vc1) == 1);

  assert(size1 == size2);
  unsigned size = size1;

  if (0 < size) assert(vc1elem[0].threadid == vc2elem[0].threadid);
  if (0 < size) assert(vc1elem[0].count == vc2elem[0].count);

  if (1 < size) assert(vc1elem[1].threadid == vc2elem[1].threadid);
  if (1 < size) assert(vc1elem[1].count == vc2elem[1].count);

  if (2 < size) assert(vc1elem[2].threadid == vc2elem[2].threadid);
  if (2 < size) assert(vc1elem[2].count == vc2elem[2].count);

  if (3 < size) assert(vc1elem[3].threadid == vc2elem[3].threadid);
  if (3 < size) assert(vc1elem[3].count == vc2elem[3].count);

  if (4 < size) assert(vc1elem[4].threadid == vc2elem[4].threadid);
  if (4 < size) assert(vc1elem[4].count == vc2elem[4].count);

  if (5 < size) assert(vc1elem[5].threadid == vc2elem[5].threadid);
  if (5 < size) assert(vc1elem[5].count == vc2elem[5].count);

  if (6 < size) assert(vc1elem[6].threadid == vc2elem[6].threadid);
  if (6 < size) assert(vc1elem[6].count == vc2elem[6].count);

  if (7 < size) assert(vc1elem[7].threadid == vc2elem[7].threadid);
  if (7 < size) assert(vc1elem[7].count == vc2elem[7].count);
}
#endif

#ifdef _CBMC_VC_4_
static void vc_combine_upper_bound_cbmc(void)
{
  unsigned size1, size2;
  __CPROVER_assume(size1 <= VC_PREALLOCATED/2);
  __CPROVER_assume(size2 <= VC_PREALLOCATED/2);

  VectorClock vc1;
  VCElem vc1elem[size1];

  VectorClock vc2;
  VCElem vc2elem[size2];

  VectorClock vc1_copy;
  VCElem vc1_copyelem[size1];

  VC_PRE(vc1elem, size1)
  VC_PRE(vc2elem, size2)

  DRD_(vc_init)(&vc1, vc1elem, size1);
  DRD_(vc_init)(&vc2, vc2elem, size2);

  if (0 < size1) __CPROVER_assume(vc1elem[0].threadid == vc1_copyelem[0].threadid);
  if (0 < size1) __CPROVER_assume(vc1elem[0].count == vc1_copyelem[0].count);

  if (1 < size1) __CPROVER_assume(vc1elem[1].threadid == vc1_copyelem[1].threadid);
  if (1 < size1) __CPROVER_assume(vc1elem[1].count == vc1_copyelem[1].count);

  if (2 < size1) __CPROVER_assume(vc1elem[2].threadid == vc1_copyelem[2].threadid);
  if (2 < size1) __CPROVER_assume(vc1elem[2].count == vc1_copyelem[2].count);

  if (3 < size1) __CPROVER_assume(vc1elem[3].threadid == vc1_copyelem[3].threadid);
  if (3 < size1) __CPROVER_assume(vc1elem[3].count == vc1_copyelem[3].count);

  if (4 < size1) __CPROVER_assume(vc1elem[4].threadid == vc1_copyelem[4].threadid);
  if (4 < size1) __CPROVER_assume(vc1elem[4].count == vc1_copyelem[4].count);

  if (5 < size1) __CPROVER_assume(vc1elem[5].threadid == vc1_copyelem[5].threadid);
  if (5 < size1) __CPROVER_assume(vc1elem[5].count == vc1_copyelem[5].count);

  if (6 < size1) __CPROVER_assume(vc1elem[6].threadid == vc1_copyelem[6].threadid);
  if (6 < size1) __CPROVER_assume(vc1elem[6].count == vc1_copyelem[6].count);

  if (7 < size1) __CPROVER_assume(vc1elem[7].threadid == vc1_copyelem[7].threadid);
  if (7 < size1) __CPROVER_assume(vc1elem[7].count == vc1_copyelem[7].count);

  DRD_(vc_init)(&vc1_copy, vc1_copyelem, size1);

  assert(vc1.capacity == vc1_copy.capacity);
  assert(vc1.size == vc1_copy.size);

  // make vc1_copy an upper bound of vc1 and vc2
  DRD_(vc_combine)(&vc1_copy, &vc2);

  assert(DRD_(vc_lte)(&vc1, &vc1_copy) == 1);
  assert(DRD_(vc_lte)(&vc2, &vc1_copy) == 1);
}
#endif

#ifdef _CBMC_VC_5_
static void vc_combine_least_upper_bound_cbmc(void)
{
  unsigned size1, size2, size3;
  __CPROVER_assume(size1 <= VC_PREALLOCATED/2);
  __CPROVER_assume(size2 <= VC_PREALLOCATED/2);
  __CPROVER_assume(size3 <= VC_PREALLOCATED);

  VectorClock vc1;
  VCElem vc1elem[size1];

  VectorClock vc2;
  VCElem vc2elem[size2];

  VectorClock vc3;
  VCElem vc3elem[size3];

  VC_PRE(vc1elem, size1)
  VC_PRE(vc2elem, size2)
  VC_PRE(vc3elem, size3)

  DRD_(vc_init)(&vc1, vc1elem, size1);
  DRD_(vc_init)(&vc2, vc2elem, size2);
  DRD_(vc_init)(&vc3, vc3elem, size3);

  __CPROVER_assume(DRD_(vc_lte)(&vc1, &vc3) == 1);
  __CPROVER_assume(DRD_(vc_lte)(&vc2, &vc3) == 1);

  // make vc1' the least upper bound of vc1 and vc2
  DRD_(vc_combine)(&vc1, &vc2);

  assert(DRD_(vc_lte)(&vc1, &vc3) == 1);
}
#endif

int main(int argc, char** argv)
{
#ifdef _TEST_1_
  vc_unittest();
#endif

#ifdef _TEST_2_
  vc_reflexivity();
#endif

#ifdef _CBMC_VC_1_
  vc_reflexivity_cbmc();
#endif

#ifdef _CBMC_VC_2_
  vc_transitivity_cbmc();
#endif

#ifdef _CBMC_VC_3_
  vc_antisymmetry_cbmc();
#endif

// ~ 3 hours
#ifdef _CBMC_VC_4_
  vc_combine_upper_bound_cbmc();
#endif

// ~ 7 hours
#ifdef _CBMC_VC_5_
  vc_combine_least_upper_bound_cbmc();
#endif

  return 0;
}
