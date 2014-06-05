// Similar to SV-COMP'14 (loops/count_up_down_false.c) except
// that we use explicit signedness constraints to support
// benchmarks with tools that are not bit precise.

#define N 500

void nse_assume(bool);
void nse_assert(bool);
int nse_symbolic_int();

// It suffices to unwind N times
int main() {
  int n = nse_symbolic_int();
  nse_assume(0 <= n && n < N);

  int x = n, y = 0;
  while (x > 0) {
    x = x - 1;
    y = y + 1;
  }
  nse_assert(0 <= y && y != n);
  return 0;
}
