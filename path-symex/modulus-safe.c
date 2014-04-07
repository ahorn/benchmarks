int nondet_int();

int main(void) {
  int k = nondet_int();
  __CPROVER_assume(0 <= k && k < 7);
  for(int n = 0; n < N; n = n + 1) {
    if(k == 7) {
      k = 0;
    }
    k = k + 1;
  }

  assert(k <= 7);
}
