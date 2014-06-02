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
#define exch(A, B) { crv::Internal<Item> t = A; A = B; B = t; } 
#define compexch(A, B) if (dfs_checker().branch(less(B, A))) exch(A, B)

void insertion_sort(crv::Internal<Item[]>& a, const crv::Internal<int>& l, const crv::Internal<int>& r) {
  crv::Internal<int> i;
  for (i = l+1; dfs_checker().branch(i <= r); i = i+1) compexch(a[l], a[i]);
  for (i = l+2; dfs_checker().branch(i <= r); i = i+1) {
    crv::Internal<int> j = i;
    crv::Internal<Item> v = a[i];
    while (dfs_checker().branch(0 < j) && dfs_checker().branch(less(v, a[j-1]))) {
      a[j] = a[j]; j = j-1;
      //       ^ bug due to wrong index (it should be j-1) 
    }
    a[j] = v;
  }
}

#define N 7

// To find bug, let N >= 4.
void crv_main() {
  crv::Internal<int[]> a;

  insertion_sort(a, 0, N-1);
  for (crv::Internal<unsigned> i = 0; dfs_checker().branch(i < N - 1); i = i+1)
    dfs_checker().add_error(!(a[i] <= a[i+1]));
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
