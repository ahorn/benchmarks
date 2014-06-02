// For more explanations, see Section 2.2 (Sums and Recurrences) in
// "Concrete Mathematics", Second Edition, by Ronald L. Graham,
// Donald E. Knuth, and Oren Patashnik

#include <iostream>
#include <nse_sequential.h>
#include <nse_report.h>

#ifndef dfs_checker
#define dfs_checker crv::backtrack_dfs_checker
#endif

crv::Internal<int> sumR(const crv::Internal<int>& a, const crv::Internal<int>& b, const crv::Internal<int>& k) {
  crv::Internal<int> sum = a + b*k;
  if (dfs_checker().branch(k > 0))
    return sum + sumR(a, b, k-1);
  else
    return sum;
}

#define N 46

// N must be even
void crv_main() {
  crv::Internal<int> a, b;
  dfs_checker().add_assertion(a < 16384);
  dfs_checker().add_assertion(b < 16384);

  crv::Internal<int> result = sumR(a, b, N);
  dfs_checker().add_error(result == ((a*(N+1)) + (b*(N+1)*(N/2))));
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

  report_statistics(dfs_checker().solver().stats(), dfs_checker().stats(), seconds);

  return error;
}
