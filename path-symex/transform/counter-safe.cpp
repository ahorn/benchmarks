// Similar to SV-COMP'14 (loops/count_up_down_true.c) except
// that we use explicit signedness constraints to support
// benchmarks with tools that are not bit precise.

#include <iostream>
#include <nse_sequential.h>

#ifndef dfs_checker
#define dfs_checker crv::backtrack_dfs_checker
#endif

#include "report.h"

#ifdef FORCE_BRANCH
#define BRANCH_CALL force_branch
#else
#define BRANCH_CALL branch
#endif

#define N 500

// It suffices to unwind N times
void crv_main() {
  crv::Internal<int> n;
  dfs_checker().add_assertion(0 <= n && n < N);

  crv::Internal<int> x = n, y = 0;
  while (dfs_checker().BRANCH_CALL(x > 0)) {
    x = x - 1;
    y = y + 1;
  }

  dfs_checker().add_error(!(0 <= y) || !(y == n));
}

int main() {
  bool error = false;

  std::chrono::seconds seconds(std::chrono::seconds::zero());
  {
    smt::NonReentrantTimer<std::chrono::seconds> timer(seconds);
  
    do {
      crv_main();
  
#ifndef FORCE_BRANCH
      error |= smt::sat == dfs_checker().check();
#endif
    } while (dfs_checker().find_next_path() && !error);
  }

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  report_time(seconds);

  return error;
}
