#define a (2)
int nse_symbolic_int();
void nse_assert(bool);

int main() { 
  int i, j=10, n=nse_symbolic_int(), sn=0;
  for(i=1; i<=n; i++) {
    if (i<j) 
    sn = sn + a;
    j--;
  }
  nse_assert(sn==n*a || sn == 0);
  return 0;
}
