#define N 2000

void nse_assume(bool);
void nse_assert(bool);
int nse_symbolic_int();

int main() {
  int k = nse_symbolic_int();
  nse_assume(0 <= k && k < 7);

  for (int n = 0; n < N; n = n + 1) {
    if (k == 7) {
      k = 0;
    }
    k = k + 1;
  }

  nse_assert(k <= 7);
  return 0;
}
