int nse_symbolic_int();
bool nse_symbolic_bool();
void nse_assert(bool);

int main()
{
  int x=nse_symbolic_int();
  int y=nse_symbolic_int();
  int z=nse_symbolic_int();

  while(x<100 && 100<z) 
  {
    bool tmp;
    if (tmp)
   {
     x++;
   }
   else
   {
     x--;
     z--;
   }
  }                       
    
  nse_assert(x>100);    
  return 0;
}


