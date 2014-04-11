#include <assert.h>

// conservatively safe for N <= 46340
int main(void) {
  unsigned n = 1;
  unsigned sum = 0;

  while (n <= N)
  {
    sum = sum + n;
    n = n + 1;
  }

  assert(sum == ((N * (N + 1)) / 2));

  return 0;
}
