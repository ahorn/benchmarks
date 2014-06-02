// This file contains code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick.
//
// See https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#include <iostream>
#include <nse_sequential.h>

#include "report.h"

#ifndef dfs_checker
#define dfs_checker crv::sequential_dfs_checker
#endif

#ifdef FORCE_BRANCH
#define BRANCH_CALL force_branch
#else
#define BRANCH_CALL branch
#endif

// Note that we do not instrument this type on purpose
typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))

crv::Internal<Item[]> aux;
void merge(crv::Internal<Item[]>& a, const crv::Internal<int>& l, const crv::Internal<int>& m, const crv::Internal<int>& r) {
  crv::Internal<int> i, j, k;
  for (i = m+1; dfs_checker().BRANCH_CALL(i > l); i = i-1) aux[i-1] = a[i-1];
  for (j = m; dfs_checker().BRANCH_CALL(j < r); j = j+1) aux[r+m-j] = a[j+1];
  for (k = l; dfs_checker().BRANCH_CALL(k <= r); k = k+1)
    if (dfs_checker().BRANCH_CALL(less(aux[i], aux[j])))
    {
      a[k] = aux[i];
      i = i+1;
    } else {
      a[k] = aux[j];
      j = j-1;
    }
}

void mergesort(crv::Internal<Item[]>& a, const crv::Internal<int>& l, const crv::Internal<int>& r) {
  crv::Internal<int> m = (r+l)/2;
  if (dfs_checker().BRANCH_CALL(r <= l)) return;
  mergesort(a, l, m);
  mergesort(a, m+1, r);
  merge(a, l, m, r);
}

#define N 7

void crv_main() {
  crv::Internal<Item[]> a;

  mergesort(a, 0, N-1);
  for (crv::Internal<unsigned> i = 0; dfs_checker().BRANCH_CALL(i < N - 1); i = i+1)
    dfs_checker().add_error(!(a[i] <= a[i+1]));
}

int main() {
  bool error = false;

  std::chrono::seconds seconds(std::chrono::seconds::zero());
  {
    smt::NonReentrantTimer<std::chrono::seconds> timer(seconds);

    do {
      // global array ought to be initially nondeterministic
      crv::make_any(aux);
  
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
