// This file contains code snippets from "Algorithms in C, Third Edition,
// Parts 1-4," by Robert Sedgewick.
//
// See https://www.cs.princeton.edu/~rs/Algs3.c1-4/code.txt

#define N 7

void nse_assert(bool);

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

  mergesort(a, 0, N-1);

  for (unsigned i = 0; i < N - 1; i++)
    nse_assert(a[i] <= a[i+1]);

  return 0;
}
