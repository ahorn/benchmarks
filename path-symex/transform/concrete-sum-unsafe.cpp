#include <iostream>
#include <crv.h>

#define N 46340

void crv_main() {
  crv::Internal<unsigned> n = 1;
  crv::Internal<unsigned> sum = 0;

  while (crv::dfs_prune_checker().branch(n <= N)) {
    sum = sum + n;
    n = n + 1;
  }

  crv::dfs_prune_checker().add_error(sum == ((N * (N + 1)) / 2));
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
