// Similar to SV-COMP'14 (loops/count_up_down_false.c) except
// that we use explicit signedness constraints to support
// benchmarks with tools that are not bit precise.
#include <assert.h>

int nondet_int();

// It suffices to unwind N times
int main() {
  int n = nondet_int();
  __CPROVER_assume(0 <= n && n < N);

  int x = n, y = 0;
  while (x > 0) {
    x = x - 1;
    y = y + 1;
  }
  assert(0 <= y && y != n);
  return 0;
}
