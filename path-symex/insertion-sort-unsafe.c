#include <assert.h>

// This file contains modified code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick. The code is intentionally buggy!
//
// For the correct code, see https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; } 
#define compexch(A, B) if (less(B, A)) exch(A, B)

void insertion_sort(Item a[], int l, int r)
{
  int i;
  for (i = l+1; i <= r; i++) compexch(a[l], a[i]);
  for (i = l+2; i <= r; i++) {
    int j = i; Item v = a[i]; 
    while (less(v, a[j-1])) {
      a[j] = a[j]; j--;
      //       ^ bug due to wrong index (it should be j-1) 
    }
    a[j] = v; 
  } 
} 

// To find bug, let N >= 4.
// It suffices to unwind at most N^2 steps.
int main() {
  Item a[N];
  insertion_sort(a, 0, N-1);

  for (unsigned i = 0; i < N - 1; i++)
    assert(a[i] <= a[i+1]);

  return 0;
}
