#include <assert.h>

// This file contains code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick.
//
// See https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; } 

int partition(Item a[], int l, int r);
void quick_sort(Item a[], int l, int r) {
  int i;
  if (r <= l) return;
  i = partition(a, l, r);
  quick_sort(a, l, i-1);
  quick_sort(a, i+1, r);
}

int partition(Item a[], int l, int r) {
  int i = l-1, j = r; Item v = a[r];
  for (;;) { 
    while (less(a[++i], v)) ;
    while (less(v, a[--j])) if (j == l) break;
    if (i >= j) break;
    exch(a[i], a[j]);
  }
  exch(a[i], a[r]);
  return i;
}

int nondet_int();
int a[N];

// It suffices to unwind at most N^2 steps.
int main() {
  for (unsigned i = 0; i < N; i++)
    a[i] = nondet_int();

  quick_sort(a, 0, N-1);
  for (unsigned i = 0; i < N - 1; i++)
    assert(a[i] <= a[i+1]);

  return 0;
}
