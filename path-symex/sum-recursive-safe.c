// For more explanations, see Section 2.2 (Sums and Recurrences) in
// "Concrete Mathematics", Second Edition, by Ronald L. Graham,
// Donald E. Knuth, and Oren Patashnik

#include <assert.h>

int sumR(int a, int b, int k) {
  int sum = a + b*k;
  if (k > 0)
    return sum + sumR(a, b, k-1);
  else
    return sum;
}

// N must be even
int main() {
  int a = nondet_int();
  int b = nondet_int();

  __CPROVER_assume(a < 16384);
  __CPROVER_assume(b < 16384);

  int result = sumR(a, b, N);
  assert(result == ((a*(N+1)) + (b*(N+1)*(N/2))));

  return 0;
}
