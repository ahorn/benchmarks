#include <iostream>
#include <crv.h>

#define N 46340

// conservatively safe for N <= 46340
void crv_main() {
  crv::Internal<unsigned> n = 1;
  crv::Internal<unsigned> sum = 0;

  while (crv::tracer().decide_flip(n <= N)) {
    sum = sum + n;
    n = n + 1;
  }

  crv::tracer().add_error(sum != ((N * (N + 1)) / 2));
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
