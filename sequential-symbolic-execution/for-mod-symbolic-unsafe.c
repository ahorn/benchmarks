// Congruence modulo K
#define K 7

// Similar to entering "if (c) { ... }"
#define ASSUME(c) __CPROVER_assume((c))

int nondet_int();

int main(void)
{
  int k = nondet_int();
  ASSUME(0 <= k && k < K);
  for (int n = 0; n < N; n = n + 1)
  {
    if (k == K)
    {
      k = 0;
    }
    k = k + 1;
  }
  assert(k < K);
}
