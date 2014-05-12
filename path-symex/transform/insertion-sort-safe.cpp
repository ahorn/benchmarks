// This file contains code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick.
//
// See https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#include <iostream>
#include <nse_sequential.h>

#include "report.h"

#ifdef FORCE_BRANCH
#define BRANCH_CALL force_branch
#else
#define BRANCH_CALL branch
#endif

// Note that we do not instrument this type on purpose
typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { crv::Internal<Item> t = A; A = B; B = t; } 
#define compexch(A, B) if (crv::sequential_dfs_checker().BRANCH_CALL(less(B, A))) exch(A, B)

void insertion_sort(crv::Internal<Item[]>& a, const crv::Internal<int>& l, const crv::Internal<int>& r) {
  crv::Internal<int> i;
  for (i = l+1; crv::sequential_dfs_checker().BRANCH_CALL(i <= r); i = i+1) compexch(a[l], a[i]);
  for (i = l+2; crv::sequential_dfs_checker().BRANCH_CALL(i <= r); i = i+1) {
    crv::Internal<int> j = i;
    crv::Internal<Item> v = a[i];
    while (crv::sequential_dfs_checker().BRANCH_CALL(0 < j) && crv::sequential_dfs_checker().BRANCH_CALL(less(v, a[j-1]))) {
      a[j] = a[j-1]; j = j-1;
    }
    a[j] = v;
  }
}

#define N 7

void crv_main() {
  crv::Internal<int[]> a;

  insertion_sort(a, 0, N-1);
  for (crv::Internal<unsigned> i = 0; crv::sequential_dfs_checker().BRANCH_CALL(i < N - 1); i = i+1)
    crv::sequential_dfs_checker().add_error(!(a[i] <= a[i+1]));
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
