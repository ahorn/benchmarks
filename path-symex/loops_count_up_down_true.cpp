typedef unsigned int uint;
uint nse_symbolic_uint();
void nse_assert(bool);

int main()
{
  uint n = nse_symbolic_uint();
  uint x=n, y=0;

  if (x > 1024)
    return 1;

  while(x>0)
  {
    x--;
    y++;
  }
  nse_assert(y==n);

  return 0;
}

