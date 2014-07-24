int nse_symbolic_int();
void nse_assert(bool);

int main() {
  int i=0, x=0, y=0;
  int n=nse_symbolic_int();
  if (n<=0)
    return 1;

  for(i=0; i<n; i++)
  {
    x = x-y;
    nse_assert(x==0);
    y = nse_symbolic_int();
    if (y==0)
      return 1;
    x = x+y;
    nse_assert(x!=0);
  }
  nse_assert(x==0);

  return 0;
}

