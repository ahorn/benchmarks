#include <iostream>
#include <nse_sequential.h>

#ifndef dfs_checker
#define dfs_checker crv::backtrack_dfs_checker
#endif

#include "report.h"

#define N 2000

void crv_main() {
  crv::Internal<int> k;

  for(crv::Internal<int> n = 0; dfs_checker().branch(n < N); n = n + 1) {
    if(dfs_checker().branch(k == 7)) {
      k = 0;
    }
    k = k + 1;
  }

  dfs_checker().add_error(!(k <= 7));
}

int main() {
  bool error = false;

  std::chrono::seconds seconds(std::chrono::seconds::zero());
  {
    smt::NonReentrantTimer<std::chrono::seconds> timer(seconds);

    do {
      crv_main();
  
      error |= smt::sat == dfs_checker().check();
  
    } while (dfs_checker().find_next_path() && !error);
  }

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  report_time(seconds);

  return error;
}
