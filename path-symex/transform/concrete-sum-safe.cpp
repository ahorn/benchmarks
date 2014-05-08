#include <iostream>
#include <nse_sequential.h>

#include "report.h"

#define N 46340

// conservatively safe for N <= 46340
void crv_main() {
  crv::Internal<unsigned> n = 1;
  crv::Internal<unsigned> sum = 0;

  while (crv::sequential_dfs_checker().branch(n <= N)) {
    sum = sum + n;
    n = n + 1;
  }

  crv::sequential_dfs_checker().add_error(sum != ((N * (N + 1)) / 2));
}

int main() {
  bool error = false;

  std::chrono::seconds seconds(std::chrono::seconds::zero());
  {
    smt::NonReentrantTimer<std::chrono::seconds> timer(seconds);

    do {
      crv_main();

      error |= smt::sat == crv::sequential_dfs_checker().check();
    } while (crv::sequential_dfs_checker().find_next_path() && !error);
  }

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  report_time(seconds);

  return error;
}
