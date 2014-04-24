// Similar to SV-COMP'14 (loops/count_up_down_false.c) except
// that we use explicit signedness constraints to support
// benchmarks with tools that are not bit precise.

#include <iostream>
#include <crv.h>

#define N 500

// It suffices to unwind N times
void crv_main() {
  crv::Internal<int> n;
  crv::dfs_prune_checker().add_assertion(0 <= n && n < N);

  crv::Internal<int> x = n, y = 0;
  while (crv::dfs_prune_checker().branch(x > 0)) {
    x = x - 1;
    y = y + 1;
  }

  crv::dfs_prune_checker().add_error(0 <= y && y == n);
}

int main() {
  crv::dfs_prune_checker().reset();
  crv::Encoder encoder;

  bool error = false;
  do {
    crv_main();

    error |= smt::sat == encoder.check(crv::tracer(), crv::dfs_prune_checker());
  } while (crv::dfs_prune_checker().find_next_path() && !error);

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  return error;
}
