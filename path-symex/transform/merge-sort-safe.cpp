// This file contains code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick.
//
// See https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#include <iostream>
#include <crv.h>

// Note that we do not instrument this type on purpose
typedef int Item;

#define key(A) (A)
#define less(A, B) (key(A) < key(B))

crv::Internal<Item[]> aux;
void merge(crv::Internal<Item[]>& a, const crv::Internal<int>& l, const crv::Internal<int>& m, const crv::Internal<int>& r) {
  crv::Internal<int> i, j, k;
  for (i = m+1; crv::dfs_prune_checker().branch(i > l); i = i-1) aux[i-1] = a[i-1];
  for (j = m; crv::dfs_prune_checker().branch(j < r); j = j+1) aux[r+m-j] = a[j+1];
  for (k = l; crv::dfs_prune_checker().branch(k <= r); k = k+1)
    if (crv::dfs_prune_checker().branch(less(aux[i], aux[j])))
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
  if (crv::dfs_prune_checker().branch(r <= l)) return;
  mergesort(a, l, m);
  mergesort(a, m+1, r);
  merge(a, l, m, r);
}

#define N 7

void crv_main() {
  crv::Internal<Item[]> a;

  mergesort(a, 0, N-1);
  for (crv::Internal<unsigned> i = 0; crv::dfs_prune_checker().branch(i < N - 1); i = i+1)
    crv::dfs_prune_checker().add_error(!(a[i] <= a[i+1]));
}

int main() {
  crv::dfs_prune_checker().reset();
  crv::Encoder encoder;

  bool error = false;
  do {
    // global array ought to be initially nondeterministic
    make_any(aux);

    crv_main();

    error |= smt::sat == encoder.check(crv::tracer(), crv::dfs_prune_checker());
  } while (crv::dfs_prune_checker().find_next_path() && !error);

  if (error)
    std::cout << "Found bug!" << std::endl;
  else
    std::cout << "Could not find any bugs." << std::endl;

  return error;
}