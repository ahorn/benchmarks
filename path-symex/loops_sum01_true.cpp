#define a (2)
#define N 200
void nse_assert(bool);
int main() { 
  int i, n=N, sn=0;
  for(i=1; i<=n; i++) {
    sn = sn + a;
  }
  nse_assert(sn==n*a || sn == 0);
  return 0;
}
