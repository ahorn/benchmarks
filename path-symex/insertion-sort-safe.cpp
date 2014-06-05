// This file contains code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick.
//
// See https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#define N 7

void nse_assert(bool);

typedef int Item;
#define key(A) (A)
#define less(A, B) (key(A) < key(B))
#define exch(A, B) { Item t = A; A = B; B = t; } 
#define compexch(A, B) if (less(B, A)) exch(A, B)

void insertion_sort(Item a[], int l, int r) {
  int i;
  for (i = l+1; i <= r; i++) compexch(a[l], a[i]);
  for (i = l+2; i <= r; i++) {
    int j = i; Item v = a[i];
    while (0 < j && less(v, a[j-1])) {
      a[j] = a[j-1]; j--;
    }
    a[j] = v;
  }
}

int main() {
  int a[N];

  insertion_sort(a, 0, N-1);
  for (unsigned i = 0; i < N - 1; i++)
    nse_assert(a[i] <= a[i+1]);

  return 0;
}
