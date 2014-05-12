// This file contains code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick.
//
// See https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#include <assert.h>

#ifdef ENABLE_KLEE
#include <klee/klee.h>
#endif

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))

Item aux[N];
void merge(Item a[], int l, int m, int r) {
  int i, j, k;
  for (i = m+1; i > l; i--) aux[i-1] = a[i-1];
  for (j = m; j < r; j++) aux[r+m-j] = a[j+1];
  for (k = l; k <= r; k++)
    if (less(aux[i], aux[j]))
      a[k] = aux[i++]; else a[k] = aux[j--];
}

void mergesort(Item a[], int l, int r) {
  int m = (r+l)/2;
  if (r <= l) return;
  mergesort(a, l, m);
  mergesort(a, m+1, r);
  merge(a, l, m, r);
}

int main() {
  int a[N];

#ifdef ENABLE_KLEE
  klee_make_symbolic(a, sizeof(a), "a");
#endif

  mergesort(a, 0, N-1);

#ifndef FORCE_BRANCH
  for (unsigned i = 0; i < N - 1; i++)
    assert(a[i] <= a[i+1]);
#endif

  return 0;
}
