// For more explanations, see Section 2.2 (Sums and Recurrences) in
// "Concrete Mathematics", Second Edition, by Ronald L. Graham,
// Donald E. Knuth, and Oren Patashnik

#define N 46

void nse_assume(bool);
void nse_assert(bool);
int nse_symbolic_int();

int sumR(int a, int b, int k) {
  int sum = a + b*k;
  if (k > 0)
    return sum + sumR(a, b, k-1);
  else
    return sum;
}

// N must be even
int main() {
  int a = nse_symbolic_int();
  int b = nse_symbolic_int();

  nse_assume(a < 16384);
  nse_assume(b < 16384);

  int result = sumR(a, b, N);
  nse_assert(result != ((a*(N+1)) + (b*(N+1)*(N/2))));
  //            ^ in fact, LHS is equals equal to RHS

  return 0;
}
