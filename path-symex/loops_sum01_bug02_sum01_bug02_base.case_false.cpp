#define a (2)
void nse_assert(bool);
int nse_symbolic_int();
int main() { 
  int i, n=nse_symbolic_int(), sn=0;
  for(i=1; i<=n; i++) {
    sn = sn + a;
    if (i==4) sn=-10;
  }
  nse_assert(sn==n*a || sn == 0);
  return 0;
}
