#define a (2)
int nse_symbolic_int();
void nse_assert(bool);
int main() { 
  int i, n=nse_symbolic_int(), sn=0;
  for(i=1; i<=n; i++) {
    if (i<10)
    sn = sn + a;
  }
  nse_assert(sn==n*a || sn == 0);
  return 1;
}
