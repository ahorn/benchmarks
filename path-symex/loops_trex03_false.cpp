typedef unsigned int uint;
extern uint nse_symbolic_uint();
bool nse_symbolic_bool();
void nse_assert(bool);

#define _Bool bool

int main()
{
  uint x1=nse_symbolic_uint(), x2=nse_symbolic_uint(), x3=nse_symbolic_uint();
  uint d1=1, d2=1, d3=1;
  bool c1, c2;
  
  while(x1>0 && x2>0 && x3>0)
  {
    if (c1) x1=x1-d1;
    else if (c2) x2=x2-d2;
    else x3=x3-d3;
    c1=nse_symbolic_bool();
    c2=nse_symbolic_bool();
  }

  nse_assert(x1==0 && x2==0 && x3==0);
  return 0;
}

