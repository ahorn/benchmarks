// For more explanations, see Section 2.2 (Sums and Recurrences) in
// "Concrete Mathematics", Second Edition, by Ronald L. Graham,
// Donald E. Knuth, and Oren Patashnik

#include <iostream>
#include <nse_sequential.h>

crv::Internal<int> sumR(const crv::Internal<int>& a, const crv::Internal<int>& b, const crv::Internal<int>& k) {
  crv::Internal<int> sum = a + b*k;
  if (crv::sequential_dfs_checker().branch(k > 0))
    return sum + sumR(a, b, k-1);
  else
    return sum;
}

#define N 46

// N must be even
void crv_main() {
  crv::Internal<int> a, b;
  crv::sequential_dfs_checker().add_assertion(a < 16384);
  crv::sequential_dfs_checker().add_assertion(b < 16384);

  crv::Internal<int> result = sumR(a, b, N);
  crv::sequential_dfs_checker().add_error(result != ((a*(N+1)) + (b*(N+1)*(N/2))));
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
