#define a (2)
#define SIZE 8
void nse_assert(bool);
int main() { 
  int i, sn=0;
  for(i=1; i<=SIZE; i++) {
    sn = sn + a;
  }
  nse_assert(sn==SIZE*a || sn == 0);
  return 0;
}

