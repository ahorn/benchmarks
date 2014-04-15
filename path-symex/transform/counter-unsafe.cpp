// Similar to SV-COMP'14 (loops/count_up_down_false.c) except
// that we use explicit signedness constraints to support
// benchmarks with tools that are not bit precise.

#include <iostream>
#include <crv.h>

#define N 500

// It suffices to unwind N times
void crv_main() {
  unsigned unwind = N;

  crv::Internal<int> n;
  crv::tracer().add_assertion(0 <= n && n < N);

  crv::Internal<int> x = n, y = 0;
  while (crv::tracer().decide_flip(x > 0)) {
    x = x - 1;
    y = y + 1;

    unwind--;
    if (unwind == 0)
      // reached loop unrolling bound
      break;
  }

  crv::tracer().add_error(0 <= y && y == n);
}

int main() {
  crv::tracer().reset();
  crv::Encoder encoder;

  bool error = false;
  do {
    crv_main();

    error |= smt::sat == encoder.check(crv::tracer());
  } while (crv::tracer().flip() && !error);

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  return error;
}
