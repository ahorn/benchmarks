// For more explanations, see Section 2.2 (Sums and Recurrences) in
// "Concrete Mathematics", Second Edition, by Ronald L. Graham,
// Donald E. Knuth, and Oren Patashnik

#include <assert.h>

#ifdef ENABLE_KLEE
#include <klee/klee.h>
#endif

int sumR(int a, int b, int k) {
  int sum = a + b*k;
  if (k > 0)
    return sum + sumR(a, b, k-1);
  else
    return sum;
}

#ifdef ENABLE_CPROVER
int nondet_int();
#endif

// N must be even
int main() {
#ifdef ENABLE_CPROVER
  int a = nondet_int();
  int b = nondet_int();

  __CPROVER_assume(a < 16384);
  __CPROVER_assume(b < 16384);
#elif ENABLE_KLEE
  int a;
  int b;

  klee_make_symbolic(&a, sizeof(a), "a");
  klee_make_symbolic(&b, sizeof(b), "b");

  if (a >= 16384)
    return 0;

  if (b >= 16384)
    return 0;
#endif

  int result = sumR(a, b, N);
  assert(result == ((a*(N+1)) + (b*(N+1)*(N/2))));

  return 0;
}
