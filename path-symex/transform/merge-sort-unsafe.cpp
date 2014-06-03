// This file contains modified code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick. The code is intentionally buggy!
//
// For the correct code, see https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#include <iostream>
#include <nse_sequential.h>
#include <nse_report.h>

#ifndef dfs_checker
#define dfs_checker crv::backtrack_dfs_checker
#endif

// Note that we do not instrument this type on purpose
typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))

#define N 7

crv::Internal<Item[N]> aux;
void merge(crv::Internal<Item*> a, const crv::Internal<int> l, const crv::Internal<int> m, const crv::Internal<int> r) {
  crv::Internal<int> i, j, k;
  for (i = m+1; dfs_checker().branch(i > l); i = i-1) aux[i-1] = a[i-1];
  for (j = m; dfs_checker().branch(j < r); j = j+1) aux[r+m-j] = a[j];
  //                                                               ^ bug due to wrong offset (it should be j+1)
  for (k = l; dfs_checker().branch(k <= r); k = k+1)
    if (dfs_checker().branch(less(aux[i], aux[j])))
    {
      a[k] = aux[i];
      i = i+1;
    } else {
      a[k] = aux[j];
      j = j-1;
    }
}

void mergesort(crv::Internal<Item*> a, const crv::Internal<int> l, const crv::Internal<int> r) {
  crv::Internal<int> m = (r+l)/2;
  if (dfs_checker().branch(r <= l)) return;
  mergesort(a, l, m);
  mergesort(a, m+1, r);
  merge(a, l, m, r);
}

// To find bug, let N >= 4.
void crv_main() {
  crv::Internal<Item[N]> a;

  mergesort(a, 0, N-1);
  for (crv::Internal<unsigned> i = 0; dfs_checker().branch(i < N - 1); i = i+1)
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
