#include <iostream>
#include <nse_sequential.h>
#include <nse_report.h>

#ifndef dfs_checker
#define dfs_checker crv::backtrack_dfs_checker
#endif

#ifdef FORCE_BRANCH
#define BRANCH_CALL force_branch
#else
#define BRANCH_CALL branch
#endif

#define N 46340

// conservatively safe for N <= 46340
void crv_main() {
  crv::Internal<unsigned> n = 1;
  crv::Internal<unsigned> sum = 0;

  while (dfs_checker().BRANCH_CALL(n <= N)) {
    sum = sum + n;
    n = n + 1;
  }

  dfs_checker().add_error(sum != ((N * (N + 1)) / 2));
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

  report_statistics(dfs_checker().solver().stats(), dfs_checker().stats(), seconds);

  return error;
}
