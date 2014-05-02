#include <iostream>
#include <crv.h>

#define N 2000

void crv_main() {
  crv::Internal<int> k;

  for(crv::Internal<int> n = 0; crv::dfs_prune_checker().branch(n < N); n = n + 1) {
    if(crv::dfs_prune_checker().branch(k == 7)) {
      k = 0;
    }
    k = k + 1;
  }

  crv::dfs_prune_checker().add_error(!(k <= 7));
}

int main() {
  crv::dfs_prune_checker().reset();

  bool error = false;
  do {
    crv_main();

    error |= smt::sat == crv::dfs_prune_checker().check(crv::tracer());
  } while (crv::dfs_prune_checker().find_next_path() && !error);

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  return error;
}
