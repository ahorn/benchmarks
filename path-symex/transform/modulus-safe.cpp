#include <iostream>
#include <crv.h>

#define N 2000

void crv_main() {
  crv::Internal<int> k;
  crv::tracer().add_assertion(0 <= k && k < 7);

  for(crv::Internal<int> n = 0; crv::tracer().decide_flip(n < N); n = n + 1) {
    if(crv::tracer().decide_flip(k == 7)) {
      k = 0;
    }
    k = k + 1;
  }

  crv::tracer().add_error(!(k <= 7));
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
