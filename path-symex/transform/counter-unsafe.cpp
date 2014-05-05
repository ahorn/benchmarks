// Similar to SV-COMP'14 (loops/count_up_down_false.c) except
// that we use explicit signedness constraints to support
// benchmarks with tools that are not bit precise.

#include <iostream>
#include <nse_sequential.h>

#define N 500

// It suffices to unwind N times
void crv_main() {
  crv::Internal<int> n;
  crv::sequential_dfs_checker().add_assertion(0 <= n && n < N);

  crv::Internal<int> x = n, y = 0;
  while (crv::sequential_dfs_checker().branch(x > 0)) {
    x = x - 1;
    y = y + 1;
  }

  crv::sequential_dfs_checker().add_error(0 <= y && y == n);
}

int main() {
  crv::sequential_dfs_checker().reset();

  bool error = false;
  do {
    crv_main();

    error |= smt::sat == crv::sequential_dfs_checker().check();
  } while (crv::sequential_dfs_checker().find_next_path() && !error);

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  return error;
}
