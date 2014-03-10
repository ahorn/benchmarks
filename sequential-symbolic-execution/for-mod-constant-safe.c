// Test constant propagation in a tight loop

// Congruence modulo K
#define K 7

int main(void)
{
  int k = 0;
  for (int n = 0; n < N; n = n + 1)
  {
    if (k == K)
    {
      k = 0;
    }
    k = k + 1;
  }

  assert(k == (N % K));
  assert(k < K);
}
