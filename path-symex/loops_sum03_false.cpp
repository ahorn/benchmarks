#define a (2)
typedef unsigned int uint;
uint nse_symbolic_uint();
void nse_assert(bool);

int main() { 
  int sn=0;
  uint loop1=nse_symbolic_uint(), n1=nse_symbolic_uint();
  uint x=0;

  for (int i = 0; i < 12; ++i) {
    if (x<10)
      sn = sn + a;
    x++;
    nse_assert(sn==x*a || sn == 0);
  }
  return 0;
}

