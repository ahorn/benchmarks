// From SV-COMP'14 (loops/count_up_down_true.c)
#include <assert.h>

unsigned int nondet_uint();

// It suffices to unwind N times
int main() {
  unsigned int n = nondet_uint();
  __CPROVER_assume(n < N);

  unsigned int x = n, y = 0;
  while (x > 0) {
    x = x - 1;
    y = y + 1;
  }
  assert(y == n);
  return 0;
}
