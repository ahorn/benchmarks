#define N 46340

void nse_assert(bool);

int main() {
  unsigned n = 1;
  unsigned sum = 0;

  while (n <= N)
  {
    sum = sum + n;
    n = n + 1;
  }

  nse_assert(sum != ((N * (N + 1)) / 2));

  return 0;
}
