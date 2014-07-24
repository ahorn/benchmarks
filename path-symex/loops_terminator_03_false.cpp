int nse_symbolic_int();
void nse_assert(bool);

int main()
{
  int x=nse_symbolic_int();
  int y=nse_symbolic_int();

  if (y>0)
  {
    while(x<100) 
    {
      x=x+y;
     }
  }                           
  nse_assert(y<=0 || (y<0 && x>=100));
  return 0;
}


