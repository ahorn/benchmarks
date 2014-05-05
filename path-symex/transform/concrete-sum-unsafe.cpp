#include <iostream>
#include <nse_sequential.h>

#define N 46340

void crv_main() {
  crv::Internal<unsigned> n = 1;
  crv::Internal<unsigned> sum = 0;

  while (crv::sequential_dfs_checker().branch(n <= N)) {
    sum = sum + n;
    n = n + 1;
  }

  crv::sequential_dfs_checker().add_error(sum == ((N * (N + 1)) / 2));
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
