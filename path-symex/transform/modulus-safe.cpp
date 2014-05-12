#include <iostream>
#include <nse_sequential.h>

#include "report.h"

#ifdef FORCE_BRANCH
#define BRANCH_CALL force_branch
#else
#define BRANCH_CALL branch
#endif

#define N 2000

void crv_main() {
  crv::Internal<int> k;
  crv::sequential_dfs_checker().add_assertion(0 <= k && k < 7);

  for(crv::Internal<int> n = 0; crv::sequential_dfs_checker().BRANCH_CALL(n < N); n = n + 1) {
    if(crv::sequential_dfs_checker().BRANCH_CALL(k == 7)) {
      k = 0;
    }
    k = k + 1;
  }

  crv::sequential_dfs_checker().add_error(!(k <= 7));
}

int main() {
  bool error = false;

  std::chrono::seconds seconds(std::chrono::seconds::zero());
  {
    smt::NonReentrantTimer<std::chrono::seconds> timer(seconds);

    do {
      crv_main();

#ifndef FORCE_BRANCH
      error |= smt::sat == crv::sequential_dfs_checker().check();
#endif
    } while (crv::sequential_dfs_checker().find_next_path() && !error);
  }

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  report_time(seconds);

  return error;
}
